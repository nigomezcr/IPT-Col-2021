#include "molecular_dynamics.h"

Body::Body(int n){
    N = n;
    g.load(0,0,7.0417e-6); // computational dl per computational dt squared
}

Collider::Collider(int n){
    N = n;
}

void Collider::calculate_force(Body &molecule, Fluids &boltzmann){
    double x = molecule.r[0], y = molecule.r[1], z = molecule.r[2], R = molecule.R, R2 = R*R;

    unsigned int x_min = x - R, x_max = x + R;
    unsigned int y_min = y - R, y_max = y + R;
    unsigned int z_min = z - R, z_max = z + R;

    if(x_min > Lxm1) x_min = 0;
    if(y_min > Lym1) y_min = 0;
    if(z_min > Lzm1) z_min = 0;

    if(x_max > Lxm1) x_max = Lxm1;
    if(y_max > Lym1) y_max = Lym1;
    if(z_max > Lzm1) z_max = Lzm1;

    double Fx = 0.0, Fy = 0.0, Fz = 0.0;

    for(int ix=x_min; ix<=x_max; ix++)
        for(int iy=y_min; iy<=y_max; iy++)
            for(int iz=z_min; iz<=z_max; iz++){
                unsigned int pos = get_1D(ix, iy, iz);

                double rho0 = boltzmann.rho(pos);

                double Ux = boltzmann.Jx(pos)/rho0;
                double Uy = boltzmann.Jy(pos)/rho0;
                double Uz = boltzmann.Jz(pos)/rho0;

                double U2 = Ux*Ux + Uy*Uy + Uz*Uz;

                double distance = (ix - x)*(ix - x) + (iy - y)*(iy - y) + (iz - z)*(iz - z);

                if(distance <= R2)
                    for(int i=0; i<Q; i++){
                        double UdotVi = Ux*boltzmann.V[0][i] + Uy*boltzmann.V[1][i] + Uz*boltzmann.V[2][i];

                        Fx += 2*(boltzmann.f[pos+i] + boltzmann.w[i]*UdotVi)*boltzmann.V[0][i];
                        Fy += 2*(boltzmann.f[pos+i] + boltzmann.w[i]*UdotVi)*boltzmann.V[1][i];
                        Fz += 2*(boltzmann.f[pos+i] + boltzmann.w[i]*UdotVi)*boltzmann.V[2][i];
                    }
            }

    Vector3D dF(Fx, Fy, Fz);
    molecule.add_force(dF);
}

void Collider::calculate_all_forces(Body *molecule, Fluids &boltzmann){
    Vector3D zero;
    for(int i=0; i<N; i++){
        molecule[i].delete_f();
        calculate_force(molecule[i], boltzmann);
    }

}

void Collider::move_with_pefrl(Body *molecule, double dt, Fluids &boltzmann){
    int i;
    for(i=0;i<N;i++) molecule[i].move_r(dt,Zi);
    calculate_all_forces(molecule, boltzmann);
    for(i=0;i<N;i++) molecule[i].move_v(dt,coef1);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Xi);
    calculate_all_forces(molecule, boltzmann);
    for(i=0;i<N;i++) molecule[i].move_v(dt,Lambda);
    for(i=0;i<N;i++) molecule[i].move_r(dt,coef2);
    calculate_all_forces(molecule, boltzmann);
    for(i=0;i<N;i++) molecule[i].move_v(dt,Lambda);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Xi);
    calculate_all_forces(molecule, boltzmann);
    for(i=0;i<N;i++) molecule[i].move_v(dt,coef1);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Zi);
}
