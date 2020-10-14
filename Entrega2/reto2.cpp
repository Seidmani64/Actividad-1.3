#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include "analytics.h"
#include "analytics.cpp"
#include "log.cpp"

using namespace std;

int main()
{
    //Load Files
    Analytics my_analitic;
    
    if (my_analitic.load_data_from_csv("../equipo9.csv") > 0)
        cout << "Loaded data." << endl;
    else
    {
        cout << "ERROR loading input file... Exiting program...";
        return 0;
    }

    //Inicializacion de ConexionesComputadora
    int userInput;
    cout<<"Elige un numero entre 1 y 150: ";
    cin>>userInput;
    cout<<""<<endl;
    string userIP = "172.23.5.";
    userIP+=to_string(userInput);
    string fullName = "";
    fullName = my_analitic.get_computer_name(userIP);
    string name = fullName.substr(0, fullName.find(".", 0));
    cout<<"The user's name is: "<<name<<endl;

    return 0;
}