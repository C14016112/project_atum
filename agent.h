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
	mat* get_weight();
	void set_weight(mat* new_weight);
	mat* get_bias();
	void set_bias(mat* new_bias);
	mat *create_initial_bias();
	mat *create_initial_weight();
	void add_weight(mat* added_weight);
	void add_bias(mat* added_bias);
	void copy_agent(Agent* new_agent);
	void initialize_weight(mat* initial_weight);
	void initialize_bias(mat* initial_bias);
	inline uint get_problem_size(){ return m_problem_size;}
	inline void set_problem_size(uint size){ m_problem_size = size;}
	inline vector<int> get_model_width(){ return m_model_width;}
	void save_model();
	void load_model();
	mat relu(mat);

private:
	mat *m_weight;
	mat *m_bias;
	uint m_problem_size;
	vector<int> m_model_width;

};
#endif
