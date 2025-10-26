#include <iostream>
#include <unistd.h>
#include <cmath>
#include "linkit/matrix3.h"
#include "linkit/matrix4.h"
#include "linkit/quaternion.h"
#include "linkit/utils.h"
#include "linkit/vector3.h"
using namespace linkit;

int main()
{
    // auto i = linkit::Vector3(1, 0, 0);
    // auto j = linkit::Vector3(0, 1, 0);
    // auto k = linkit::Vector3(0, 0, 1);
    //
    // linkit::Matrix3 m;
    // linkit::Matrix4 m4;
    // linkit::Vector3 v1;
    //
    // v1 = m.rotate(M_PI_2, k) * i;
    //
    // std::cout << v1.to_string() << std::endl;
    //
    // v1 = m.rotate(M_PI_2, k).inverse() * m.rotate(M_PI_2, k) * i;
    // std::cout << v1.to_string() << std::endl;
    //
    // std::cout << (linkit::Matrix3::rotate(M_PI_2, k).determinant()) << std::endl;
    //
    // std::cout << (linkit::Matrix4::translate(linkit::Vector3(2,1,1))*to_vector4(linkit::Vector3(1,1,1))).to_string() << std::endl;

    auto q1 = Quaternion(PI/2, Vector3(1, 0 ,0));
    auto q2 = Quaternion(PI/2, Vector3(1, 0 ,0));
    auto q = q1 * q2;
    std::cout << q.angle_axis_string() << std::endl;
}
