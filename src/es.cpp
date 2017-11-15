#include "es.h"

Es::Es(uint thread_num, uint pop_num, double param_sigma, double param_alpha){
	m_thread_number = thread_num;
	m_population_number = pop_num;
	m_sigma = param_sigma;
	m_alpha = param_alpha;
	
	m_csv_log_file = fopen("log.csv", "w");
	if (m_csv_log_file == NULL){
    	cout << "[ERROR] fail to open log.csv." << endl;
        exit(EXIT_FAILURE);
    }
    fprintf(m_csv_log_file, "Time, Iteration, average_reward\n");
    fclose(m_csv_log_file);
}

Es::~Es(){
	
}

void Es::write_log(int cur_iteration, double reward_mean){
	struct timeval stopT;
	gettimeofday(&stopT, NULL);
	double end_time = stopT.tv_sec + (1.0/1000000) * stopT.tv_usec;

	cout << "cur_iteration " << cur_iteration << ", time: " << end_time - m_start_time << ", average reward " << reward_mean << endl;
	m_csv_log_file = fopen("log.csv", "a+");
	fprintf(m_csv_log_file, "%f, %d, %f\n", end_time-m_start_time, cur_iteration, reward_mean);
	fclose(m_csv_log_file);
}

void Es::train(AbstractEnv & problem, Agent * ai, uint max_iteration){

	// mat ** weight_noise = new mat*[m_population_number];
	// Abstract_env *envs = new Abstract_env[population_number];

	Game2048Env* envs = new Game2048Env[m_population_number];
	vector<vector<mat>> model_weight_noise;

	struct timeval startT;
	gettimeofday(&startT, NULL);
	m_start_time = startT.tv_sec + (1.0/1000000) * startT.tv_usec;
	mat normalized_retrun;
	mat rewards;
	for(int i = 0; i < m_population_number; i++) model_weight_noise.push_back(ai->create_initial_model_weight());

	for (int i = 0; i < max_iteration; i++){
		
		// model_weight_noise.clear();
		rewards = zeros(m_population_number);

		// simulation 
		#pragma omp parallel for num_threads(m_thread_number)
		for(int j = 0; j < m_population_number; j++){
			if(i == 0 && j == 0) cout << "thread number: " << omp_get_num_threads() << endl;
			Agent noised_ai = Agent(ai->get_model_width());
			ai->copy_agent(noised_ai);

			model_weight_noise[j] = noised_ai.create_initial_model_weight();
			for(int k = 0; k < noised_ai.get_model_weight().size(); k++)
				model_weight_noise[j][k] *= m_sigma;

			noised_ai.add_model_weight(model_weight_noise[j]);

			double reward = envs[j].evaluate_agent(noised_ai);
			rewards(j) = reward;
		}
		
		double reward_mean = mean(mean(rewards));
		mat reward_m = stddev(rewards);
		double reward_std = reward_m(0,0);
		normalized_retrun = (rewards - reward_mean)/reward_std;
		if(i%10 == 0) Es::write_log(i, reward_mean);	

		// update 
		for(int j = 0; j < m_population_number; j++){
			#pragma omp parallel for num_threads(m_thread_number)
			for(int k = 0; k < ai->get_model_weight().size(); k++){
				model_weight_noise[j][k] *= m_alpha/(m_population_number*m_sigma*m_sigma)*normalized_retrun[j];
			}
			ai->add_model_weight(model_weight_noise[j]);
		}
		
		
		if(i % 10 == 0 && i > 0) ai->save_model();
	}
	
	delete [] envs;

}

