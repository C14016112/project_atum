#ifndef __AGENT_H__
#define __AGENT_H__

#include <armadillo>
#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using namespace arma;

class Agent{

public:
	Agent(vector<int> model_wid);
	~Agent();
	void build_model();
	mat predict(mat input_matrix);
	vector<mat> get_model_weight();
	void set_model_weight(vector<mat> new_model_weight);
	vector<mat> create_initial_model_weight();
	void add_model_weight(vector<mat> added_weight);
	void copy_agent(Agent& new_agent);
	inline uint get_problem_size(){ return m_problem_size;}
	inline void set_problem_size(uint size){ m_problem_size = size;}
	inline vector<int> get_model_width(){ return m_model_width;}
	void save_model();
	void load_model();
	mat relu(mat);

private:
	// mat *m_weight;
	// mat *m_bias;
	uint m_problem_size;
	vector<int> m_model_width;
	vector<mat> m_model_weight;

};
#endif
