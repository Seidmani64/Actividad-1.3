#include <iostream>
#include <vector>
#include <fstream>
#include <regex>
#include <stack>
#include <queue>
#include "analytics.cpp"
#include "log.cpp"
#include "conexiones.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Programa para recibir datos de una computadora del sistema                //
//y guardar la informacion dentro de estructuras lineales apropiadas        //
//con el fin de reflexionar informacion particular de la computadora        //
//                                                                          //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Fecha de creacion 12/10/2020                                              //
//////////////////////////////////////////////////////////////////////////////

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
    userIP += to_string(userInput);
    string fullName = "";
    fullName = my_analitic.get_computer_name(userIP);
    string name = fullName.substr(0, fullName.find(".", 0));
    ConexionesComputadora<string> userPC(userIP,name);

    //Llenar ConexionesEntrantes
    stack<string> entryConnections = my_analitic.get_entry_connections(userIP);
    userPC.setConexionesEntrantes(entryConnections);

    while(!entryConnections.empty())
    {
        cout<<"Testing entryConnections val: "<<entryConnections.top()<<endl;
        entryConnections.pop();
    }

    cout<<"Testing getConexionEntrante()  result is: "<<userPC.getConexionEntrante()<<endl;

    //Llenar ConexionesSalientes
    queue<string> exitConnections = my_analitic.get_exit_connections(userIP);
    userPC.setConexionesSalientes(exitConnections);

    while(!exitConnections.empty())
    {
        cout<<"Testing exitConnections val: "<<exitConnections.front()<<endl;
        exitConnections.pop();
    }

    cout<<"Testing getConexionSaliente() result is: "<<userPC.getConexionSaliente()<<endl;

    return 0;
}