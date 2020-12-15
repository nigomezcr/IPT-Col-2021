#include"Fluids_LB_D2Q9.h"
//#include"Diffusion_LB_D2Q9.h"

std::string filename(int t);

int main(void){
  Fluids Boltzmann;
  //Diffusion Boltzmann;
  int t_max = 1000;
  double rho0 = 1.0, v = 0.1;
  std::ofstream file("data.txt");
  
  Boltzmann.initialize(rho0, 0, 0, 0);
  Boltzmann.save("initial.txt", v);
  
  for(int t=0; t<t_max; t++){
    Boltzmann.collide();
    Boltzmann.impose_fields(v);
    Boltzmann.propagate();
    file << t << '\t' << Boltzmann.detector(75) << '\n';
    //file << t << '\t' << Boltzmann.sigmax2() << '\n';
  }
  file.close();
  
  Boltzmann.save("final.txt", v);

  return 0;
}

std::string filename(int t){
  std::string name; std::stringstream t_s; t_s << t;
  name = t_s.str() + ".txt";
  return name;
}
