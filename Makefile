CC=g++
CXXFLAGS=-Wall -Wvla -Wextra -Werror -g -std=c++14
LDFLAGS=-lm
HEADERS=Matrix.h Activation.h Dense.h MlpNetwork.h
OBJS=Matrix.o Activation.o Dense.o MlpNetwork.o main.o

# Correct pattern rule for compiling C++ files to object files
%.o: %.cpp $(HEADERS)
	$(CC) $(CXXFLAGS) -c $< -o $@

mlpnetwork: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(CXXFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf *.o mlpnetwork
