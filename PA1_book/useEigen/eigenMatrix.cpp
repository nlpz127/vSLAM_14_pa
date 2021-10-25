#include <iostream>
using namespace std;

#include <ctime>
// eigen core
#include <Eigen/Core>
// density matrix
#include <Eigen/Dense>
using namespace Eigen;

#define MATRIX_SIZE 50

int main(int argc, char **argv){

    /*Create*/
    // Matrix<dobule, 2, 3> == Matrix3d
    Matrix<float, 2, 3> matrix_23;
    Matrix3d m_33; // Matrix3d -> double; Matrix3f -> float

    // Matrix<double, 3, 1> == Vector3d
    Matrix<float, 3, 1> vector_3d;
    Vector3d v_3d; 
    
    // Matrix<double, Dynamic, Dynamic> == MatrixXd
    Matrix<double, Dynamic, Dynamic> matrix_dynamic;
    MatrixXd m_d;

    /*init*/
    cout << "Initial..." << endl;
    // matrix_23 = Matrix<float, 2, 3>::Zero(); // zeros
    matrix_23 << 1, 2, 3, 4, 5, 6;
    cout << "[matrix_23 2x3 from 1 to 6]: \n" << matrix_23 << endl;

    m_33 = Matrix3d::Random(); // random digits
    cout << endl;

    vector_3d << 3, 2, 1;
    v_3d << 4, 5, 6;

    /*visit*/
    cout << "Visiting..." << endl;
    cout << "[print m_33]: " << endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j <3; j++){
            cout << m_33(i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl;

    /*show converted data types*/
    // pay attention to the dimensions
    // it will be wrong: Matrix<double, 2, 1> result = matrix_23 * v_3d;
    cout << "Show converted data types..." << endl;
    Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << "[result of matrix_23*v_3d]: \n" << result << endl;
    cout << endl;

    /*Some matrix operations*/
    cout << "Some matrix operations..." << endl;
    cout << "[transpose matrix_23]: \n" << matrix_23.transpose() << endl;
    cout << "[sum of matrix_23]: \n" << matrix_23.sum() << endl;
    cout << "[trace]: \n" << matrix_23.trace() << endl;
    cout << "[times 10]: \n" << 10*matrix_23 << endl;
    cout << "[inverse]: \n" << m_33.inverse() << endl;
    cout << "[determinant]: \n" << m_33.determinant() << endl;
    cout << endl;

    /*Eigenvalues and Eigenvectors*/
    cout << "Eigenvalues and Eigenvectors..." << endl;
    SelfAdjointEigenSolver<Matrix3d> eigen_solver(m_33);
    cout << "[Eigen values of m_33]: \n" << eigen_solver.eigenvalues() << endl;
    cout << "[Eigen vectors of m_33]: \n" << eigen_solver.eigenvectors() << endl;
    cout << endl;

    /*calcute matrix_NN * x = v_Nd */
    cout << "Calcute matrix_NN * x = v_Nd..." << endl;
    /* x = matrix_NN^{-1} * v_Nd */
    Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    // cout << matrix_NN(0, 0) << endl;
    matrix_NN = matrix_NN * matrix_NN.transpose(); // Guaranteed semi-positive fixation
    // cout << matrix_NN(0, 0) << endl;
    Matrix<double, MATRIX_SIZE, 1> v_Nd = MatrixXd::Random(MATRIX_SIZE, 1);

    cout << "[Direct method]..." << endl;
    clock_t time_stt = clock();
    Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    cout << "time of normal inverse is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x= " << x.transpose() << endl;

    cout << "[QR method]..." << endl; // Commonly used
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    cout << "time of QR decomposition is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x= " << x.transpose() << endl;    

    cout << "[Cholesky method]..." << endl; // Applicable to positive definite matrix
    time_stt = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    cout << "time of ldlt decomposition is " << 1000 * (clock() - time_stt) / (double)CLOCKS_PER_SEC << "ms" << endl;
    cout << "x= " << x.transpose() << endl;      

    return 0;
}