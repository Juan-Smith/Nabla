#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum ActivationFunctions {SIGMOID = 0, TANH = 1};

class ActivationFunction
{
    private:
        int activation_function_type = SIGMOID;           // Stores the type of activation function used
    public :
        enum ActivationFunctions {SIGMOID = 0, TANH = 1}; // enumarable to store the names of Activation functions
        void Set_Activation_Function(int);                // Mutates the contents of activation_function_type
        int Get_Activation_Function() const;              // Accessor method for activation_function_type
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

int ActivationFunction::Get_Activation_Function() const
{
    return activation_function_type; // return activation function type
}

class Neuron
{
    private : 
    const int NUM_DECIMALS = 4; // stores the number of decimals used while calculating random values
    double bias = 0; // stores the bias term of the Neuron
    double* weights = 0; // stores the list of weights of the Neuron
    double* inputs = 0; // stores the list of inputs to Neuron
    int num_weights = 0; // stores the number of weights of the Neuron
    double Random_Weight(int) const; // Function to generate random weight (between -1 and 1)
    double Random_Bias(int) const; // Function to generate random bias (between -1 and 1)
    ActivationFunction* activation_function = 0; // stores the location of the activation function of the Neuron
    public :
    void Create_Neuron(int, int); // allows us to initialize a Neuron
    void Destroy_Neuron(); // allows us to destroy a Neuron
    void Set_Bias(double); // Mutator method for Neuron's bias term
    void Set_Weights(double*); // Mutator method for Neuron's weights
    void Set_Inputs(double*); // Mutator method for Neuron's Inputs
    void Set_Neuron_Activation_Function(int); // Mutator method for Neuron's Activation Function
    double Get_Bias() const; // Accessor method for Neuron's bias term
    double* Get_Weights() const; // Accessor method for Neuron's Weights
    double* Get_Inputs() const; // Accessor method for Neuron's Input
    int Get_Activation_Function() const; // Accessor method for Neuron's Activation Function
    string Get_Activation_Function_Name() const; //Accessor method for name of Neuron's Activation function
    double Get_Activation() const; // Returns activation value of the Neuron (a)
    double Get_PreActivation() const; // Returns result of weighted sum added to bias term (z)
    int Get_Weight_Count() const; // Returns amount of weights attached to neuron
    int Get_Input_Count() const; // Returns amount of inputs attached to neuron
};

double Neuron::Random_Weight(int decimals) const
{
    return (rand() % static_cast<int>(pow(10, decimals)*2) - (pow(10, decimals))) / pow(10, decimals); // return random value between -1 and 1 with certain number of decimals
}

double Neuron::Random_Bias(int decimals) const
{
    return (rand() % static_cast<int>(pow(10, decimals)*2) - (pow(10, decimals))) / pow(10, decimals); // return random value between -1 and 1 with certain number of decimals
}

void Neuron::Create_Neuron(int weights_count, int activation_function_type)
{
    num_weights = weights_count; // set the Neuron's number of weights equal to the weights_count parameter
    activation_function = new ActivationFunction; // Initialize activation_function with a new dynamically created ActivationFunction 
    (*activation_function).Set_Activation_Function(activation_function_type); // Set Neuron's Activation Function Type equal to the activation_function_type argument

    weights = new double[num_weights]; // dynamically allocate space for weights using num_weights

    inputs = new double[num_weights]; // dynamically allocate space for inputs using num_weights

    srand(time(0)); // seed the random function using the current tume

    bias = Random_Bias(NUM_DECIMALS); // initialize bias to random value (-1, 1)

    for(int w = 0; w < num_weights; w++) // loop through all weights
    {
        *(weights + w) = Random_Weight(NUM_DECIMALS); // initialize all weights with a random value (-1, 1)
    }

}

void Neuron::Destroy_Neuron()
{
    bias = 0; // set bias to zero
    num_weights = 0; // set number of weights to zero    
    delete weights; // free dynamic memory used by weights
}

void Neuron::Set_Bias(double bias_setter)
{
    bias = bias_setter; // set bias equal to bias_setter argument
}

void Neuron::Set_Weights(double* weight_values_address)
{
   for(int w = 0; w < num_weights; w++) // loop through all weights
    {
        *(weights + w) = *(weight_values_address + w); // set weights equal to input arguments
    }
}

void Neuron::Set_Inputs(double* input_values_address)
{
    for(int i = 0; i < num_weights; i++) // loop through all inputs
    {
        *(inputs + i) = *(input_values_address + i); // set inpput equal to input arguments
    }
}

void Neuron::Set_Neuron_Activation_Function(int typeofactivationfunction)
{
    (*activation_function).Set_Activation_Function(typeofactivationfunction); // set the Neuron's activation function equal to the the argument
}

double Neuron::Get_Bias() const
{
    return bias; // return bias value
}

double* Neuron::Get_Weights() const
{
    return weights; // return address of weights
}

double* Neuron::Get_Inputs() const
{
    return inputs; // return inputs
}

int Neuron::Get_Activation_Function() const
{
    return (*activation_function).Get_Activation_Function(); // return activation function type
}

string Neuron::Get_Activation_Function_Name() const
{
    string activation_function_name = ""; // create string to store name of activation function
    switch ((*activation_function).Get_Activation_Function()) // check which type of activation function it is
    {
        case 0 : activation_function_name = "SIGMOID"; // set activation_function_name equal to SIGMOID 
                 break;
        case 1 : activation_function_name = "TANH"; // set activation_function_name equal to TANH
                 break;
    };

    return activation_function_name; // return activation_function_name
}

double Neuron::Get_Activation() const
{
    double weighted_sum = 0; // create value to store weighted sum

    for(int j = 0; j < num_weights; j++) // loop through all the weights
    {
        weighted_sum += (*(weights + j)) * (*(inputs + j)); // add value product of weight and input to weighted sum
    }

    return (*activation_function).Evaluate_Activation_Function_At(weighted_sum + bias); // return activation
}

double Neuron::Get_PreActivation() const
{
    double weighted_sum = 0; // create value to store weighted sum

    for(int j = 0; j < num_weights; j++) // loop through all the weights
    {
        weighted_sum += (*(weights + j)) * (*(inputs + j)); // add value product of weight and input to weighted sum
    }

    return weighted_sum; // return weighted sum
}

int Neuron::Get_Weight_Count() const
{
    return num_weights; // returns number of weights of neuron
}

int Neuron::Get_Input_Count() const
{
    return num_weights; // returns number of inputs of neuron
}

class Layer
{
    private : 
    int layer_size = 0; // stores amount of neurons in the layer
    Neuron* neurons = 0; // stores all the neurons in the layer
    public : 
    void Create_Layer(int, int, int); // method for instantiating a new layer
    void Destroy_Layer(); // method for removing layer from memory
    void Set_Activation_Function_At(int, int); // mutator method for specific neuron in Layer's activation function
    void Set_Bias_At(int, double); //mutator method for bias of specific neuron in layer
    void Set_Weights_At(int, double*); //mutator method for weights of a specific neuron in layer
    void Set_Inputs_At(int, double*); //mutator method for input to specific neuron in layer
    double* Get_Weights_At(int) const; // accessor method for weights of a specific neuron in the layer
    double Get_Bias_At(int) const; // accessor method for bias of specific neuron in layer
    int Get_Activation_Function_At(int) const; // accessor method for activation function of specific neuron in layer
    string Get_Activation_Function_Name_At(int) const; // accessor method for activation function's name of specific neuron in layer
    double Get_Activation_At(int) const; //accessor method for activation of specific neuron in layer
    double Get_PreActivation_At(int) const; // accessor method for preactivation of specific neuron in layer
    int Get_Layer_Size() const; //accessor method for size of layer
    double* Get_Inputs_At(int) const; //accessor method for inputs to specific neuron in layer
    int Get_Weights_Count_At(int) const; // get number of weights of neuron in layer 
    int Get_Inputs_Count_At(int) const; // get number of inputs to neuron in layer
};

void Layer::Create_Layer(int sizeoflayer, int inputcount, int activation_func)
{
    layer_size = sizeoflayer; // set layer_size equal to input argument

    neurons = new Neuron[layer_size]; // create space dynamically for all neurons in layer

    for(int n = 0; n < layer_size; n++) // loop through all neurons in layer
    {
        (*(neurons + n)).Create_Neuron(inputcount, activation_func); // initialize all neurons in layer with given number of inputs and activation function
    }
}

void Layer::Destroy_Layer()
{
    layer_size = 0; // set the layer's size to zero
    delete neurons; // free up memory allocated to neurons in layer
}

void Layer::Set_Activation_Function_At(int index, int activation_func)
{
     (*(neurons + index)).Set_Neuron_Activation_Function(activation_func); // set specific neuron in layer to have specific activation function
}

void Layer::Set_Bias_At(int index, double bias)
{
    (*(neurons + index)).Set_Bias(bias); // set bias of specific neuron in layer
}

void Layer::Set_Weights_At(int index, double* input_weights)
{
     (*(neurons + index)).Set_Weights(input_weights); // set neuron's weight to input_weights
}

void Layer::Set_Inputs_At(int index, double* neuron_inputs)
{
     (*(neurons + index)).Set_Inputs(neuron_inputs); // set inputs to specific neurons
}

double* Layer::Get_Weights_At(int index) const
{
    return  (*(neurons + index)).Get_Inputs(); // return list of inputs to neuron
}

double Layer::Get_Bias_At(int index) const
{
    return  (*(neurons + index)).Get_Bias(); // return bias of neuron
}

double* Layer::Get_Inputs_At(int index) const
{
    return  (*(neurons + index)).Get_Inputs(); // return number of inputs to neuron
}

int Layer::Get_Activation_Function_At(int index) const
{
    return  (*(neurons + index)).Get_Activation_Function(); //get activation function at specific neuron
}

string Layer::Get_Activation_Function_Name_At(int index) const
{
    return (*(neurons + index)).Get_Activation_Function_Name(); // return name of neuron's activation function
}

double Layer::Get_Activation_At(int index) const
{
    return (*(neurons + index)).Get_Activation(); // get activation of specific neuron in layer
}

double Layer::Get_PreActivation_At(int index) const
{
    return (*(neurons + index)).Get_PreActivation(); // return preactivation of neuron
}

int Layer::Get_Layer_Size() const
{
    return layer_size; // return size of layer
}

int Layer::Get_Inputs_Count_At(int index) const
{
    return (*(neurons + index)).Get_Input_Count(); // return number of inputs to specific neuron
}

int Layer::Get_Weights_Count_At(int index) const
{
    return (*(neurons + index)).Get_Weight_Count(); //return the number of weights neuron has
}

class NeuralNetwork
{

};