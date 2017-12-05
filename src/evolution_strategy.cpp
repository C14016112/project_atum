#include "evolution_strategy.h"
#include "utils.h"

EvolutionStrategy::EvolutionStrategy(uint thread_num, uint pop_num, double param_sigma, double param_alpha){
    m_thread_number = thread_num;
    m_population_number = pop_num;
    m_sigma = param_sigma;
    m_alpha = param_alpha;

    m_csv_log_file = fopen("log.csv", "w");
    if (m_csv_log_file == NULL){
        std::cout << "[ERROR] fail to open log.csv." << std::endl;
        exit(EXIT_FAILURE);
    }
    fprintf(m_csv_log_file, "Time, Iteration, average_reward\n");
    fclose(m_csv_log_file);
}

EvolutionStrategy::~EvolutionStrategy(){

}

void EvolutionStrategy::write_log(int cur_iteration, double reward_mean){
    double end_time = utils::get_current_time_in_seconds();

    std::cout << "cur_iteration " << cur_iteration << ", time: " << end_time - m_start_time << ", average reward " << reward_mean << std::endl;
    m_csv_log_file = fopen("log.csv", "a+");
    fprintf(m_csv_log_file, "%f, %d, %f\n", end_time-m_start_time, cur_iteration, reward_mean);
    fclose(m_csv_log_file);
}

void EvolutionStrategy::train(AbstractEnv & problem, DnnAgent* ai, uint max_iteration){

    vector<Weights> noised_weights(m_population_number);

    m_start_time = utils::get_current_time_in_seconds();
    Matrix normalized_return;
    Matrix rewards;

    for (int i = 1; i <= max_iteration; i++){
        rewards = zeros(m_population_number*2);

        #pragma omp parallel for num_threads(m_thread_number)
        for(int j = 0; j < m_population_number; j++){
            if(i == 0 && j == 0) std::cout << "thread number: " << omp_get_num_threads() << std::endl;
            noised_weights[j] = Weights(ai->get_weights(), Weights::GAUSSIAN);
            noised_weights[j] *= m_sigma;

            DnnAgent noised_ai(*ai);
            noised_ai.add_weights(noised_weights[j]);

            double reward = problem.evaluate_agent(noised_ai);

            noised_weights[j] *= -1;
            DnnAgent mirror_ai(*ai);
            mirror_ai.add_weights(noised_weights[j]);

            double mirror_reward = problem.evaluate_agent(mirror_ai);

            noised_weights[j] *= -1;

            rewards(2*j) = reward;
            rewards(2*j+1) = mirror_reward;
        }

        double reward_mean = mean(mean(rewards));
        Matrix reward_m = stddev(rewards);
        double reward_std = reward_m(0,0);
        normalized_return = (rewards - reward_mean)/reward_std;
        if(i%10 == 0) write_log(i, reward_mean);

        // update
        for(int j = 0; j < m_population_number; j++){
            noised_weights[j] *= m_alpha*(normalized_return[2*j]-normalized_return[2*j+1])/(m_population_number*2*m_sigma*m_sigma);
            //noised_weights[j] *= m_alpha*(normalized_return[2*j])/(m_population_number*m_sigma*m_sigma);
            ai->add_weights(noised_weights[j]);
        }


        if(i % 10 == 0 && i > 0) ai->save_agent();
    }

}

