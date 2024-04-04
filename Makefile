CC :=g++ -std=c++11

OPTIONS :=-g -pedantic -Wall -Wextra -Wno-error
OBJECTS := main.o

PYBIND :=-I/usr/include/pybind11
PYTHON:=-I/usr/include/python3.6m/ -L/usr/lib64 -lpython3.6m

getCurrentTone: $(OBJECTS) 
	$(CC) $(OPTIONS) $(OBJECTS) $(PYTHON) $(PYBIND) -o getCurrentTone

main.o: main.cpp 
	$(CC) $(OPTIONS) -c main.cpp $(PYTHON) $(PYBIND) -o main.o 


clean:
	rm -f ./*.o getCurrentTone