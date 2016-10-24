neuralTest: main.o Neuron.o NeuralMath.o
	cc -o neuralTest main.o Neuron.o NeuralMath.o

main.o: main.c
	cc -c main.c

Neuron.o: Neuron.c Neuron.h
	cc -c Neuron.c

NeuralMath.o: NeuralMath.c NeuralMath.h
	cc -c NeuralMath.c
