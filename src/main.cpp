#include <iostream>
#include <vector>
#include <sys/time.h>
#include <string>
#include <omp.h>
#include "dnn_agent.h"
#include "matrix.h"
#include "opt_env.h"
#include "evolution_strategy.h"
#include "2048_env.h"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char **argv){
    FILE * config_file;
    config_file = fopen("config.txt", "r");
    if (config_file == NULL){
        cout << "[ERROR] fail to open config.txt." << endl;
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    ssize_t read;
    char * line = NULL;

    uint thread_number=1;
    uint max_iteration=1;
    uint population=1;
    bool is_load_model=false;
    double es_sigma = 0.1;
    double es_alpha = 0.1;
    std::vector<int> model;

    while ((read = getline(&line, &len, config_file)) != -1) {
        string content = string(line);
        string title = content.substr(0, content.find(" "));
        int begin = content.find_first_not_of(" ", content.find(":")+1);
        content = content.substr(begin, content.length()-begin);

        if (title.compare("thread_number") == 0)
            thread_number = stoi(content);
        else if(title.compare("max_iteration") == 0){
            max_iteration = stoi(content);
        }
        else if(title.compare("population") == 0)
            population = stoi(content);
        else if(title.compare("model") == 0){
            int end = 0;
            do {
                end = content.find_first_of(" ");
                model.push_back(stoi(content.substr(0, end)));
                content = content.substr(content.find_first_not_of(" ", end+1));
            }while(end <= content.length());
        }
        else if(title.compare("is_load_model") == 0)
            is_load_model = (bool)stoi(content);
        else if(title.compare("es_sigma") == 0)
            es_sigma = stod(content);
        else if(title.compare("es_alpha") == 0)
            es_alpha = stod(content);

    }

    Game2048Env problem = Game2048Env();
    model.insert(model.begin(), problem.get_input_size());
    model.push_back(problem.get_output_size());

    DnnAgent ai(model);
    if(is_load_model==true) ai.load_agent();
    EvolutionStrategy es = EvolutionStrategy(thread_number, population, es_sigma, es_alpha);

    cout << "thread_number: " << thread_number << endl;
    cout << "max_iteration: " << max_iteration << endl;
    cout << "population: " << population << endl;
    cout << "is load model: " << is_load_model << endl;
    for(int i = 0; i < model.size(); i++){
       if (i == 0) cout << "model: ";
       cout << model[i] << " ";
       if (i == model.size()-1) cout << endl;
    }
    cout << "es sigma: " << es_sigma << endl;
    cout << "es alpha: " << es_alpha << endl;

    es.train(problem, &ai, max_iteration);

    return 0;
}
