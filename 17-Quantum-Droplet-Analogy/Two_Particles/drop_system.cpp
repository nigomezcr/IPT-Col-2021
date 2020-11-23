#include "drop_system.hpp"
/* VEFRL 4-th Order */
/*
const double xi = 0.1644986515575760e0;
const double lambda = -0.2094333910398989e-1;
const double chi = 0.1235692651138917e1;
*/

/* PEFRL 4-th Order */
const double xi = 0.1786178958448091;
const double lambda = -0.2123418310626054;
const double chi = -0.6626458266981849e-1;

drop_system::drop_system (
  double g,
  double K,
  double f,
  double a,
  double b,
  double lf,
  std::vector< std::map< std::string, std::vector<double> > > drops_R_V_F,
  std::vector< std::map< std::string, double> > drops_m_r
): m_drops({}),  m_g(g), m_K(K), m_f(f), m_a(a), m_b(b), m_lf(lf) {

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


void drop_system::compute_position(double constant, double dt){
  for(size_t i=0; i<m_drops.size(); i++){
    for(size_t j=0; j<m_drops[i].m_R.size(); j++){
      m_drops[i].m_R[j] += m_drops[i].m_V[j]*constant*dt;
    }
  }
}


void drop_system::compute_velocity(double constant, double dt){
  for(size_t i=0; i<m_drops.size(); i++){
    for(size_t j=0; j<m_drops[i].m_V.size(); j++){
      m_drops[i].m_V[j] += m_drops[i].m_F[j]*constant*dt/m_drops[i].m_mass;
    }
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

    std::vector<double> R = m_drops[drop_index].GetR();
    std::vector<double> V = m_drops[drop_index].GetV();
    double v = std::sqrt(V[0] * V[0] + V[1] * V[1]);

    //driving force
    F[0] += m_a * std::sin(m_f * v) * V[0]/v;
    F[1] += m_a * std::sin(m_f * v) * V[1]/v;

    //damping force
    F[0] -= m_b * V[0];
    F[1] -= m_b * V[1];

    //binding forces
    for (size_t second_drop = 0; second_drop < m_drops.size(); second_drop++) {
      if (second_drop != drop_index) {
        std::vector<double> R_2 = m_drops[second_drop].GetR();
        std::vector<double> R_12 = {R[0] - R_2[0], R[1] - R_2[1]};
        double r_12 = std::sqrt(R_12[0] * R_12[0] + R_12[1] * R_12[1] );

        F[0] += m_a * m_lf * R_12[0] / (r_12 * r_12) * std::sin(r_12 / m_lf);
        F[1] += m_a * m_lf * R_12[1] / (r_12 * r_12) * std::sin(r_12 / m_lf);
      }
    }

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
  /* Leap-frog */
  /*
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
    }*/

  /* VEFRL 4-th Order */
  /*
  compute_force();
  compute_velocity(xi, dt);
  compute_position(0.5 - lambda, dt);
  
  compute_force();
  compute_velocity(chi, dt);
  compute_position(lambda, dt);

  compute_force();
  compute_velocity(1.0 - 2.0*(chi+xi), dt);
  compute_position(lambda, dt);

  compute_force();
  compute_velocity(chi, dt);
  compute_position(0.5 - lambda, dt);

  compute_force();
  compute_velocity(xi, dt);
  */

  /* PEFRL 4-th Order */
  compute_position(xi, dt);
  compute_force();
  compute_velocity(0.5 - lambda, dt);

  compute_position(chi, dt);
  compute_force();
  compute_velocity(lambda, dt);

  compute_position(1.0 - 2.0*(xi+chi), dt);
  compute_force();
  compute_velocity(lambda, dt);

  compute_position(chi, dt);
  compute_force();
  compute_velocity(0.5 - lambda, dt);

  compute_position(xi, dt);
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
