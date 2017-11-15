SOURCE = ./src
OBJ = ./obj
OPT_DEGREE = -O3
CFLAGS = -g $(OPT_DEGREE) -larmadillo -fopenmp
OFLAGS = -g $(OPT_DEGREE) -c -larmadillo -fopenmp
CC = g++ -std=c++11

all: train
train: $(OBJ)/weight.o $(OBJ)/2048_env.o $(OBJ)/opt_env.o  $(OBJ)/agent.o $(OBJ)/evolution_strategy.o $(OBJ)/main.o
	$(CC) -g -o train $(OBJ)/*.o $(CFLAGS)
$(OBJ)/weight.o: ${SOURCE}/weight.cpp ${SOURCE}/weight.h
	$(CC) $(SOURCE)/weight.cpp -o $(OBJ)/weight.o $(OFLAGS)
$(OBJ)/2048_env.o: ${SOURCE}/2048_env.cpp ${SOURCE}/2048_env.h
	$(CC) $(SOURCE)/2048_env.cpp -o $(OBJ)/2048_env.o $(OFLAGS)
$(OBJ)/opt_env.o: ${SOURCE}/opt_env.cpp ${SOURCE}/opt_env.h
	$(CC) $(SOURCE)/opt_env.cpp -o $(OBJ)/opt_env.o $(OFLAGS)
$(OBJ)/agent.o: ${SOURCE}/agent.cpp ${SOURCE}/agent.h
	$(CC) $(SOURCE)/agent.cpp -o $(OBJ)/agent.o $(OFLAGS)
$(OBJ)/evolution_strategy.o: ${SOURCE}/evolution_strategy.cpp ${SOURCE}/evolution_strategy.h
	$(CC) $(SOURCE)/evolution_strategy.cpp -o $(OBJ)/evolution_strategy.o $(OFLAGS)
$(OBJ)/main.o: ${SOURCE}/main.cpp
	$(CC) $(SOURCE)/main.cpp -o $(OBJ)/main.o $(OFLAGS)
clean:
	rm $(OBJ)/*.o train *.bin *.csv -f
