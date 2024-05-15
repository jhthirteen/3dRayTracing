all: tracer

tracer: vec.o sphere.o tracer.o
	g++ vec.o sphere.o tracer.o -o tracer 

tracer.o:
	g++ -c tracer.cpp

vec.o:
	g++ -c vec.cpp

sphere.o:
	g++ -c sphere.cpp

clean:
	rm *.o