#include "LB_D3Q19.h"

/* Initialize weights and basis vectors, allocate memory for arrays. */
LatticeBoltzmann::LatticeBoltzmann(void){
    // weights
    w[0] = 1.0/3.0;
    w[1] = w[2] = w[3] = w[4] = w[5] = w[6] = 1.0/18.0;
    w[7] = w[8] = w[9] = w[10] = w[11] = w[12] = 1.0/36.0;
    w[13] = w[14] = w[15] = w[16] = w[17] = w[18] = 1.0/36.0;

    // basis vectors
    V[0][0]=0; //x
    V[1][0]=0; //y
    V[2][0]=0; //z

    V[0][1]=1;   V[0][2]=-1;  V[0][3]=0;   V[0][4]=0;   V[0][5]=0;   V[0][6]=0;
    V[1][1]=0;   V[1][2]=0;   V[1][3]=1;   V[1][4]=-1;  V[1][5]=0;   V[1][6]=0;
    V[2][1]=0;   V[2][2]=0;   V[2][3]=0;   V[2][4]=0;   V[2][5]=1;   V[2][6]=-1;

    V[0][7]=1;   V[0][8]=-1;  V[0][9]=1;   V[0][10]=-1;  V[0][11]=0;   V[0][12]=0;
    V[1][7]=1;   V[1][8]=-1;  V[1][9]=0;   V[1][10]=0;   V[1][11]=1;   V[1][12]=-1;
    V[2][7]=0;   V[2][8]=0;   V[2][9]=1;   V[2][10]=-1;  V[2][11]=1;   V[2][12]=-1;

    V[0][13]=1;   V[0][14]=-1;  V[0][15]=1;   V[0][16]=-1;  V[0][17]=0;   V[0][18]=0;
    V[1][13]=-1;  V[1][14]=1;   V[1][15]=0;   V[1][16]=0;   V[1][17]=1;   V[1][18]=-1;
    V[2][13]=0;   V[2][14]=0;   V[2][15]=-1;  V[2][16]=1;   V[2][17]=-1;  V[2][18]=1;

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
    double r = 0;

    r += f[position + 0];

    r += f[position + 1];
    r += f[position + 2];
    r += f[position + 3];
    r += f[position + 4];
    r += f[position + 5];
    r += f[position + 6];

    r += f[position + 7];
    r += f[position + 8];
    r += f[position + 9];
    r += f[position + 10];
    r += f[position + 11];
    r += f[position + 12];

    r += f[position + 13];
    r += f[position + 14];
    r += f[position + 15];
    r += f[position + 16];
    r += f[position + 17];
    r += f[position + 18];

    return r;
}

/* Velocity field in the x axis, times the density. (i.e., U_x * rho) */
double LatticeBoltzmann::Jx(int position){
    double J_x = 0;

    J_x += f[position + 1];
    J_x -= f[position + 2];

    J_x += f[position + 7];
    J_x -= f[position + 8];
    J_x += f[position + 9];
    J_x -= f[position + 10];

    J_x += f[position + 13];
    J_x -= f[position + 14];
    J_x += f[position + 15];
    J_x -= f[position + 16];

    return J_x;
}

/* Velocity field in the y axis, times the density. (i.e., U_y * rho) */
double LatticeBoltzmann::Jy(int position){
    double J_y = 0;

    J_y += f[position + 3];
    J_y -= f[position + 4];

    J_y += f[position + 7];
    J_y -= f[position + 8];

    J_y += f[position + 11];
    J_y -= f[position + 12];
    J_y -= f[position + 13];
    J_y += f[position + 14];

    J_y += f[position + 17];
    J_y -= f[position + 18];

    return J_y;
}

/* Velocity field in the z axis, times the density. (i.e., U_z * rho) */
double LatticeBoltzmann::Jz(int position){
    double J_z = 0;

    J_z += f[position + 5];
    J_z -= f[position + 6];

    J_z += f[position + 9];
    J_z -= f[position + 10];
    J_z += f[position + 11];
    J_z -= f[position + 12];

    J_z -= f[position + 15];
    J_z += f[position + 16];
    J_z -= f[position + 17];
    J_z += f[position + 18];

    return J_z;
}
// Using f_new
double LatticeBoltzmann::Jx_new(int ix, int iy, int iz){
    double J_x = 0; int pos = get_1D(ix, iy, iz);
    for(int i=0; i<Q; i++)
        J_x += f_new[pos + i] * V[0][i];
    return J_x;
}

// Using f_new
double LatticeBoltzmann::Jy_new(int ix, int iy, int iz){
    double J_y = 0; int pos = get_1D(ix, iy, iz);
    for(int j=0; j<Q; j++)
        J_y += f_new[pos+j] * V[1][j];
    return J_y;
}

// Using f_new
double LatticeBoltzmann::Jz_new(int ix, int iy, int iz){
    double J_z = 0; int pos = get_1D(ix, iy, iz);
    for(int k=0; k<Q; k++)
        J_z += f_new[pos+k] * V[2][k];
    return J_z;
}
