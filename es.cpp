#include "es.h"

es::es(uint thread_num, uint pop_num, double param_sigma, double param_alpha){
	es::thread_number = thread_num;
	es::population_number = pop_num;
	es::sigma = param_sigma;
	es::alpha = param_alpha;
	
	csv_log_file = fopen("log.csv", "w");
	if (csv_log_file == NULL){
    	cout << "[ERROR] fail to open log.csv." << endl;
        exit(EXIT_FAILURE);
    }
    fprintf(csv_log_file, "Time, Iteration, average_reward\n");
    fclose(csv_log_file);
}

es::~es(){
	// fclose(csv_log_file);
}

void es::write_log(int cur_iteration, double reward_mean){
	struct timeval stopT;
	gettimeofday(&stopT, NULL);
	double end_time = stopT.tv_sec + (1.0/1000000) * stopT.tv_usec;

	cout << "cur_iteration " << cur_iteration << ", time: " << end_time - start_time << ", average reward " << reward_mean << endl;
	csv_log_file = fopen("log.csv", "a+");
	fprintf(csv_log_file, "%f, %d, %f\n", end_time-start_time, cur_iteration, reward_mean);
	fclose(csv_log_file);
}

void es::train(Abstract_env & problem, agent * AI, uint max_iteration){

	mat ** weight_noise = new mat*[es::population_number];
	mat ** bias_noise = new mat*[es::population_number];
	// Abstract_env *envs = new Abstract_env[es::population_number];
	game_2048_env* envs = new game_2048_env[es::population_number];

	struct timeval startT;
	gettimeofday(&startT, NULL);
	start_time = startT.tv_sec + (1.0/1000000) * startT.tv_usec;
	
	for (int i = 0; i < max_iteration; i++){
		mat rewards = zeros(es::population_number);

		// simulation 
		#pragma omp parallel for num_threads(es::thread_number)
		for(int j = 0; j < es::population_number; j++){
			if(i == 0 && j == 0) cout << "thread number: " << omp_get_num_threads() << endl;
			agent noised_ai = agent(AI->get_model_width());
			AI->copy_agent(&noised_ai);


			weight_noise[j] = noised_ai.create_initial_weight();
			bias_noise[j] = noised_ai.create_initial_bias();

			for(int k = 0; k < noised_ai.get_model_width().size(); k++){
				weight_noise[j][k] *= es::sigma;
				bias_noise[j][k] *= es::sigma;
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

		es::write_log(i, reward_mean);

		// update 
		for(int j = 0; j < es::population_number; j++){
			for(int k = 0; k < AI->get_model_width().size(); k++){
				weight_noise[j][k] *= es::alpha/(es::population_number*es::sigma*es::sigma)*A[j];
				bias_noise[j][k] *= es::alpha/(es::population_number*es::sigma*es::sigma)*A[j];
			}
			AI->add_weight(weight_noise[j]);
			AI->add_bias(bias_noise[j]);
		}
		for(int j = 0; j < es::population_number; j++){
			delete [] weight_noise[j];
			delete [] bias_noise[j];
		}
		if(i % 100 == 0 && i > 0)
			AI->save_model();
	}
	
	// mat x = randu<mat>(1, AI.get_problem_size());
	// cout << x.t() << " " << problem.evaluate(x) << " " << AI.predict(x) << endl;

	delete [] weight_noise;
	delete [] bias_noise;
	delete [] envs;

}

