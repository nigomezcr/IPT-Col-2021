#ifndef DROP_HPP
#define DROP_HPP

#include <vector>
#include <iostream>
//#include "drop_system.hpp"

class drop {
public:
  drop (
    std::vector<double> R,
    std::vector<double> V,
    std::vector<double> F,
    double mass = 1,
    double rad = 0.43
  );

  ~drop ();

  double GetMass();
  double GetRad();
  std::vector<double> GetR();
  std::vector<double> GetV();
  std::vector<double> GetF();

  void SetMass(double mass);
  void SetRad(double rad);
  void SetR(std::vector<double> R);
  void SetV(std::vector<double> V);
  void SetF(std::vector<double> F);

  void ResetF();

  friend class drop_system;

private:
  double m_mass;
  double m_rad;
  std::vector<double> m_R;
  std::vector<double> m_V;
  std::vector<double> m_F;
};

#endif // DROP_HPP
