#include<iostream>
#include "Nabla.h"

using namespace std;

int main()
{
    ActivationFunction myActivationfunction;
    myActivationfunction.Set_Activation_Function(0);

    cout << "SIGMOID" << endl;
    cout << "Function:" << myActivationfunction.Evaluate_Activation_Function_At(-2) << endl;
    cout << "Derivative: " << myActivationfunction.Evaluate_Activation_Derivative_At(-2) << endl;
    cout << "TANH" << endl;
    myActivationfunction.Set_Activation_Function(1);
    cout << "Function:" << myActivationfunction.Evaluate_Activation_Function_At(-2) << endl;
    cout << "Derivative: " << myActivationfunction.Evaluate_Activation_Derivative_At(-2) << endl; 

    return 0;
}