
#ifndef Container_hpp
#define Container_hpp

#include <vector>
#include <iostream>
#include <string>
#include <cmath>
using std::vector, std::endl, std::string;

using VectorS   =  vector<string>;
using VectorD   =  vector<double>;
using Matrix2D  =  vector<VectorD>;
using Matrix3D  =  vector<Matrix2D>;


// overload + operator for VectorD + VectorD
VectorD operator+(const VectorD& vt1, const VectorD& vt2);


// overload ^ operator for VectorD ^ int
VectorD operator^(const VectorD& vt, int n);


// overload += operator for VectorD += VectorD
VectorD& operator+=(VectorD& vt1, const VectorD& vt2);


// overload += operator for VectorD += double
VectorD& operator+=(VectorD& vt, double n);


// overload - operator for VectorD - VectorD
VectorD operator-(const VectorD& vt1, const VectorD& vt2);


// overload / operator for VectorD / int
VectorD operator/(const VectorD& vt, double n);


// square root of VectorD
VectorD sqrt(const VectorD& vt);


// overload / operator for Matrix3D / int
Matrix3D operator/(const Matrix3D& vt, double n);


#endif /* Container_hpp */
