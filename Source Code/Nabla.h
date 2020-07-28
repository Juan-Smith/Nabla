#include <cmath>
using namespace std;

enum ActivationFunctions {SIGMOID = 0, TANH = 1};

class ActivationFunction
{
    private:
        int activation_function_type = SIGMOID;           // Stores the type of activation function used
    public :
        void Set_Activation_Function(int);                // Mutates the contents of activation_function_type
        double Evaluate_Activation_Function_At(double) const;   // Returns value of activation function at a specific location
        double Evaluate_Activation_Derivative_At(double) const; // Returns value of derivative of activation function at a specific Location
};

void ActivationFunction::Set_Activation_Function(int typeofactivaiton) 
{
    activation_function_type = typeofactivaiton;    // sets private member activation_function_type equal to the argument received
}

double ActivationFunction::Evaluate_Activation_Function_At(double location) const
{
    double activation = 0; // activation stores the value of activation function at a specific point

    switch(activation_function_type)
    {
        case SIGMOID : // if the activation function is of type sigmoid
             activation = 1/(1+pow(exp(1.0), -location)); // evaluate value of the sigmoid function at the specific location and set equal to activaiton
             break;
        case TANH : // if the activation function is of type hyperbolic tan
             activation = tanh(location); // evaluate value of the hyperbolic tan function at the specific location and set equal to activaiton
             break;

    };

    return activation; // return value of activation
}

double ActivationFunction::Evaluate_Activation_Derivative_At(double location) const
{
    double derivative = 0; // derivative is used to store value of derivative of activation function at the given point

    switch(activation_function_type)
    {
        case SIGMOID : // if activation function is of type sigmoid 
             derivative = (pow(exp(1.0), -location))/(pow((1+pow(exp(1.0),-location)), 2)); // evaluate the value of the first derivative of the sigmoid function at the given point (location) and set equal to derivative
             break;
        case TANH : // if activation function is of type sigmoid
             derivative = pow(1/cosh(location), 2);  // evalueate the valye of first derivative of hyperbolic tan function at given point (location) and set equal to derivative
             break;

    };
return derivative; // return value of derivative
}

class Neuron
{

};

class Layer
{

};

class NeuralNetwork
{

};