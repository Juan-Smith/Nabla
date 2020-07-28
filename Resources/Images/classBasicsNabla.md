```mermaid
 classDiagram
      
      NeuralNetwork --> Layer : Contains
      Layer --> Neuron : Contains
      NeuralNetwork --> ActivationFunction : Contains
      Neuron --> ActivationFunction : Contains
      
      class NeuralNetwork{
          -double learningrate
          -Layer* layers
          +void SetLearningRate()
          +void SetLayers()
          +double* Predict()
          +void Train()
      }
      
      class Layer{
          -Neuron* neurons
          -int layer_size
          +int GetSize()
          +void SetSize()
      }
      
      class Neuron{
      	-Activation* activation_function
        -double bias
        -double* weights
        -double output
        +double GetOutput()
        +double* GetWeights()
        +double GetBias()
        +void SetOutput()
        +void SetWeights()
        +void SetBias()
	  }
      
      
      class ActivationFunction{
          -int activation_function_type
          +void Set_Activation_Function(int)
          +double Evaluate_Activation_Function_At(double)
          +double Evaluate_Activation_Derivative_At(double)
      }
      
```

