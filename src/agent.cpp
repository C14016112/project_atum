#include "agent.h"

Agent::Agent(vector<int> model_wid){
	m_problem_size = model_wid[0];
	m_model_width = model_wid;
	m_model_weight = create_initial_model_weight();
}

Agent::~Agent(){
	m_model_weight.clear();
}

vector<mat> Agent::create_initial_model_weight(){
	vector<mat> new_model_weight;
	// mat* new_weight = new mat[m_model_width.size()];
	for(int i = 0; i < m_model_width.size()-1; i++){
		new_model_weight.push_back(randn<mat>(m_model_width[i], m_model_width[i+1]));
		new_model_weight.push_back(randn<mat>(1, m_model_width[i+1]));
	}
	return new_model_weight;
}

mat Agent::predict(mat input_matrix){
	mat result = input_matrix;
	for(int i = 0; i < m_model_width.size()-1; i++){
		result = result*m_model_weight[2*i] + m_model_weight[2*i+1];
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

void Agent::copy_agent(Agent &new_agent){
	new_agent.set_model_weight(m_model_weight);
	new_agent.set_problem_size(get_problem_size());
}

vector<mat> Agent::get_model_weight(){
	vector<mat> new_model_weight = m_model_weight;
	return new_model_weight;
}

void Agent::set_model_weight(vector<mat> new_model_weight){
	m_model_weight = new_model_weight;
}

void Agent::add_model_weight(vector<mat> added_model_weight){
	for(int i = 0; i < m_model_weight.size(); i++){
		m_model_weight[i] += added_model_weight[i];
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
		for(int i = 0; i < m_model_weight.size(); i++){
			m_model_weight[i].save(ofs);
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
		for(int i = 0; i < m_model_weight.size() - 1; i++){
			m_model_weight[i].load(ifs);
		}
		ifs.close();
	}
	else{
		cout << "[ERROR] fail to open model.bin." << endl;
		exit(EXIT_FAILURE);
	}
}