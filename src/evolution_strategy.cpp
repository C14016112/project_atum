#include "evolution_strategy.h"
#include "utils.h"

EvolutionStrategy::EvolutionStrategy(uint thread_num, uint pop_num, double param_sigma, double param_alpha){
    m_thread_number = thread_num;
    m_population_number = pop_num;
    m_sigma = param_sigma;
    m_alpha = param_alpha;
    create_utility_table();

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

    vector<Weights> noised_weights (m_population_number*2, Weights(ai->get_weights(), Weights::GAUSSIAN));
    vector<std::pair<int, double>> id_and_rewards_vector (m_population_number*2, std::pair<int, double>(0, 0.0));

    m_start_time = utils::get_current_time_in_seconds();

    for (int i = 0; i < max_iteration; i++){
        double total_reward = 0;

        #pragma omp parallel for num_threads(m_thread_number)
        for(int j = 0; j < m_population_number; j++){
            if(i == 0 && j == 0) std::cout << "thread number: " << omp_get_num_threads() << std::endl;
            int position = 2*j;
            noised_weights[position] = Weights(ai->get_weights(), Weights::GAUSSIAN);
            noised_weights[position] *= m_sigma;
            DnnAgent noised_ai(*ai);
            noised_ai.add_weights(noised_weights[position]);
            double reward = problem.evaluate_agent(noised_ai);
            id_and_rewards_vector[position] = std::pair<int, double>(position, reward);
            total_reward += reward;

            // mirrored noised
            noised_weights[position+1] = noised_weights[position];
            noised_weights[position+1] *= -1;
            DnnAgent mirror_ai(*ai);
            mirror_ai.add_weights(noised_weights[position+1]);
            double mirror_reward = problem.evaluate_agent(mirror_ai);
            id_and_rewards_vector[position+1] = std::pair<int, double>(position+1, mirror_reward);
            total_reward += mirror_reward;
        }

        id_and_rewards_vector = sort_id_reward_vector(id_and_rewards_vector);
        if(i%10 == 0) write_log(i, (total_reward/(2*m_population_number)));

        // update
        for(int j = 0; j < m_population_number*2; j++){
            int noise_id = id_and_rewards_vector[j].first;
            noised_weights[noise_id] *= m_alpha*(utility_table[j])/(m_population_number*2*m_sigma*m_sigma);
            ai->add_weights(noised_weights[noise_id]);
        }


        if(i % 10 == 0 && i > 0) ai->save_agent();
    }

}

void EvolutionStrategy::create_utility_table(){
    int base = 2*m_population_number;
    double util_sum = 0;
    for(int i = 0; i < base; i++){
        utility_table.push_back(std::max(0.0, log(base/(2.0) + 1)-log(i+1)));
        util_sum += utility_table[i];
    }
    for(int i = 0; i < base; i++)
        utility_table[i] = (utility_table[i] / util_sum) - (1.0/base);
}

vector<std::pair<int, double>> EvolutionStrategy::sort_id_reward_vector( vector<std::pair<int, double>> id_rewards){

    for(int i = 0; i < id_rewards.size(); i++){
        for(int j = i+1; j < id_rewards.size(); j++){
            if (id_rewards[i].second < id_rewards[j].second){
                std::swap(id_rewards[i], id_rewards[j]);
            }
        }

    }
    return id_rewards;
}

