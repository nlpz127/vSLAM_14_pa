#include <iostream>
#include <cmath>
using namespace std;

#include <Eigen/Core>
#include <Eigen/Geometry> // Eigen/Geometry 模块提供了各种旋转和平移的表示
using namespace Eigen;

// 本程序演示了 Eigen 几何模块的使用方法

int main(int argc, char **argv) {

  /* 旋转矩阵与旋转向量、欧拉角之间的相互转换 */
  // 3D 旋转矩阵直接使用 Matrix3d 或 Matrix3f
  Matrix3d rotation_matrix = Matrix3d::Identity(); // 单位矩阵
  cout << "[rotation matrix]\n" << rotation_matrix << endl;
  cout << endl;

  // 旋转向量使用 AngleAxis, 它底层不直接是Matrix，但运算可以当作矩阵（因为重载了运算符）
  AngleAxisd rotation_vector(M_PI / 4, Vector3d(0, 0, 1));     //沿 Z 轴旋转 45 度，旋转向量好像不能直接表示出来，必须以矩阵的形式表示
  cout.precision(3);
  cout << "[1 - rotation matrix]\n" << rotation_vector.matrix() << endl;   //用matrix()转换成矩阵
  // 也可以直接赋值，将旋转向量变为旋转矩阵
  rotation_matrix = rotation_vector.toRotationMatrix();
  cout << "[2 - rotation_vector --> rotation_matrix]\n" << rotation_matrix << endl;
  cout <<endl;

  // 用 AngleAxis 可以进行坐标变换，这里的例子是一个向量通过旋转向量变化后的结果
  Vector3d v(1, 0, 0);
  Vector3d v_rotated = rotation_vector * v;
  //cout << "[(1,0,0) after rotation (by angle axis)] = \n" << v_rotated.transpose() << endl;
  cout << "[(1,0,0) after rotation (by angle axis)] = \n" << v_rotated << endl;
  cout << endl;

  // 或者用旋转矩阵
  v_rotated = rotation_matrix * v;
  cout << "[(1,0,0) after rotation (by matrix)] = \n" << v_rotated << endl;
  cout << endl;

  // 欧拉角: 可以将旋转矩阵直接转换成欧拉角
  Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX顺序，即yaw-pitch-roll顺序，这里的参数得记牢了
  cout << "[yaw pitch roll] = \n" << euler_angles << endl;
  cout << endl;

  /*变换矩阵，即是 旋转矩阵 + 平移 的表达*/
  // 欧氏变换矩阵使用 Eigen::Isometry
  Isometry3d T = Isometry3d::Identity();                // 虽然称为3d，实质上是4＊4的矩阵
  T.rotate(rotation_vector);                                     // 按照rotation_vector进行旋转
  T.pretranslate(Vector3d(1, 3, 4));                     // 把平移向量设成(1,3,4)
  cout << "[Transform matrix] = \n" << T.matrix() << endl;
  cout << endl;

  // 用变换矩阵进行坐标变换
  Vector3d v_transformed = T * v;                              // 相当于R*v+t
  cout << "[v tranformed] = \n" << v_transformed << endl;
  cout << endl;

  // 对于仿射和射影变换，使用 Eigen::Affine3d 和 Eigen::Projective3d 即可，略

  /* 四元数 */
  // 旋转向量 -> 四元数，可以直接把AngleAxis赋值给四元数，反之亦然
  Quaterniond q = Quaterniond(rotation_vector);
  cout << "[quaternion from rotation vector] = \n" << q.coeffs() << endl;   // 请注意coeffs的顺序是(x,y,z,w),w为实部，前三者为虚部
  
  // 旋转矩阵 -> 四元数，也可以把旋转矩阵赋给它
  q = Quaterniond(rotation_matrix);
  cout << "[quaternion from rotation matrix] = \n" << q.coeffs() << endl;
  cout << endl;

  // 使用四元数旋转一个向量，使用重载的乘法即可
  v_rotated = q * v; // 注意数学上是qvq^{-1}
  cout << "[(1,0,0) after rotation] = \n" << v_rotated << endl; // 去掉 .transpose()
  // 用常规向量乘法表示，则应该如下计算，这是书本上的计算公式
  cout << "[should be equal to] \n" << (q * Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs() << endl; // 去掉 .transpose()

  return 0;
}
