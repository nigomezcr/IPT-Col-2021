#include "Fluids_LB_D3Q19.h"

void Fluids::collide(void){
    double rho0, Ux0, Uy0, Uz0; int pos;
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                pos = get_1D(ix, iy, iz);

                rho0 = rho(pos);
                Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0; Uz0 = Jz(pos)/rho0;
                double U2 = Ux0*Ux0 + Uy0*Uy0 + Uz0*Uz0;

                for(int i=0; i<Q; i++){
                    double UdotVi = Ux0*V[0][i] + Uy0*V[1][i] + Uz0*V[2][i];
                    f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, UdotVi, U2, i);
                }
            }
}

void Fluids::propagate(void){
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                int pos_new = get_1D(ix, iy, iz);
                    for(int i=0; i<Q; i++){
                        int x_pos = (Lx + ix + V[0][i])%Lx, y_pos = (Ly + iy + V[1][i])%Ly, z_pos = (Lz + iz + V[2][i])%Lz;
                        int pos = get_1D(x_pos, y_pos, z_pos);

                        if( // Box obstacle by halfway bounce-back
                            ((Lx3<=ix)&&(ix<T_Lx3)) && ((Ly3<=iy)&&(iy<T_Ly3)) && ((0<=iz)&&(iz<Lz2))
                        ){
                            f_new[pos + opposite_of[i]] = f_new[pos + i];
                        }
                        else{ // Fluid site
                            f[pos + i] = f_new[pos_new + i];
                        }
                    }
        }
}

void Fluids::initialize(double rho0, double Ux0, double Uy0, double Uz0){
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                int pos = get_1D(ix, iy, iz);
                double U2 = Ux0*Ux0 + Uy0*Uy0 + Uz0*Uz0;

                for(int i=0; i<Q; i++){
                    double UdotVi = Ux0*V[0][i] + Uy0*V[1][i] + Uz0*V[2][i];
                    f[pos + i] = f_eq(rho0, UdotVi, U2, i);
                }
            }
}

void Fluids::impose_fields(double v){
    int pos; double rho0;
    #pragma omp parallel for private(pos, rho0)
    for(int iy=0; iy<Ly; iy++)
        for(int iz=0; iz<Lz; iz++){
            // Wind tunnel in x
                pos = get_1D(0, iy, iz);

                rho0 = rho(pos);
                for(int i=0; i<Q; i++){
                    double UdotVi = v*V[0][i];
                    double v2 = v*v;
                    f_new[pos + i] = f_eq(rho0, UdotVi, v2, i);
                }
        }
}


void Fluids::save(std::string filename, double v){
    if(v == 0.0) std::cout << "v = 0" << std::endl;
    std::ofstream File(filename); double rho0, Ux0, Uy0, Uz0;
    for(int ix=0; ix<Lx; ix+=4){
        for(int iy=0; iy<Ly; iy+=4){
            for(int iz=0; iz<Lz; iz+=4){
                int pos = get_1D(ix, iy, iz);

                rho0 = rho(pos);
                Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0; Uz0 = Jz(pos)/rho0;
                File << ix << '\t' << iy << '\t' << iz << '\t' << 4*(Ux0)/v << '\t'
                << 4*Uy0/v << '\t' << 4*Uz0/v << '\n';
            }
            File << '\n';
        }
        File << '\n';
    }
    File << std::endl;
    File.close();
}

// Saves a 2D view from a fixed z position
void Fluids::save_2D(std::string filename, int z_pos, double v){
    if(v == 0.0) std::cout << "v = 0" << std::endl;
    std::ofstream File(filename); double rho0, Ux0, Uy0;
    for(int ix=0; ix<Lx; ix+=4){
        for(int iy=0; iy<Ly; iy+=4){
            int pos = get_1D(ix, iy, z_pos);

            rho0 = rho(pos);
            Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0;
            File << ix << '\t' << iy << '\t' << 4*(Ux0)/v << '\t' << 4*Uy0/v << '\n';
        }
        File << '\n';
    }
    File << std::endl;
    File.close();
}

void Fluids::print(double v){
    if(v == 0.0) std::cout << "v = 0" << std::endl;
    double rho0, Ux0, Uy0, Uz0;
    for(int ix=0; ix<Lx; ix+=4)
        for(int iy=0; iy<Ly; iy+=4)
            for(int iz=0; iz<Lz; iz+=4){
                int pos = get_1D(ix, iy, iz);

                rho0 = rho(pos);
                Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0; Uz0 = Jz(pos)/rho0;
                std::cout << ix << '\t' << iy << '\t' << iz << "\t\t" << 4*(Ux0)/v << '\t'
                << 4*Uy0/v << '\t' << 4*Uz0/v << '\n';
            }
    std::cout << std::endl;
}
