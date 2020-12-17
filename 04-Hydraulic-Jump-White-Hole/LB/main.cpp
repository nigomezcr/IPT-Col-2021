#include"Fluids_LB_D2Q9.h"

std::string filename(int t);

int main(void)
{
  Fluids Boltzmann;
  int t_max = 1e3;
  double rho0 = 1.0, v = 0.1;
  std::ofstream file("data.txt");

  Boltzmann.initialize(rho0, 0, 0, 0, 15, Ly-1);
  Boltzmann.save("initial.txt", v);

  std::cout << "set pm3d map " << std::endl;
  std::cout << "set xrange[0:" << Lx << "]" << std::endl;
  std::cout << "set yrange[0:" << Ly << "]" << std::endl;
  //std::cout << "set cbrange[0:10]" << std::endl;
  for(int t=0; t<t_max; t++){
    Boltzmann.collide();
    Boltzmann.impose_fields(v);
    Boltzmann.propagate();
    file << t << '\t' << Boltzmann.detector(75) << '\n';
    if(t%4 == 0){
      Boltzmann.save("my_data.txt", v);
      std::cout << "set title '" << t << "'" << std::endl;
      std::cout << "splot 'my_data.txt' u 1:2:($3*$3 + $4*$4) notitle " << std::endl;
    }
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
