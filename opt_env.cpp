#include "opt_env.h"

OptEnv::OptEnv(uint p_size){
	// OptEnv::problem_weight = randn<mat>(p_size);
	m_problem_size = p_size;

}

OptEnv::~OptEnv(){

}

double OptEnv::evaluate(mat input_matrix){
	mat value = zeros(1);
	for(int i = 0; i < input_matrix.size(); i++){
		value += input_matrix[i]*input_matrix[i];
	}
	return value(0);
	// return input_matrix*OptEnv::problem_weight;
}

double OptEnv::evaluate_agent(Agent *ai){
	mat x = randu<mat>(1,m_problem_size);

	mat diff = ai->predict(x) - evaluate(x);
	mat loss = diff.t() * diff;
	return -loss(0,0);
}