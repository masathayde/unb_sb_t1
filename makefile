.PHONY: clean
# Specify compiler to be used
CXX = g++
CXXFLAGS += -std=c++11 -O1
OBJS = $(wildcard *.o)

ifdef OS
   RM = del /Q
   FixPath = $(subst /,\,$1)
else
   ifeq ($(shell uname), Linux)
      RM = rm -f
      FixPath = $1
   endif
endif

all: main clean

main: main.cpp common.o classes.o error.o preprocessing.o print.o tokens.o
	$(CXX) $(CXXFLAGS) -o main.exe main.cpp common.o classes.o error.o preprocessing.o print.o tokens.o

classes.o: classes.hpp classes.cpp
	$(CXX) $(CXXFLAGS) -c classes.cpp

common.o: common.hpp common.cpp
	$(CXX) $(CXXFLAGS) -c common.cpp

error.o: error.hpp error.cpp
	$(CXX) $(CXXFLAGS) -c error.cpp

tokens.o: tokens.hpp tokens.cpp
	$(CXX) $(CXXFLAGS) -c tokens.cpp

preprocessing.o: preprocessing.hpp preprocessing.cpp
	$(CXX) $(CXXFLAGS) -c preprocessing.cpp

print.o: print.hpp print.cpp
	$(CXX) $(CXXFLAGS) -c print.cpp

clean:
	$(RM) $(OBJS)