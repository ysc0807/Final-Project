
#include "Container.hpp"


VectorD operator+(const VectorD& vt1, const VectorD& vt2) {
    VectorD res(vt1.size());
    for (size_t i = 0; i < vt1.size(); i++)
        res[i] = vt1[i] + vt2[i];
    return res;
}


VectorD operator^(const VectorD& vt, int n) {
    VectorD res(vt.size());
    for (size_t i = 0; i < vt.size(); i++)
        res[i] = std::pow(vt[i], n);
    return res;
}


VectorD& operator+=(VectorD& vt1, const VectorD& vt2) {
    for (size_t i = 0; i < vt1.size(); i++)
        vt1[i] += vt2[i];
    return vt1;
}


VectorD operator-(const VectorD& vt1, const VectorD& vt2) {
    VectorD res(vt1.size());
    for (size_t i = 0; i < vt1.size(); i++)
        res[i] = vt1[i] - vt2[i];
    return res;
}


VectorD& operator+=(VectorD& vt, double n) {
    for (size_t i = 0; i < vt.size(); i++)
        vt[i] += n;
    return vt;
}


VectorD operator/(const VectorD& vt, double n) {
    VectorD res(vt.size());
    for (size_t i = 0; i < vt.size(); i++)
        res[i] = vt[i] / n;
    return res;
}


VectorD sqrt(const VectorD& vt) {
    VectorD res(vt.size());
    for (size_t i = 0; i < vt.size(); i++)
        res[i] = std::sqrt(vt[i]);
    return res;
}


Matrix3D operator/(const Matrix3D& mt, double n) {
    Matrix3D res(mt.size(), Matrix2D(mt[0].size()));
    for (int i=0; i<(int)mt.size(); i++)
        for (int j=0; j<(int)mt[0].size(); j++)
            res[i][j] = mt[i][j] / n;
    return res;
}
