#include<iostream>
#include<cmath>
using namespace std;
int main(){
  //defining variables
  string operation;
  double number1,number2;
  //get the user input
  cout<<"Enter first number: ";
  cin>>number1;
  cout<<"Enter Operation(+,-,*,/): ";
  cin>>operation;
  cout<<"Enter second number:  ";
  cin>>number2;
  //if else statement checking entered operation
  if(operation=="+"){
    cout<<number1+number2; 
    }
    else if(operation=="-"){
      cout<<number1-number2;
    }
     else if(operation=="*"){
      cout<<number1*number2;
    }
     else if(operation=="/"){
      cout<<number1/number2;
    }
    else{
      cout<<"unrecognisable operation";
    }



  return 0;

}