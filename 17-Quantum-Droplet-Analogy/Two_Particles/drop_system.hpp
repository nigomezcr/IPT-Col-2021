#ifndef DROP_SYSTEM_HPP
#define DROP_SYSTEM_HPP

#include "drop.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <cmath>

class drop_system {
public:
  drop_system (
    double g,
    double K,
    double f,
    double a,
    double b,
    double lf,
    std::vector< std::map< std::string, std::vector<double> > > drops_R_V_F,
    std::vector< std::map<std::string, double> > drops_m_r
  );

  ~drop_system ();

  // function declarations
  void initial_conditions(
    std::vector< std::map< std::string, std::vector<double> > > drops_R_V,
    std::vector< std::map<std::string, double> > drops_m_r
  );
  void compute_force();
  void time_integration(const double & dt);
  void start_integration(const double & dt);
  void print(int body);

  std::string GetDataCSV(double time_sim, int body);
  std::string GetDataTXT(double time_sim, int body);

private:
  std::vector<drop> m_drops;

  const double m_g;
  const double m_K;
  const double m_f;
  const double m_a;
  const double m_b;
  const double m_lf;
};

#endif // DROP_SYSTEM_HPP
