#include "Fluids_LB_D2Q9.h"


void Fluids::collide(void){
    double rho0, Ux0, Uy0, Uz0; int pos;
    for(int ix=0; ix<Lx; ix++){
        for(int iy=0; iy<Ly; iy++){
            pos = get_1D(ix, iy);

            rho0 = rho(pos);
            Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0;
            double U2 = Ux0*Ux0 + Uy0*Uy0;

            for(int i=0; i<Q; i++){
    double UdotVi = Ux0*V[0][i] + Uy0*V[1][i];
    f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, UdotVi, U2, i);
            }
        }
    }
}

void Fluids::propagate(void){
    for(int ix=1; ix<Lx-1; ix++){
        for(int iy=0; iy<Ly-1; iy++){
            int pos_new = get_1D(ix, iy);
            for(int i=0; i<Q; i++){
    int x_pos = (ix + V[0][i]), y_pos = (iy + V[1][i]);
    int pos = get_1D(x_pos, y_pos);

    if(y_pos < 0){
        f_new[pos_new + opposite_of[i]] = f[pos_new + i];
    }
    else{
        f[pos + i] = f_new[pos_new + i];
    }
            }
        }
    }
}

void Fluids::initialize(double rho0, double Ux0, double Uy0, double Uz0, double R0, double H0){
    // pass
}

void Fluids::save(std::string filename){
    std::ofstream File(filename); double rho0, Ux0, Uy0, Uz0;
    for(int ix=0; ix<Lx; ix+=4){
        for(int iy=0; iy<Ly; iy+=1){
            int pos = get_1D(ix, iy);

            rho0 = rho(pos);
            Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0;
            File << ix << ',' << iy << ',' << 4*Ux0 << ',' << 4*Uy0 <<  rho0 << '\n';
        }
        File << '\n';
    }
    File << std::endl;
    File.close();
}
