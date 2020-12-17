#include "Fluids_LB_D3Q19.h"

void Fluids::collide(double t, Body *drops, int N){
    double g_cos_t = gamma*std::cos(omega*t);

    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){
            for(int iz=0; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                double rho0 = rho(pos);
                double Urho0 = 1.0/rho0;

                double Ux = Jx(pos)*Urho0;
                double Uy = Jy(pos)*Urho0;
                double Uz = (Jz(pos)*Urho0) + 0.5*g_cos_t*Urho0;

                double Fx = 0.0;
                double Fy = 0.0;
                double Fz = g_cos_t*rho0;

                if(is_fluid(drops, ix, iy, iz, N) == false)
                    for(int i=0; i<N; i++){
                        Ux += drops[i].V[0]*0.5*Urho0;
                        Uy += drops[i].V[1]*0.5*Urho0;
                        Uz += drops[i].V[2]*0.5*Urho0;

                        Fx += drops[i].F[0]*rho0;
                        Fy += drops[i].F[1]*rho0;
                        Fz += drops[i].F[2]*rho0;
                    }

                double U2 = Ux*Ux + Uy*Uy + Uz*Uz;
                double UdotF = Ux*Fx + Uy*Fy + Uz*Fz;

                double S0 = UmU2tau*(w[0]/c_s2)*(-UdotF);

                f_new[pos] = UmUtau*f[pos] + Utau*f_eq(rho0, 0.0, U2, 0) + S0;

                for(int i=1; i<Q; i++){
                    double UdotVi = Ux*V[0][i] + Uy*V[1][i] + Uz*V[2][i];
                    double FdotVi = Fx*V[0][i] + Fy*V[1][i] + Fz*V[2][i];

                    double Si = UmU2tau*(w[i]/c_s2)*( FdotVi + (FdotVi*UdotVi - c_s2*UdotF)/c_s2 );

                    f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, UdotVi, U2, i) + Si;
                }
            }
        }
}

void Fluids::propagate(Body *drops, int N){
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++){
                    unsigned int x = ix + V[0][i];
                    unsigned int y = iy + V[1][i];
                    unsigned int z = iz + V[2][i];

                    if( // Walls & drops
                        (x > Lxm1) || (y > Lym1) || (z > Lzm1)
                        //|| (is_fluid(drops, x, y, z, N) == false)
                    ){
                        f_new[pos + opposite_of[i]] = f[pos+i];
                    }
                    else{ // Fluid site
                        unsigned int streamed_pos = get_1D(x, y, z);
                        f[streamed_pos + i] = f_new[pos + i];
                    }
                }
            }
}

bool Fluids::is_fluid(Body *drops, int x, int y, int z, int N){
    // For now I'll assume that all drops have the same radius
    double R = drops[0].R + dl, r = 4.0*R/5.0, R2 = R*R, r2 = r*r;

    for(int i=0; i<N; i++){
        double value = (x-drops[i].r[0])*(x-drops[i].r[0])
            + (y-drops[i].r[1])*(y-drops[i].r[1])
            + (z-drops[i].r[2])*(z-drops[i].r[2]);
        if(
            (value <= R2)
        )
            return false;
    }
    return true;
}

// Initialize population using the Mei  et al. scheme
void Fluids::initialize(Body *drops, int N){
    #define V0 0.0
    #define rho0 1.0
    #define top 1

    // Load initial density
    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++){
            for(int iz=0; iz<Lz-top; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, V0, V0, i);
            }
            #undef rho0
            #define rho0 0.5
            for(int iz=Lz-top; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++) f[pos + i] = f_eq(rho0, V0, V0, i);
            }
        }
    #undef rho0

    // Collide & propagate just the density
    #define STEPS 10
    for(int t=0; t<STEPS; t++){
        for(unsigned int pos=0; pos<size; pos+=Q){
            double rho0 = rho(pos);

            for(int i=0; i<Q; i++) f_new[pos + i] = UmUtau*f[pos + i] + Utau*f_eq(rho0, V0, V0, i);
        }
        propagate(drops, N);
    }
    #undef V0
    #undef STEPS
}


void Fluids::save(std::string filename){
    std::ofstream file(filename);

    for(int ix=0; ix<Lx; ix+=4){
        for(int iy=0; iy<Ly; iy+=4){
            for(int iz=0; iz<Lz; iz+=4){
                unsigned int pos = get_1D(ix, iy, iz);

                double rho0 = rho(pos);
                double Ux = Jx(pos)/rho0, Uy = Jy(pos)/rho0, Uz = Jz(pos)/rho0;

                file << ix << ',' << iy << ',' << iz << ',' << 4*Ux << ','
                << 4*Uy << ',' << 4*Uz << '\n';
            }
            file << '\n';
        }
        file << '\n';
    }

    file.close();
}

// Saves a 2D view from a fixed x position
void Fluids::save_2D(std::string filename, int x_pos){
    std::ofstream file(filename);

    for(int iy=0; iy<Ly; iy++){
        for(int iz=0; iz<Lz; iz++){
            unsigned int pos = get_1D(x_pos, iy, iz);

            double rho0 = rho(pos);
            double Uy = Jy(pos)/rho0;
            double Uz = Jz(pos)/rho0;

            file << iy << ',' << iz << ',' << 10*Uy << ',' << 10*Uz << ',' << rho0 << '\n';
        }
        file << '\n';
    }

    file.close();
}

