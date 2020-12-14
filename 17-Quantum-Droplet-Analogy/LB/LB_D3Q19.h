#ifndef __LB_CPP_LB_D3Q19_H
#define __LB_CPP_LB_D3Q19_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

// Geometry
#define Lx 200  // dx = 0.5mm
#define Ly 200  // dy = 0.5mm
#define Lz 30  // dz = 0.5mm, liquid: 20 cells, 10mm
#define D 3
#define Q 19

// mini obstacle 8mm

#define Lxm1 199
#define Lym1 199
#define Lzm1 29

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
        double Jz(int position);
        double Jx_new(int ix, int iy, int iz);
        double Jy_new(int ix, int iy, int iz);
        double Jz_new(int ix, int iy, int iz);
};

#endif