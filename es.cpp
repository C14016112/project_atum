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

	mat ** weight_noise = new mat*[m_population_number];
	mat ** bias_noise = new mat*[m_population_number];
	// Abstract_env *envs = new Abstract_env[population_number];
	Game2048Env* envs = new Game2048Env[m_population_number];

	struct timeval startT;
	gettimeofday(&startT, NULL);
	m_start_time = startT.tv_sec + (1.0/1000000) * startT.tv_usec;
	
	for (int i = 0; i < max_iteration; i++){
		mat rewards = zeros(m_population_number);

		// simulation 
		#pragma omp parallel for num_threads(m_thread_number)
		for(int j = 0; j < m_population_number; j++){
			if(i == 0 && j == 0) cout << "thread number: " << omp_get_num_threads() << endl;
			Agent noised_ai = Agent(ai->get_model_width());
			ai->copy_agent(&noised_ai);


			weight_noise[j] = noised_ai.create_initial_weight();
			bias_noise[j] = noised_ai.create_initial_bias();

			for(int k = 0; k < noised_ai.get_model_width().size(); k++){
				weight_noise[j][k] *= m_sigma;
				bias_noise[j][k] *= m_sigma;
			}
			noised_ai.add_weight(weight_noise[j]);
			noised_ai.add_bias(bias_noise[j]);

			double reward = envs[j].evaluate_agent(&noised_ai);
			rewards(j) = reward;
		}
		

		double reward_mean = mean(mean(rewards));
		mat reward_m = stddev(rewards);
		double reward_std = reward_m(0,0);
		mat A = (rewards - reward_mean)/reward_std;

		Es::write_log(i, reward_mean);

		// update 
		for(int j = 0; j < m_population_number; j++){
			for(int k = 0; k < ai->get_model_width().size(); k++){
				weight_noise[j][k] *= m_alpha/(m_population_number*m_sigma*m_sigma)*A[j];
				bias_noise[j][k] *= m_alpha/(m_population_number*m_sigma*m_sigma)*A[j];
			}
			ai->add_weight(weight_noise[j]);
			ai->add_bias(bias_noise[j]);
		}
		for(int j = 0; j < m_population_number; j++){
			delete [] weight_noise[j];
			delete [] bias_noise[j];
		}
		if(i % 100 == 0 && i > 0)
			ai->save_model();
	}
	
	// mat x = randu<mat>(1, ai.get_problem_size());
	// cout << x.t() << " " << problem.evaluate(x) << " " << ai.predict(x) << endl;

	delete [] weight_noise;
	delete [] bias_noise;
	delete [] envs;

}

