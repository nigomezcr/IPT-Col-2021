#ifndef __VECTOR3D_H
#define __VECTOR3D_H
/**
 * 3D Vector helper class.
 * Author : Juan Vanegas. Git: jpvanegasc
 */
#include <iostream>
#include <cmath>


class Vector3D;

Vector3D operator* (double a, Vector3D v);

namespace vec3d{
    Vector3D unit_vector(Vector3D v);
    double norm2(Vector3D v);
    double norm(Vector3D v);
}

class Vector3D{
    double v[3];
    public:
        Vector3D(double =0.0, double =0.0, double =0.0);
        void load(double x0, double y0, double z0){v[0] = x0; v[1] = y0; v[2] = z0;}
        void show(void);
        /* @return x component*/
        double x(void){return v[0];};
        /* @return y component*/
        double y(void){return v[1];};
        /* @return z component*/
        double z(void){return v[2];};
        /* @return nth component*/
        double & operator[](int n){return v[n];};
        Vector3D operator= (Vector3D v2);
        Vector3D operator+ (Vector3D v2);
        Vector3D operator+=(Vector3D v2);
        Vector3D operator- (Vector3D v2);
        Vector3D operator-=(Vector3D v2);
        Vector3D operator* (double a);
        Vector3D operator*=(double a);
        Vector3D operator/ (double a);
        double operator* (Vector3D v2);
        Vector3D operator^ (Vector3D v2);

        friend Vector3D operator* (double a, Vector3D v);
        friend Vector3D vec3d::unit_vector(Vector3D v);
        friend double vec3d::norm2(Vector3D v);
        friend double vec3d::norm(Vector3D v);
};

#endif
