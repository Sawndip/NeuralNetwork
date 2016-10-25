#ifndef NEURON_H
#define NEURON_H

#include <time.h>
#include <stdlib.h>

double randomDouble(double min, double max);

struct Perceptron {
    int n_inputs;
    double *weights;
};

struct Perceptron createPerceptron(int n_inputs);
int perceptronOutput(struct Perceptron *p, int *inputs);


struct NeuralLayer {
    int n_neurons;
    
    int n_neuron_inputs;
    struct Perceptron *neurons;
};

struct NeuralLayer createNeuralLayer(int n_neur, int n_inputs_neur);
int *neuralLayerUpdate(struct NeuralLayer *l, int *inputs);


struct NeuralNetwork {
    int n_inputs;
    int n_outputs;

    int n_hlayers;
    int *n_hlayer_neurons;
    struct NeuralLayer *layers;

};

struct NeuralNetwork *createNeuralNetwork(int n_in, int n_out, int num_l, int *n_layer_neurons);
void  freeNeuralNetwork(struct NeuralNetwork* n);
int *UpdateNetwork(struct NeuralNetwork *net, int *inputs);

#endif
