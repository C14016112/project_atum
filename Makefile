SOURCE = ./src
OBJ = ./obj
CFLAGS = -g -O3 -larmadillo -fopenmp
OFLAGS = -g -c -O3 -larmadillo -fopenmp
CC = g++ -std=c++11

all: train
train: $(OBJ)/2048_env.o $(OBJ)/opt_env.o  $(OBJ)/agent.o $(OBJ)/es.o $(OBJ)/main.o
	$(CC) -g -o train $(OBJ)/*.o $(CFLAGS)
$(OBJ)/2048_env.o: 
	$(CC) $(SOURCE)/2048_env.cpp -o $(OBJ)/2048_env.o $(OFLAGS)
$(OBJ)/opt_env.o: 
	$(CC) $(SOURCE)/opt_env.cpp -o $(OBJ)/opt_env.o $(OFLAGS)
$(OBJ)/agent.o: 
	$(CC) $(SOURCE)/agent.cpp -o $(OBJ)/agent.o $(OFLAGS)
$(OBJ)/es.o: 
	$(CC) $(SOURCE)/es.cpp -o $(OBJ)/es.o $(OFLAGS)
$(OBJ)/main.o: 
	$(CC) $(SOURCE)/main.cpp -o $(OBJ)/main.o $(OFLAGS)
clean:
	rm $(OBJ)/*.o train *.bin *.csv -f
