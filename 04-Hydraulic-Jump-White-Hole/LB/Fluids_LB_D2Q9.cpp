#include "Fluids_LB_D2Q9.h"

#define R Lx/8

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
  R_jet = R0;
  H_water = H0;
  int pos;
  double U2, UdotVi;
  for(int ix=0; ix<Lx; ix++){
    for(int iy=H_water; iy<Ly; iy++){
      pos = get_1D(ix, iy);
      U2 = Ux0*Ux0 + Uy0*Uy0;

      for(int i=0; i<Q; i++){
	UdotVi = Ux0*V[0][i] + Uy0*V[1][i];
	f[pos + i] = f_eq(rho0*0.1, UdotVi, U2, i);
      }
    }
  }

  for(unsigned int ix=(0.5*Lx - R_jet); ix<(0.5*Lx + R_jet); ix++){
    for(unsigned int iy=H_water; iy<Ly; iy++){
      pos = get_1D(ix, iy);
      U2 = Ux0*Ux0 + Uy0*Uy0;

      for(int i=0; i<Q; i++){
	UdotVi = Ux0*V[0][i] + Uy0*V[1][i];
	f[pos + i] = f_eq(rho0, UdotVi, U2, i);
      }
    }
  }

  for(unsigned int ix=0; ix<Lx; ix++){
    for(unsigned int iy=0; iy<H_water; iy++){
      pos = get_1D(ix, iy);
      U2 = Ux0*Ux0 + Uy0*Uy0;

      for(int i=0; i<Q; i++){
	UdotVi = Ux0*V[0][i] + Uy0*V[1][i];
	f[pos + i] = f_eq(rho0, UdotVi, U2, i);
      }
    }
  }
}

void Fluids::impose_fields(double v){
  int pos; double rho0;
#pragma omp parallel for private(pos, rho0)
  for(unsigned int ix=(0.5*Lx - R_jet); ix<(0.5*Lx + R_jet); ix++){
    for(unsigned int iy=Ly-3; iy<Ly; iy++){
      pos = get_1D(ix, iy);

      rho0 = rho(pos);
      for(int i=0; i<Q; i++){
	double UdotVi = v*V[1][i];
	f_new[pos + i] = f_eq(rho0, UdotVi, v*v, i);
      }
    }
  }
}

/* Fluid density on a given position */
double Fluids::detector(int x_pos){
  double rho0 = 0;
  for(int iy=0; iy<Ly; iy++){
    int pos = get_1D(x_pos, iy);
    rho0 += rho(pos);
  }
  return rho0;
}


void Fluids::save(std::string filename, double v){
  if(v == 0.0) std::cout << "v = 0" << std::endl;
  std::ofstream File(filename); double rho0, Ux0, Uy0, Uz0;
  for(int ix=0; ix<Lx; ix+=4){
    for(int iy=0; iy<Ly; iy+=1){
      int pos = get_1D(ix, iy);

      rho0 = rho(pos);
      Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0;
      File << ix << '\t' << iy << '\t' << 4*(Ux0)/v << '\t' << 4*Uy0/v << '\n';// rho0 << '\n';//4*(Ux0)/v << '\t'
      //<< 4*Uy0/v << '\t' << '\n';
    }
    File << '\n';
  }
  File << std::endl;
  File.close();
}

void Fluids::print(double v){
  if(v == 0.0) std::cout << "v = 0" << std::endl;
  double rho0, Ux0, Uy0, Uz0;
  for(int ix=0; ix<Lx; ix+=4){
    for(int iy=0; iy<Ly; iy+=4){
      int pos = get_1D(ix, iy);
      
      rho0 = rho(pos);
      Ux0 = Jx(pos)/rho0; Uy0 = Jy(pos)/rho0;
      std::cout << ix << '\t' << iy << '\t' << "\t\t" << 4*(Ux0)/v << '\t'
		<< 4*Uy0/v << '\t' << '\n';
    }
    std::cout << std::endl;
  }
}
