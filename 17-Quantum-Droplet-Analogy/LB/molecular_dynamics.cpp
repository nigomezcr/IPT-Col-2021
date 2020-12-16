#include "molecular_dynamics.h"

Body::Body(int n){
    N = n;
    g.load(0,0,6.3375e-05); // computational dl per computational dt squared
}

Collider::Collider(int n){
    N = n;
}

void Collider::calculate_all_forces(Body *molecule){
    Vector3D zero;
    for(int i=0; i<N; i++){
        molecule[i].delete_f();
        // molecule[i].interact_with_lb()
        molecule[i].add_force(zero);
    }
}

void Collider::move_with_pefrl(Body *molecule, double dt){
    int i;
    for(i=0;i<N;i++) molecule[i].move_r(dt,Zi);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,coef1);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Xi);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,Lambda);
    for(i=0;i<N;i++) molecule[i].move_r(dt,coef2);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,Lambda);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Xi);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,coef1);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Zi);
}
