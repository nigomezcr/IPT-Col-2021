#include "drop_system.hpp"

drop_system::drop_system (
  double g,
  double K,
  double f,
  double a,
  double b,
  std::vector< std::map< std::string, std::vector<double> > > drops_R_V_F,
  std::vector< std::map< std::string, double> > drops_m_r
): m_drops({}),  m_g(g), m_K(K), m_f(f), m_a(a), m_b(b) {

  for (int drop_index = 0; drop_index < drops_R_V_F.size(); drop_index++) {
    m_drops.push_back(drop(
      drops_R_V_F[drop_index]["R"],
      drops_R_V_F[drop_index]["V"],
      drops_R_V_F[drop_index]["F"],
      drops_m_r[drop_index]["m"],
      drops_m_r[drop_index]["r"])
    );
  }

}

drop_system::~drop_system () {}

void drop_system::initial_conditions(
  std::vector< std::map< std::string, std::vector<double> > > drops_R_V,
  std::vector< std::map<std::string, double> > drops_m_r
) {

  for (int drop_index = 0; drop_index < drops_R_V.size(); drop_index++) {
    m_drops[drop_index].SetR(drops_R_V[drop_index]["R"]);
    m_drops[drop_index].SetV(drops_R_V[drop_index]["V"]);
    m_drops[drop_index].SetMass(drops_m_r[drop_index]["m"]);
    m_drops[drop_index].SetRad(drops_m_r[drop_index]["r"]);
  }
}

void drop_system::compute_force() {
  for (int drop_index = 0; drop_index < m_drops.size(); drop_index++) {
    // reset force
    m_drops[drop_index].ResetF();

    std::vector<double> F = {0.0, 0.0, 0.0};

    // gravitational force
    F[2] += m_drops[drop_index].GetMass() * m_g;

    //Elastic force
    double delta = m_drops[drop_index].GetRad() - m_drops[drop_index].GetR()[2];
    if(delta > 0.0){
      F[2] += delta * m_K;
    }

    //driving force
    F[0] += m_a * std::sin(m_f * m_drops[drop_index].GetV()[0]);

    //damping force
    F[0] -= m_b * m_drops[drop_index].GetV()[0];

    m_drops[drop_index].SetF(F);
  }
}


void drop_system::start_integration(const double & dt) {
  for (int drop_index = 0; drop_index < m_drops.size(); drop_index++) {
    std::vector <double> V = m_drops[drop_index].GetV();

    V[0] -= m_drops[drop_index].GetF()[0]*dt/(2*m_drops[drop_index].GetMass());
    V[1] -= m_drops[drop_index].GetF()[1]*dt/(2*m_drops[drop_index].GetMass());
    V[2] -= m_drops[drop_index].GetF()[2]*dt/(2*m_drops[drop_index].GetMass());

    m_drops[drop_index].SetV(V);
  }
}

void drop_system::time_integration(const double & dt) {
  for (int drop_index = 0; drop_index < m_drops.size(); drop_index++) {
    std::vector <double> V = m_drops[drop_index].GetV();
    std::vector <double> R = m_drops[drop_index].GetR();

    V[0] += m_drops[drop_index].GetF()[0]*dt/m_drops[drop_index].GetMass();
    V[1] += m_drops[drop_index].GetF()[1]*dt/m_drops[drop_index].GetMass();
    V[2] += m_drops[drop_index].GetF()[2]*dt/m_drops[drop_index].GetMass();

    m_drops[drop_index].SetV(V);

    R[0] += m_drops[drop_index].GetV()[0] * dt;
    R[1] += m_drops[drop_index].GetV()[1] * dt;
    R[2] += m_drops[drop_index].GetV()[2] * dt;

    m_drops[drop_index].SetR(R);
  }
}

void drop_system::print(int body) {
  std::cout
  << std::to_string(m_drops[body].GetR()[0]) << " "
  << std::to_string(m_drops[body].GetR()[1]) << " "
  << std::to_string(m_drops[body].GetR()[2]) << " ";
}

std::string drop_system::GetDataCSV(double time_sim, int body) {
  std::string data = std::to_string(time_sim) + " ";

  data
  + std::to_string(m_drops[body].GetR()[0]) + ", "
  + std::to_string(m_drops[body].GetR()[1]) + ", "
  + std::to_string(m_drops[body].GetR()[2]) + ", "
  + std::to_string(m_drops[body].GetV()[0]) + ", "
  + std::to_string(m_drops[body].GetV()[1]) + ", "
  + std::to_string(m_drops[body].GetV()[2]);
  std::cout << data << '\n';
  return data;
}

std::string drop_system::GetDataTXT(double time_sim, int body) {
  std::string data = std::to_string(time_sim) + " ";

  data
  + std::to_string(m_drops[body].GetR()[0]) + "  "
  + std::to_string(m_drops[body].GetR()[1]) + "  "
  + std::to_string(m_drops[body].GetR()[2]) + "  "
  + std::to_string(m_drops[body].GetV()[0]) + "  "
  + std::to_string(m_drops[body].GetV()[1]) + "  "
  + std::to_string(m_drops[body].GetV()[2]);
  std::cout << data << '\n';
  return data;
}
