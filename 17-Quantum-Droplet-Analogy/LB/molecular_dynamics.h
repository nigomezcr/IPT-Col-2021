#ifndef __3_BODY_PROBLEM_MOLECULAR_DYNAMICS_H
#define __3_BODY_PROBLEM_MOLECULAR_DYNAMICS_H

#include<iostream>
#include<cmath>
#include<fstream>

#include"vector3D.h"

// Gravity
const double G = 8.88769165499824e-10; //  AU3 / (d2 earthMass)

// PEFRL
const double Zi = 0.1786178958448091e0;
const double Lambda = 0.2123418310626054*(-1);
const double Xi = 0.06626458266981849*(-1);

const double coef1 = (1 - 2*Lambda)/2;
const double coef2 = (1 - 2*(Xi+Zi));


class Body{
    private:
        int N; Vector3D r, V, F; double m, R;
    public:
        Body(int =0);
        void initialize(double x0, double y0, double z0, double Vx0, double Vy0, double Vz0, double m, double R);
        void print(void);
        void add_force(Vector3D dF){F += dF;}
        void move_r(double dt, double coef){r += V*(dt*coef);}
        void move_v(double dt, double coef){V += F*(dt*coef/m);}
        void delete_f(void){F.load(0,0,0);}
        double get_x(void){return r.x();} 
        double get_y(void){return r.y();} 
        double get_z(void){return r.z();} 
        double get_vx(void){return V.x();} 
        double get_vy(void){return V.y();} 
        double get_fx(void){return F.x();} 
        double get_fy(void){return F.y();}

        friend class Collider;
};

class Collider{
    private:
        int N;
    public:
        Collider(int =0);
        void calculate_force_pair(Body &molecule1, Body &molecule2);
        void calculate_all_forces(Body *molecule);
        void move_with_pefrl(Body *molecule, double dt);
        double energy(Body *molecule);
        double angular_momentum(Body molecule, double x_axis=0.0, double y_axis=0.0, double z_axis=0.0);
};

#endif
