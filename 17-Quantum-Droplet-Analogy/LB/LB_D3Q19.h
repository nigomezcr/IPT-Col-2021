#ifndef __LB_CPP_LB_D3Q19_H
#define __LB_CPP_LB_D3Q19_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

// Geometry
#define Lx 280  // dx = 0.25mm
#define Ly 280  // dy = 0.25mm
#define Lz 16  // dz = 0.25mm
#define D 3
#define Q 19

#define dl 0.25

// mini obstacle 8mm

#define Lxm1 279
#define Lym1 279
#define Lzm1 15

// 3D to 1D
#define size (Lx*Ly*Lz*Q)
#define x_mult (Ly*Lz*Q)
#define y_mult (Lz*Q)
#define z_mult Q

/**
 * Transform from 3D notation to 1D notation 
 * @return 1D macro-coordinate on array
 */
#define get_1D(ix, iy, iz) ((ix*x_mult) + (iy*y_mult) + (iz*z_mult))

// LB constants
#define tau 0.6
#define Utau 1.6666666666
#define UmUtau (-0.6666666666)

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
        double Jz(int position);
        double Jx_new(int ix, int iy, int iz);
        double Jy_new(int ix, int iy, int iz);
        double Jz_new(int ix, int iy, int iz);
};

#endif