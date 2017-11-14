#include "opt_env.h"

opt_env::opt_env(uint p_size){
	// opt_env::problem_weight = randn<mat>(p_size);
	problem_size = p_size;

}

opt_env::~opt_env(){

}

double opt_env::evaluate(mat input_matrix){
	mat value = zeros(1);
	for(int i = 0; i < input_matrix.size(); i++){
		value += input_matrix[i]*input_matrix[i];
	}
	return value(0);
	// return input_matrix*opt_env::problem_weight;
}

double opt_env::evaluate_agent(agent *ai){
	mat x = randu<mat>(1,opt_env::problem_size);

	mat diff = ai->predict(x) - opt_env::evaluate(x);
	mat loss = diff.t() * diff;
	return -loss(0,0);
}