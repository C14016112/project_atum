#include "opt_env.h"

OptEnv::OptEnv(uint p_size){
	// OptEnv::problem_weight = randn<mat>(p_size);
	m_problem_size = p_size;

}

OptEnv::~OptEnv(){

}

double OptEnv::evaluate(Matrix input_matrix){
	Matrix value = zeros(1);
	for(int i = 0; i < input_matrix.size(); i++){
		value += input_matrix[i]*input_matrix[i];
	}
	return value(0);
	// return input_matrix*OptEnv::problem_weight;
}

double OptEnv::evaluate_agent(AbstractAgent &ai){
	Matrix x = randu<Matrix>(1,m_problem_size);

	Matrix diff = ai.evaluate_action(x) - evaluate(x);
	Matrix loss = diff.t() * diff;
	return -loss(0,0);
}
