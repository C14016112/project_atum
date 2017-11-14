# all:
# 	g++ -std=c++11 ./*.cpp ./*.h -o main -O2 -larmadillo -fopenmp

all: train
train: abstract_env.o 2048_env.o opt_env.o  agent.o es.o main.o
	g++ -std=c++11 -g -o train 2048_env.o opt_env.o  agent.o es.o main.o -O2 -larmadillo -fopenmp
abstract_env.o:
	g++ -std=c++11 -g -c abstract_env.h -o abstract_env.o -O2 -larmadillo -fopenmp
2048_env.o:
	g++ -std=c++11 -g -c 2048_env.cpp -o 2048_env.o -O2 -larmadillo -fopenmp
opt_env.o:
	g++ -std=c++11 -g -c opt_env.cpp -o opt_env.o -O2 -larmadillo -fopenmp
agent.o:
	g++ -std=c++11 -g -c agent.cpp -o agent.o -O2 -larmadillo -fopenmp
es.o:
	g++ -std=c++11 -g -c es.cpp -o es.o -O2 -larmadillo -fopenmp
main.o:
	g++ -std=c++11 -g -c main.cpp -o main.o -O2 -larmadillo -fopenmp
clean:
	rm *.o train *.bin *.csv