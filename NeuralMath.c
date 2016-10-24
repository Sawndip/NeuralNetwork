#include "NeuralMath.h"

double randomDouble(double min, double max) { 
   return ((max-min) * (rand() / (double)RAND_MAX))+min;
}
