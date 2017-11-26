CC = g++
SOURCE = ./src
OBJDIR = ./obj
OBJ = weight.o 2048_env.o opt_env.o agent.o evolution_strategy.o main.o
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

OPT_DEGREE = -O3
COMMON_FLAGS = -fopenmp
COMPILE_FLAGS = -std=c++11 -g
LDFLAGS = -larmadillo
CFLAGS = $(COMPILE_FLAGS) $(OPT_DEGREE) $(COMMON_FLAGS)
OFLAGS = $(COMMON_FLAGS) $(LDFLAGS)
EXEC = train


VPATH = $(SOURCE)
vpath
vpath %.c %.h $(SOURCE)

.PHONY: all
all: obj $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) $(OFLAGS) -o $@
$(OBJDIR)/weight.o: weight.cpp weight.h
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJDIR)/2048_env.o: 2048_env.cpp 2048_env.h
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJDIR)/opt_env.o: opt_env.cpp opt_env.h abstract_env.h
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJDIR)/agent.o: agent.cpp agent.h abstract_agent.h
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJDIR)/evolution_strategy.o: evolution_strategy.cpp evolution_strategy.h
	$(CC) -c $(CFLAGS) $< -o $@
$(OBJDIR)/main.o: main.cpp
	$(CC) -c $(CFLAGS) $< -o $@

# For example, you can use `make print-OBJS` to see the `OBJS` variable.
print-%: ; @echo $*=$($*)

obj:
	mkdir -p $(OBJDIR)

.PHONY: clean
clean:
	rm -rf $(OBJDIR) train *.bin *.csv
