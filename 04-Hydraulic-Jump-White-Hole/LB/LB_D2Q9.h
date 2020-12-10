#ifndef __LB_CPP_LB_D2Q9_H
#define __LB_CPP_LB_D2Q9_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

// Geometry
#define Lx 256
#define Ly 64
#define D 2
#define Q 9

// Obstacle
#define Lx3 (Lx/3)
#define Ly3 (Ly/3)

#define T_Lx3 (2*Lx/3)
#define T_Ly3 (2*Ly/3)

// 2D to 1D
#define size (Lx*Ly*Q)
#define x_mult (Ly*Q)
#define y_mult Q

/**
 * Transform from 2D notation to 1D notation 
 * @return 1D macro-coordinate on array
 */
#define get_1D(ix, iy) ((ix*x_mult) + (iy*y_mult))

// LB constants
#define tau 0.55
#define Utau (1.0/tau)
#define UmUtau (1.0-Utau)

class LatticeBoltzmann{
    protected:
        double w[Q]; int V[D][Q];
        double *f = NULL, *f_new = NULL;
    public:
        LatticeBoltzmann(void);
        ~LatticeBoltzmann();
        double rho(int position);
        double Jx(int position);
        double Jy(int position);
        double Jx_new(int ix, int iy);
        double Jy_new(int ix, int iy);
};

#endif