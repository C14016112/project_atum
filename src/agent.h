#ifndef __AGENT_H__
#define __AGENT_H__

#include <iostream>
#include <vector>
#include <fstream>
#include "matrix.h"
#include "weight.h"

using std::vector;

class Agent{

public:
	Agent(const vector<int> &model_wid);
	Agent(const Agent& agent);
	~Agent();
	void build_model();
	Matrix predict(Matrix input_matrix);
	void add_model_weights(Weights& added_model_weights);
	void copy_agent(Agent *new_agent);
	void save_agent();
	void load_agent();
	Matrix relu(Matrix);

	inline const Weights& get_model_weights() const {return m_model_weights;}

private:
	Weights m_model_weights;

};
#endif
