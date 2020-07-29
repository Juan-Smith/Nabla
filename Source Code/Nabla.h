#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

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

    return weighted_sum + bias; // return weighted sum plus bias
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
    private : 
        int num_layers = 0;
        Layer* layers = 0;
        bool Check_Valid(int, int, int); // check if network structure is valid
    public :
        void Create_Neural_Network(int*, int, int); // create Neural Network
        void Destroy_Neural_Network(); // free up memory allocated to the neural network
        void Set_Activation_Function_At_Neuron(int, int, int); // set activation function of specific neuron in network
        void Set_Activation_Function_At_Layer(int, int); // mutator method for layer's activation function
        void Set_Bias_At_Neuron(int, int, double); // mutator method to alter state of particular neuron's bias
        void Set_Bias_At_Layer(int, double*); // mutator method for layer's bias terms
        void Set_Weights_At_Neuron(int, int, double*); // mutator method for neuron's weights
        void Set_Weights_At_Layer(int, double**); // mutator method to alter weights of entire layer 
        void Set_Inputs_At_Neuron(int, int, double*); // mutator method to alter particular neuron's inputs
        void Set_Inputs_At_Layer(int, double**); // mutator method to alter layer's inputs
        double* Get_Weights_At_Neuron(int, int) const; // accessor method for neuron's weights
        double* Get_Inputs_At_Neuron(int, int) const; //accessor methods for neurons inputs
        int Get_Activation_Function_At_Neuron(int, int) const; //accessor method for neuron's activation function
        double Get_Bias_At_Neuron(int, int) const; // accessor method for particular neuron's bias
        string Get_Activation_Function_Name_At_Neuron(int, int) const; // get name of particular neuron's activation function
        double Get_Activation_At_Neuron(int, int) const; // get neuron's activation
        double Get_PreActivation_At_Neuron(int, int) const; // get neuron's preactivation
        int Get_Layer_Size_At(int) const; // get size of layer in network
        int Get_Weights_Count_At_Neuron(int, int) const; // get number of weights from neuron
        int Get_Inputs_Count_At_Neuron(int, int) const; // get number of inputs to neuron
        int Get_Inputs_Count_At_Network() const; // get number of inputs to network
        int Get_Outputs_Count_At_Network() const; // get number of ouptus from network
        double* Prediction(double*) const; // prediction of neural network
        void Train(double*, double*); // train neural network
        enum ActivationFunctions {SIGMOID = 0, TANH = 1};
};

bool NeuralNetwork::Check_Valid(int inputcount, int outputcount, int hiddenlayercount)
{
    bool return_value = 1;

    if(inputcount < 1)
    {
        return_value = 0;
        cout << "INVALID INPUT, NUMBER OF INPUTS MUST BE AT LEAST 1" << endl;
    }
    else if(outputcount < 1)
    {
        return_value = 0;
        cout << "INVALID INPUT, NUMBER OF OUTPUTS MUST BE AT LEAST 1" << endl;
    }
    else if(hiddenlayercount < 0)
    {
        return_value = 0;
        cout << "INVALID INPUT, NUMBER OF HIDDEN LAYERS MUST BE AT LEAST 0" << endl;
    }
    
}

void NeuralNetwork::Create_Neural_Network(int* layersizes, int layerscount, int activation_function)
{
    int numinputs = *layersizes;
    int numoutputs = *(layersizes + (layerscount - 1));

    if(Check_Valid(numinputs, numoutputs, layerscount - 2)) // check if network structure is valid
    {

        layers = new Layer[layerscount]; // allocate space for networks layers

        (*layers).Create_Layer(*layersizes, 1, activation_function);

        for(int l = 1; l < layerscount; l++) // loop through all layers except first
        {
            (*(layers + l)).Create_Layer(*(layersizes + l), *(layersizes + (l-1)), activation_function); // initialize dense layers
        }

        double* inputweights = new double;
        *inputweights = 1;

        for(int f = 0; f < (*layers).Get_Layer_Size(); f++) // loop through all neurons in input layer
        {
            (*layers).Set_Bias_At(f, 0.0); // set biases of all input neurons to 0
            (*layers).Set_Weights_At(f, inputweights); // set weights of all neurons in first layer to 1
        }
    }
}

void NeuralNetwork::Destroy_Neural_Network()
{
    num_layers = 0; //set number of layers to zero
    delete layers; // free space taken by network's layers
}

void NeuralNetwork::Set_Activation_Function_At_Neuron(int layer, int index, int activationfunction)
{
    (*(layers + layer)).Set_Activation_Function_At(index, activationfunction);
}

void NeuralNetwork::Set_Activation_Function_At_Layer(int layer, int activationfunction)
{
    for(int n = 0; n < (*(layers + layer)).Get_Layer_Size(); n++)
    {
        (*(layers + layer)).Set_Activation_Function_At(n, activationfunction);
    }
}

void NeuralNetwork::Set_Bias_At_Neuron(int layer, int index, double bias)
{
     (*(layers + layer)).Set_Bias_At(index, bias);
}

void NeuralNetwork::Set_Bias_At_Layer(int layer, double* biases)
{
    for(int n = 0; n < (*(layers + layer)).Get_Layer_Size(); n++)
    {
        (*(layers + layer)).Set_Bias_At(n, *(biases + n));
    }
}

void NeuralNetwork::Set_Weights_At_Neuron(int layer, int index, double* weights)
{
    (*(layers + layer)).Set_Weights_At(index, weights);
}

void NeuralNetwork::Set_Weights_At_Layer(int layer, double** weights)
{
     for(int n = 0; n < (*(layers + layer)).Get_Layer_Size(); n++)
    {
        (*(layers + layer)).Set_Weights_At(n, *(weights + n));
    }
}

void NeuralNetwork::Set_Inputs_At_Neuron(int layer, int index, double* inputs)
{
     (*(layers + layer)).Set_Inputs_At(index, inputs);
}

void NeuralNetwork::Set_Inputs_At_Layer(int layer, double** inputs)
{
    for(int n = 0; n < (*(layers + layer)).Get_Layer_Size(); n++)
    {
        (*(layers + layer)).Set_Inputs_At(n, *(inputs + n));
    }
}

double* NeuralNetwork::Get_Weights_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Weights_At(index);
}

double* NeuralNetwork::Get_Inputs_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Inputs_At(index);
}

int NeuralNetwork::Get_Activation_Function_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Activation_Function_At(index);
}

double NeuralNetwork::Get_Bias_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Bias_At(index);
}

string NeuralNetwork::Get_Activation_Function_Name_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Activation_Function_Name_At(index);
}

double NeuralNetwork::Get_Activation_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Activation_At(index);
}

double NeuralNetwork::Get_PreActivation_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_PreActivation_At(index);
}

int NeuralNetwork::Get_Layer_Size_At(int layer) const
{
    return  (*(layers + layer)).Get_Layer_Size();
}

int NeuralNetwork::Get_Weights_Count_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Weights_Count_At(index);
}

int NeuralNetwork::Get_Inputs_Count_At_Neuron(int layer, int index) const
{
    return (*(layers + layer)).Get_Inputs_Count_At(index);
}

int NeuralNetwork::Get_Inputs_Count_At_Network() const
{
    return (*layers).Get_Layer_Size();
}

int NeuralNetwork::Get_Outputs_Count_At_Network() const
{
    return (*(layers + (num_layers - 1))).Get_Layer_Size();
}

double* NeuralNetwork::Prediction(double* inputs) const
{

}

void NeuralNetwork::Train(double* inputs, double* correct_outputs)
{

}
