#define MAKE(a) (a*)malloc(sizeof(a));
#define MAKE_ARRAY(a,b) (a*)malloc(sizeof(a)*(b));

#include <stdio.h>
#include "Neuron.h"

double randomDouble(double min, double max) { 
   return ((max-min) * (rand() / (double)RAND_MAX))+min;
}

//Perceptron Functions
struct Perceptron createPerceptron(int n_inputs) {
    struct Perceptron p;

    p.n_inputs = n_inputs;
    p.weights = MAKE_ARRAY(double,p.n_inputs+1); //Add one for bias value
    
    for (int i=0; i <= p.n_inputs; i++) {
        p.weights[i] = randomDouble(-10, 10);    
    }

    return p;
}

void freePerceptron(struct Perceptron *p) {
	free(p->weights);
}

int perceptronOutput(struct Perceptron *p, int *inputs) {
    double total=0.0;

    for (int i=0; i<p->n_inputs; i++) {
        total += p->weights[i] * (double)inputs[i];
    }

    total += -p->weights[p->n_inputs]; //Add in bias
    if (total >= 0) {
       return 1;
    }

    return 0;
}

struct NeuralLayer createNeuralLayer(int n_neur, int n_input_neur) {
    struct NeuralLayer n;
    n.n_neurons = n_neur;
    n.n_neuron_inputs = n_input_neur;

    n.neurons = MAKE_ARRAY(struct Perceptron, n.n_neurons);
    for (int i=0; i < n.n_neurons; ++i) {
        n.neurons[i] = createPerceptron(n.n_neuron_inputs);
    }

    return n;
}

void freeNeuralLayer(struct NeuralLayer *nl) {
	//free perceptrons
	for (int i=0; i < nl->n_neurons; i++) {
		freePerceptron(&nl->neurons[i]);
	}
	free(nl->neurons);
}

int* neuralLayerUpdate(struct NeuralLayer *l, int *inputs) {
	int *output = MAKE_ARRAY(int, l->n_neurons);

	for (int i=0; i < l->n_neurons; i++) {
		output[i] = perceptronOutput(&l->neurons[i], inputs);
	}

	return output;
}

//Neural Network Functions
struct NeuralNetwork *createNeuralNetwork(int n_in, int n_out, int n_l, int *n_l_neurons) {
    struct NeuralNetwork *n = MAKE(struct NeuralNetwork)
    n->n_inputs = n_in;
    n->n_outputs = n_out;
    n->n_hlayers = n_l;
    
    //create the layers
    n->layers = MAKE_ARRAY(struct NeuralLayer, n->n_hlayers+1) //Add 1 for the output layer
    n->layers[0] = createNeuralLayer(n_l_neurons[0], n_in);

    for (int i=1; i < n->n_hlayers; ++i) {
        n->layers[i] = createNeuralLayer(n_l_neurons[i], n_l_neurons[i-1]);
    }

    //Create the output layer
    n->layers[n->n_hlayers] = createNeuralLayer(n->n_outputs, n_l_neurons[n->n_hlayers-1]);

    return n;
}

int *UpdateNetwork(struct NeuralNetwork *net, int *inputs) {
   //First feed inputs to first layer
	//Assume inputs has the correct number
	int *output=0;

	for (int i=0; i < net->n_hlayers; ++i) { //For each layer
 		//Create output for current layer
		//Delete Previous 
		if (output) {
			inputs = output;
		}

		output = neuralLayerUpdate(&net->layers[i], inputs);
   }

   return output;
}

void  freeNeuralNetwork(struct NeuralNetwork* n) {
	//free neural layers
	for (int i=0; i <= n->n_hlayers; ++i) {
		freeNeuralLayer(&n->layers[i]);
	}

	free(n->layers);
	free(n);
}

