#include "system.hpp"
#include <string>
#include <fstream>


int main(void)
{
  Walker drop;

  // start system
  initial_conditions(drop);
  compute_force(drop);
  start_integration(drop, DT);

  // evolve
  for(int istep = 0; istep < NSTEPS; ++istep) {
    time_integration(drop, DT);
    compute_force(drop);
    if (istep % 10 == 0) {
      print(drop, istep*DT);
      std::string fname = "simuldata/simul-" + std::to_string(istep) + ".txt";
      std::ofstream fout(fname);
      fout << drop.Rx << ", "
           << drop.Ry << ", "
           << drop.Rz << ", "
           << drop.mass << ", "
           << drop.rad << "\n";
      fout.close();
    }
  }
  return 0;
}
