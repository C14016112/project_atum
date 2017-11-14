#ifndef __AGENT_H__
#define __AGENT_H__

#include <armadillo>
#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using namespace arma;

class agent{

public:
	agent(vector<int> model_wid);
	~agent();
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
	void copy_agent(agent* new_agent);
	void initialize_weight(mat* initial_weight);
	void initialize_bias(mat* initial_bias);
	inline uint get_problem_size(){ return problem_size;}
	inline void set_problem_size(uint size){ problem_size = size;}
	inline vector<int> get_model_width(){ return model_width;}
	void save_model();
	void load_model();

private:
	mat *weight;
	mat *bias;
	uint problem_size;
	vector<int> model_width;

	mat relu(mat);
};
#endif
