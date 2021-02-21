#include"branched_flow.h"

void BranchedFlow::initialize(std::string potential_file, int init_cond){
    FileHandler file(potential_file);

    if(Lx != 0 && Ly != 0){
        delete[] film;
        delete[] potential;
    }

    Lx = (int)file.content[file.get_rows()-1][0] + 1;
    Ly = (int)file.content[file.get_rows()-1][1] + 1;

    // Film

    film = new c_double[Lx*Ly];

    if(init_cond == 0){
        double sigma = Ly/100.0;
        double mu = Ly/2.0;

        for(int iy=0; iy<Ly; iy++)
            film[get_1D(0, iy)] = std::exp(-0.5*(iy-mu)*(iy-mu)/(sigma*sigma));
    }
    else if(init_cond == 1){
        for(int iy=0; iy<Ly; iy++)
            film[get_1D(0, iy)] = 1.0;
    }
    else throw ValueError();

    // Potential

    potential = new double[Lx*Ly];

    for(int i=0; i<file.get_rows(); i++){
        int ix = (int)file.content[i][0], iy = (int)file.content[i][1];
        potential[get_1D(ix, iy)] = (double)file.content[i][3];
    }
}

c_double BranchedFlow::paraxial_equation(c_double uxy, c_double uxy1, c_double uxy_1, double potential){
    return -1.0*j*C*(uxy1 - 2.0*uxy + uxy_1)*o_dy2 + j*C*potential*uxy; // *std::norm(uxy);
}

void BranchedFlow::rk4_solve(){
    for(int ix=0; ix<Lx-1; ix++){ // move information from ix to ix+1
        film[get_1D(ix, 0)] = 0.0;
        film[get_1D(ix, (Ly-1))] = 0.0;

        for(int iy=1; iy<Ly-1; iy++){
            c_double uxy_1 = film[get_1D(ix, (iy-1))];
            c_double uxy = film[get_1D(ix, iy)];
            c_double uxy1 = film[get_1D(ix, (iy+1))];
            double V = potential[get_1D(ix, iy)];

            c_double k1 = h*paraxial_equation(uxy, uxy1, uxy_1, V);
            c_double k2 = h*paraxial_equation(uxy+k1/2.0, uxy1+k1/2.0, uxy_1+k1/2.0, V);
            c_double k3 = h*paraxial_equation(uxy+k2/2.0, uxy1+k2/2.0, uxy_1+k2/2.0, V);
            c_double k4 = h*paraxial_equation(uxy+k3, uxy1+k3, uxy_1+k3, V);

            film[get_1D((ix+1), iy)] = film[get_1D(ix, iy)] + (k1 + 2.0*k2 + 2.0*k3 + k4)/6.0;
        }
    }
}

void BranchedFlow::save(std::string filename){
    std::ofstream file(filename);

    for(int ix=0; ix<Lx; ix++){
        for(int iy=0; iy<Ly; iy++)
            file << ix << ','<< iy <<',' << std::sqrt(std::norm(film[get_1D(ix, iy)])) << '\n';
        file << '\n';
    }

    file << std::endl;
    file.close();
}

BranchedFlow::~BranchedFlow(){
    delete[] film;
    delete[] potential;
}
