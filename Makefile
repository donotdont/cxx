c++ --std=c++11 test.cpp -o test $(pkg-config --cflags --libs libmongocxx)

#OBJS specifies which files to compile as part of the project 
OBJS = test.cpp 

#CC specifies which compiler we're using 
CC = c++
STD = c++11

#COMPILER_FLAGS specifies the additional compilation options we're using 
# -w suppresses all warnings 
#COMPILER_FLAGS = -w 
#COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against 
#LINKER_FLAGS = -lSDL2 
#LINKER_FLAGS = -lmongocxx 

#OBJ_NAME specifies the name of our exectuable 
OBJ_NAME = test
#This is the target that compiles our executable 

#all : $(OBJS) 
#$(CC) --std=c++11 $(OBJS) -o $(OBJ_NAME) $(pkg-config --cflags --libs libmongocxx)
