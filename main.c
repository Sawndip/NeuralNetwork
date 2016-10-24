#include <stdio.h>
#include <stdlib.h>

#include "Neuron.h"

int main() {

    int numbers[] = {10, 5, 10, 3};
    int input[] = {1, 1, 1, 1};

    srand((unsigned)time(0));


    struct NeuralNetwork *net = createNeuralNetwork(4, 5, 4, numbers);

    int *output = UpdateNetwork(net, input);

    printf("Entering Inputs: %d, %d, %d, %d, produced:\n", input[0], input[1],input[2],input[3]);
    
    for (int i=0; i < net->n_outputs; i++) {
        printf("OUTPUT[%d]: %d\n", i, output[i]);
    }

    return 0;
}
