neuralTest: main.o Neuron.o
	cc -o neuralTest main.o Neuron.o

main.o: main.c
	cc -c main.c

Neuron.o: Neuron.c Neuron.h
	cc -c Neuron.c

