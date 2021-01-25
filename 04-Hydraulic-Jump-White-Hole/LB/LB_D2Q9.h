#ifndef __LB_CPP_LB_D2Q9_H
#define __LB_CPP_LB_D2Q9_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>

// Geometry
#define Lx 300
#define Ly 10
#define D 2
#define Q 9

#define Lxm1 (Lx-1)
#define Lym1 (Ly-1)

#define jet_min 135
#define jet_max 165

// #define jet_min 4
// #define jet_max 6

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
#define Utau 1.81818181818182
#define UmUtau (-0.81818181818182)

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
