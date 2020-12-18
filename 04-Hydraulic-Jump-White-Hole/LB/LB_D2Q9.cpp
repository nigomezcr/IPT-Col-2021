#include "LB_D2Q9.h"

/* Initialize weights and basis vectors, allocate memory for arrays. */
LatticeBoltzmann::LatticeBoltzmann(void){
    // weights
    w[0] = 4.0/9.0;
    w[1] = w[2] = w[3] = w[4] = 1.0/9.0;
    w[5] = w[6] = w[7] = w[8] = 1.0/36.0;

    // basis vectors
    V[0][0]=0; //x
    V[1][0]=0; //y

    V[0][1]=1;   V[0][2]=0;   V[0][3]=-1;  V[0][4]=0;
    V[1][1]=0;   V[1][2]=1;   V[1][3]=0;   V[1][4]=-1;

    V[0][5]=1;   V[0][6]=-1;  V[0][7]=-1;  V[0][8]=1;
    V[1][5]=1;   V[1][6]=1;   V[1][7]=-1;  V[1][8]=-1;

    // f and f_new
    f = new double[size];
    f_new = new double[size];
}

/* Free memory */
LatticeBoltzmann::~LatticeBoltzmann(){
    delete[] f; delete[] f_new;
}

/* System density */
double LatticeBoltzmann::rho(int position){
    double r = 0; int i = 0;

    r += f[position + i]; i++;

    r += f[position + i]; i++;
    r += f[position + i]; i++;
    r += f[position + i]; i++;
    r += f[position + i]; i++;

    r += f[position + i]; i++;
    r += f[position + i]; i++;
    r += f[position + i]; i++;
    r += f[position + i];

    return r;
}

/* Velocity field in the x axis, times the density. (i.e., U_x * rho) */
double LatticeBoltzmann::Jx(int position){
    double J_x = 0; int i = 1;

    J_x += f[position + i] * V[0][i]; i++;
    J_x += f[position + i] * V[0][i]; i++;
    J_x += f[position + i] * V[0][i]; i++;
    J_x += f[position + i] * V[0][i]; i++;

    J_x += f[position + i] * V[0][i]; i++;
    J_x += f[position + i] * V[0][i]; i++;
    J_x += f[position + i] * V[0][i]; i++;
    J_x += f[position + i] * V[0][i];

    return J_x;
}

/* Velocity field in the y axis, times the density. (i.e., U_y * rho) */
double LatticeBoltzmann::Jy(int position){
    double J_y = 0; int j = 1;

    J_y += f[position+j] * V[1][j]; j++;
    J_y += f[position+j] * V[1][j]; j++;
    J_y += f[position+j] * V[1][j]; j++;
    J_y += f[position+j] * V[1][j]; j++;
    
    J_y += f[position+j] * V[1][j]; j++;
    J_y += f[position+j] * V[1][j]; j++;
    J_y += f[position+j] * V[1][j]; j++;
    J_y += f[position+j] * V[1][j];

    return J_y;
}

// Using f_new
double LatticeBoltzmann::Jx_new(int ix, int iy){
    double J_x = 0; int pos = get_1D(ix, iy);
    for(int i=0; i<Q; i++)
        J_x += f_new[pos + i] * V[0][i];
    return J_x;
}

// Using f_new
double LatticeBoltzmann::Jy_new(int ix, int iy){
    double J_y = 0; int pos = get_1D(ix, iy);
    for(int j=0; j<Q; j++)
        J_y += f_new[pos+j] * V[1][j];
    return J_y;
}
