#include "agent.h"

Agent::Agent(vector<int> model_wid){
	m_problem_size = model_wid[0];
	m_model_width = model_wid;
	m_weight = create_initial_weight();
	m_bias = create_initial_bias();
}

Agent::~Agent(){
	delete [] m_weight;
	delete [] m_bias;
}

mat *Agent::create_initial_bias(){
	// vector<mat> 
	mat* new_bias = new mat[m_model_width.size()];
	for(int i = 0; i < m_model_width.size()-1; i++)
		new_bias[i] = randn<mat>(1,m_model_width[i+1]);

	return new_bias;
}

mat *Agent::create_initial_weight(){
	mat* new_weight = new mat[m_model_width.size()];
	for(int i = 0; i < m_model_width.size()-1; i++){
		new_weight[i] = randn<mat>(m_model_width[i], m_model_width[i+1]);
	}
	return new_weight;
}

void Agent::initialize_weight(mat* initial_weight){
	for(int i = 0; i < m_model_width.size()-1; i++)
		initial_weight[i] = randn<mat>(m_model_width[i], m_model_width[i+1]);
}

void Agent::initialize_bias(mat* initial_bias){
	for(int i = 0; i < m_model_width.size()-1; i++)
		initial_bias[i] = randn<mat>(1,m_model_width[i+1]);
}

mat Agent::predict(mat input_matrix){
	mat result = input_matrix;
	for(int i = 0; i < m_model_width.size()-1; i++){
		result = result*m_weight[i] + m_bias[i];
		if(i != m_model_width.size()-2)
			result = relu(result);
	}
	return result;
}

mat Agent::relu(mat matrix){
	mat relu_mat = matrix;
	for(int i = 0; i < relu_mat.size(); i++){
		if(matrix(i) < 0) relu_mat(i) = 0;
	}
	return relu_mat;
}

void Agent::copy_agent(Agent *new_agent){
	new_agent->set_weight(get_weight());
	new_agent->set_bias(get_bias());
	new_agent->set_problem_size(get_problem_size());
}

mat* Agent::get_weight(){
	mat* new_weight = create_initial_weight();
	for(int i = 0; i < m_model_width.size()-1; i++){
		new_weight[i] = m_weight[i];
	}
	return new_weight;
}

void Agent::set_weight(mat* new_weight){
	delete [] m_weight;
	m_weight = new_weight;
}

mat* Agent::get_bias(){
	mat* new_bias = create_initial_bias();
	for(int i = 0; i < m_model_width.size()-1; i++){
		new_bias[i] = m_bias[i];
	}
	return new_bias;
}
void Agent::set_bias(mat* new_bias){
	delete [] m_bias;
	m_bias = new_bias;
}

void Agent::add_weight(mat* added_weight){
	for(int i = 0; i < m_model_width.size()-1; i++){
		m_weight[i] += added_weight[i];
	}
}

void Agent::add_bias(mat* added_bias){
	for(int i = 0; i < m_model_width.size()-1; i++){
		m_bias[i] += added_bias[i];
	}
}

void Agent::save_model(){
	// FILE * checkpoint_file;
	// checkpoint_file = fopen("checkpoint.bin", "wb");
	// if(checkpoint_file == NULL){
	// 	cout << "[ERROR] fail to open checkpoint.bin." << endl;
	// 	exit(EXIT_FAILURE);
	// }
	std::ofstream ofs;
	ofs.open ("model.bin", std::ofstream::out);
	if(ofs.is_open()){
		for(int i = 0; i < m_model_width.size() - 1; i++){
			m_weight[i].save(ofs);
			m_bias[i].save(ofs);
		}
		ofs.close();
	}
	else{
		cout << "[ERROR] fail to open model.bin" << endl;
		exit(EXIT_FAILURE);
	}
}

void Agent::load_model(){
	std::ifstream ifs;
	ifs.open("model.bin", std::ifstream::in);
	if(ifs.is_open()){
		for(int i = 0; i < m_model_width.size() - 1; i++){
			m_weight[i].load(ifs);
			m_bias[i].load(ifs);
		}
		ifs.close();
	}
	else{
		cout << "[ERROR] fail to open model.bin." << endl;
		exit(EXIT_FAILURE);
	}
}