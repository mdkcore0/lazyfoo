OBJS = LUtil.cpp main.cpp
CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++11
LD_FLAGS = -lGL -lGLU -lglut
OBJ_NAME = lesson01

all: $(OBJS)
	$(CXX) $(OBJS) $(CXX_FLAGS) $(LD_FLAGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
