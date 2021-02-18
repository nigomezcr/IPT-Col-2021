#include"branched_flow.h"

void BranchedFlow::initialize(std::string potential_file){
    FileHandler file(potential_file);

    int Lx_new = (int)file.content[file.get_rows()-1][0] + 1;
    int Ly_new = (int)file.content[file.get_rows()-1][1] + 1;

    potential = file.content;

    if(Lx != 0 && Ly != 0){
        delete[] film;
    }

    film = new c_double[Lx_new*Ly_new];

    Lx = Lx_new; Ly = Ly_new;
}

c_double BranchedFlow::paraxial_equation(c_double uxy, c_double uxy1, c_double uxy_1, double potential){
    c_double derivative = (uxy1 - 2.0*uxy + uxy_1)/(dx*dx);

    return j*C*derivative + j*C*potential*uxy*std::norm(uxy);
}

void BranchedFlow::rk4_solve(){
    for(int ix=0; ix<Lx-1; ix++){ // move information from ix to ix+1
        film[get_1D(ix, 0)] = 0.0;
        film[get_1D(ix, Ly-1)] = 0.0;

        for(int iy=1; iy<Ly-1; iy++){
            c_double uxy_1 = film[get_1D(ix, iy-1)];
            c_double uxy = film[get_1D(ix, iy)];
            c_double uxy1 = film[get_1D(ix, iy+1)];
            double V = 1.0; //potential[ix][iy];

            c_double k1 = h*paraxial_equation(uxy, uxy1, uxy_1, V);
            c_double k2 = h*paraxial_equation(uxy+k1/2.0, uxy1+k1/2.0, uxy_1+k1/2.0, V);
            c_double k3 = h*paraxial_equation(uxy+k2/2.0, uxy1+k2/2.0, uxy_1+k2/2.0, V);
            c_double k4 = h*paraxial_equation(uxy+k3, uxy1+k3, uxy_1+k3, V);

            film[get_1D((ix+1), iy)] = film[get_1D(ix, iy)] + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
        }
    }
}

BranchedFlow::~BranchedFlow(){
    delete[] film;
}
