#include "drop.hpp"

drop::drop(
  std::vector<double> R,
  std::vector<double> V,
  std::vector<double> F,
  double mass,
  double rad
): m_mass(mass), m_rad(rad), m_R(R), m_V(V), m_F(F) {}

drop::~drop () {}

double drop::GetMass() {
  return m_mass;
}

double drop::GetRad() {
  return m_rad;
}

std::vector<double> drop::GetR() {
  return m_R;
}

std::vector<double> drop::GetV() {
  return m_V;
}

std::vector<double> drop::GetF() {
  return m_F;
}

void drop::SetMass(double mass) {
  m_mass = mass;
}

void drop::SetRad(double rad) {
  m_rad = rad;
}

void drop::SetR(std::vector<double> R) {
  m_R = R;
}

void drop::SetV(std::vector<double> V) {
  m_V = V;
}

void drop::SetF(std::vector<double> F) {
  m_F = F;
}

void drop::ResetF() {
  m_F = {0.0, 0.0, 0.0};
}
