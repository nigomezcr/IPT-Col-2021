#include "Fluids_LB_D3Q19.h"

void Fluids::collide(const double t, const double *r, const double *v, const double *F, const double R, int N){
    double g_cos_t = gamma*std::cos(omega*t), R2 = R*R;

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

                // Is Fluid calculation
                bool is_fluid = true;

                for(int i=0; i<N; i+=3){
                    double value = (ix-r[i])*(ix-r[i]) + (iy-r[i+1])*(iy-r[i+1]) + (iz-r[i+2])*(iz-r[i+2]);
                    if(
                        (value <= R2)
                    ){
                        is_fluid = false;
                        break;
                    }
                }
                // ======

                if(is_fluid == false)
                    for(int i=0; i<N; i+=3){
                        Ux += v[i]*0.5*Urho0;
                        Uy += v[i+1]*0.5*Urho0;
                        Uz += v[i+2]*0.5*Urho0;

                        Fx += F[i]*rho0;
                        Fy += F[i+1]*rho0;
                        Fz += F[i+2]*rho0;
                    }

                double U2 = Ux*Ux + Uy*Uy + Uz*Uz;
                double UdotF = Ux*Fx + Uy*Fy + Uz*Fz;

                f_new[pos] = UmUtau*f[pos] + Utau*f_eq(rho0, 0.0, U2, 0) + UmU2tau*w[0]*3.0*(-UdotF);

                // ==========

                double UdotVi = Ux;
                double FdotVi = Fx;

                double Si = UmU2tau*w[1]*3.0*( FdotVi + 3.0*FdotVi*Ux - UdotF );

                f_new[pos + 1] = UmUtau*f[pos + 1] + Utau*f_eq(rho0, UdotVi, U2, 1) + Si; 


                UdotVi = -Ux;
                FdotVi = -Fx;

                Si = UmU2tau*w[2]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 2] = UmUtau*f[pos + 2] + Utau*f_eq(rho0, UdotVi, U2, 2) + Si; 


                UdotVi = Uy;
                FdotVi = Fy;

                Si = UmU2tau*w[3]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 3] = UmUtau*f[pos + 3] + Utau*f_eq(rho0, UdotVi, U2, 3) + Si;
                // ======

                // ==========

                UdotVi = -Uy;
                FdotVi = -Fy;

                Si = UmU2tau*w[4]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 4] = UmUtau*f[pos + 4] + Utau*f_eq(rho0, UdotVi, U2, 4) + Si; 


                UdotVi = Uz;
                FdotVi = Fz;

                Si = UmU2tau*w[5]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 5] = UmUtau*f[pos + 5] + Utau*f_eq(rho0, UdotVi, U2, 5) + Si; 


                UdotVi = -Uz;
                FdotVi = -Fz;

                Si = UmU2tau*w[6]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 6] = UmUtau*f[pos + 6] + Utau*f_eq(rho0, UdotVi, U2, 6) + Si; 
                // ======

                // ==========

                UdotVi = Ux + Uy;
                FdotVi = Fx + Fy;

                Si = UmU2tau*w[7]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 7] = UmUtau*f[pos + 7] + Utau*f_eq(rho0, UdotVi, U2, 7) + Si; 


                UdotVi = -Ux - Uy;
                FdotVi = -Fx - Fy;

                Si = UmU2tau*w[8]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 8] = UmUtau*f[pos + 8] + Utau*f_eq(rho0, UdotVi, U2, 8) + Si; 


                UdotVi = Ux + Uz;
                FdotVi = Fx + Fz;

                Si = UmU2tau*w[9]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 9] = UmUtau*f[pos + 9] + Utau*f_eq(rho0, UdotVi, U2, 9) + Si; 
                // ======

                // ==========

                UdotVi = -Ux - Uz;
                FdotVi = -Fx - Fz;

                Si = UmU2tau*w[10]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 10] = UmUtau*f[pos + 10] + Utau*f_eq(rho0, UdotVi, U2, 10) + Si; 


                UdotVi = Uy + Uz;
                FdotVi = Fy + Fz;

                Si = UmU2tau*w[11]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 11] = UmUtau*f[pos + 11] + Utau*f_eq(rho0, UdotVi, U2, 11) + Si; 


                UdotVi = -Uy - Uz;
                FdotVi = -Fy - Fz;

                Si = UmU2tau*w[12]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 12] = UmUtau*f[pos + 12] + Utau*f_eq(rho0, UdotVi, U2, 12) + Si; 
                // ======

                // ==========

                UdotVi = Ux - Uy;
                FdotVi = Fx - Fy;

                Si = UmU2tau*w[13]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 13] = UmUtau*f[pos + 13] + Utau*f_eq(rho0, UdotVi, U2, 13) + Si; 


                UdotVi = -Ux + Uy;
                FdotVi = -Fx + Fy;

                Si = UmU2tau*w[14]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 14] = UmUtau*f[pos + 14] + Utau*f_eq(rho0, UdotVi, U2, 14) + Si; 


                UdotVi = Ux - Uz;
                FdotVi = Fx - Fz;

                Si = UmU2tau*w[15]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 15] = UmUtau*f[pos + 15] + Utau*f_eq(rho0, UdotVi, U2, 15) + Si; 
                // ======

                // ==========

                UdotVi = -Ux + Uz;
                FdotVi = -Fx + Fz;

                Si = UmU2tau*w[16]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 16] = UmUtau*f[pos + 16] + Utau*f_eq(rho0, UdotVi, U2, 16) + Si; 


                UdotVi = Uy - Uz;
                FdotVi = Fy - Fz;

                Si = UmU2tau*w[17]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 17] = UmUtau*f[pos + 17] + Utau*f_eq(rho0, UdotVi, U2, 17) + Si; 


                UdotVi = -Uy + Uz;
                FdotVi = -Fy + Fz;

                Si = UmU2tau*w[18]*3.0*( FdotVi + 3.0*FdotVi*UdotVi - UdotF );

                f_new[pos + 18] = UmUtau*f[pos + 18] + Utau*f_eq(rho0, UdotVi, U2, 18) + Si; 
                // ======
            }
        }
}

void Fluids::propagate(const double *r, const double R, int N){
    double R2 = R*R;

    for(int ix=0; ix<Lx; ix++)
        for(int iy=0; iy<Ly; iy++)
            for(int iz=0; iz<Lz; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                for(int i=0; i<Q; i++){
                    unsigned int x = ix + V[0][i];
                    unsigned int y = iy + V[1][i];
                    unsigned int z = iz + V[2][i];

                    // Is Fluid calculation
                    bool is_fluid = true;

                    for(int i=0; i<N; i+=3){
                        double value = (x-r[i])*(x-r[i]) + (y-r[i+1])*(y-r[i+1]) + (z-r[i+2])*(z-r[i+2]);
                        if(
                            (value <= R2)
                        ){
                            is_fluid = false;
                            break;
                        }
                    }
                    // ======

                    if( // Walls & drops
                        (x > Lxm1) || (y > Lym1) || (z > Lzm1) || (is_fluid == false)
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

bool Fluids::is_it_fluid(Body *drops, int x, int y, int z, int N){
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
void Fluids::initialize(const double *r, const double R, int N){
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
        propagate(r, R, N);
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

