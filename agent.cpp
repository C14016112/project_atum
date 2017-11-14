#include "agent.h"

agent::agent(vector<int> model_wid){
	agent::problem_size = model_wid[0];
	model_width = model_wid;
	agent::weight = agent::create_initial_weight();
	agent::bias = agent::create_initial_bias();
}

agent::~agent(){
	delete [] agent::weight;
	delete [] agent::bias;
}

mat *agent::create_initial_bias(){
	// vector<mat> 
	mat* new_bias = new mat[agent::model_width.size()];
	for(int i = 0; i < agent::model_width.size()-1; i++)
		new_bias[i] = randn<mat>(1,agent::model_width[i+1]);

	return new_bias;
}

mat *agent::create_initial_weight(){
	mat* new_weight = new mat[agent::model_width.size()];
	for(int i = 0; i < agent::model_width.size()-1; i++){
		new_weight[i] = randn<mat>(agent::model_width[i], agent::model_width[i+1]);
	}
	return new_weight;
}

void agent::initialize_weight(mat* initial_weight){
	for(int i = 0; i < agent::model_width.size()-1; i++)
		initial_weight[i] = randn<mat>(agent::model_width[i], agent::model_width[i+1]);
}

void agent::initialize_bias(mat* initial_bias){
	for(int i = 0; i < agent::model_width.size()-1; i++)
		initial_bias[i] = randn<mat>(1,agent::model_width[i+1]);
}

mat agent::predict(mat input_matrix){
	mat result = input_matrix;
	for(int i = 0; i < agent::model_width.size()-1; i++){
		result = result*agent::weight[i] + agent::bias[i];
		if(i != agent::model_width.size()-2)
			result = agent::relu(result);
	}
	return result;
}

mat agent::relu(mat matrix){
	mat relu_mat = matrix;
	for(int i = 0; i < relu_mat.size(); i++){
		if(matrix(i) < 0) relu_mat(i) = 0;
	}
	return relu_mat;
}

void agent::copy_agent(agent *new_agent){
	new_agent->set_weight(agent::get_weight());
	new_agent->set_bias(agent::get_bias());
	new_agent->set_problem_size(agent::get_problem_size());
}

mat* agent::get_weight(){
	mat* new_weight = agent::create_initial_weight();
	for(int i = 0; i < agent::model_width.size()-1; i++){
		new_weight[i] = weight[i];
	}
	return new_weight;
}

void agent::set_weight(mat* new_weight){
	delete [] weight;
	weight = new_weight;
}

mat* agent::get_bias(){
	mat* new_bias = agent::create_initial_bias();
	for(int i = 0; i < agent::model_width.size()-1; i++){
		new_bias[i] = bias[i];
	}
	return new_bias;
}
void agent::set_bias(mat* new_bias){
	delete [] bias;
	bias = new_bias;
}

void agent::add_weight(mat* added_weight){
	for(int i = 0; i < agent::model_width.size()-1; i++){
		weight[i] += added_weight[i];
	}
}

void agent::add_bias(mat* added_bias){
	for(int i = 0; i < agent::model_width.size()-1; i++){
		bias[i] += added_bias[i];
	}
}

void agent::save_model(){
	// FILE * checkpoint_file;
	// checkpoint_file = fopen("checkpoint.bin", "wb");
	// if(checkpoint_file == NULL){
	// 	cout << "[ERROR] fail to open checkpoint.bin." << endl;
	// 	exit(EXIT_FAILURE);
	// }
	std::ofstream ofs;
	ofs.open ("model.bin", std::ofstream::out);
	if(ofs.is_open()){
		for(int i = 0; i < agent::model_width.size() - 1; i++){
			agent::weight[i].save(ofs);
			agent::bias[i].save(ofs);
		}
		ofs.close();
	}
	else{
		cout << "[ERROR] fail to open model.bin" << endl;
		exit(EXIT_FAILURE);
	}
}

void agent::load_model(){
	std::ifstream ifs;
	ifs.open("model.bin", std::ifstream::in);
	if(ifs.is_open()){
		for(int i = 0; i < agent::model_width.size() - 1; i++){
			agent::weight[i].load(ifs);
			agent::bias[i].load(ifs);
		}
		ifs.close();
	}
	else{
		cout << "[ERROR] fail to open model.bin." << endl;
		exit(EXIT_FAILURE);
	}
}