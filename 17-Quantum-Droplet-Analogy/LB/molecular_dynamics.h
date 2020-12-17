#ifndef __3_BODY_PROBLEM_MOLECULAR_DYNAMICS_H
#define __3_BODY_PROBLEM_MOLECULAR_DYNAMICS_H

#include<iostream>
#include<cmath>
#include<fstream>

#include "vector3D.h"
#include "Fluids_LB_D3Q19.h"

class Fluids;

// PEFRL
const double Zi = 0.1786178958448091e0;
const double Lambda = 0.2123418310626054*(-1);
const double Xi = 0.06626458266981849*(-1);

const double coef1 = (1 - 2*Lambda)/2;
const double coef2 = (1 - 2*(Xi+Zi));


class Body{
    private:
        int N; Vector3D r, V, F; double m, R;

        // Helpers
        Vector3D g;
    public:
        Body(int =0);

        void initialize(double x0, double y0, double z0, 
            double Vx0, double Vy0, double Vz0, 
            double m0, double R0
        ){r.load(x0,y0,z0); V.load(Vx0,Vy0,Vz0); m = m0; R = R0;}
        void add_force(Vector3D dF){F += dF - m*g;}
        void move_r(double dt, double coef){r += V*(dt*coef);}
        void move_v(double dt, double coef){V += F*(dt*coef/m);}
        void delete_f(void){F.load(0,0,0);}

        double get_x(void){return r[0];}
        double get_y(void){return r[1];}
        double get_z(void){return r[2];}

        double get_vx(void){return V[0];}
        double get_vy(void){return V[1];}
        double get_vz(void){return V[2];}

        double get_fx(void){return F[0];}
        double get_fy(void){return F[1];}
        double get_fz(void){return F[2];}

        double kinetic(void){return 0.5*m*vec3d::norm2(V);}

        friend class Collider;
        friend class Fluids;
};

class Collider{
    private:
        int N;
    public:
        Collider(int =0);
        void calculate_force(Body &molecule, Fluids &boltzmann);
        void calculate_all_forces(Body *molecule, Fluids &boltzmann);
        void move_with_pefrl(Body *molecule, double dt, Fluids &boltzmann);
};

#endif
