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

    ////////////////// Pregunta 1 //////////////////
    cout << endl << "\tQuestion 1" << endl;

    //Inicializacion de ConexionesComputadora
    int userInput;
    int lastEntry;
    bool threeConsecutive;
    string threeConsecutiveIp;
    cout << "Choose a number between 1 and 150: ";
    cin >> userInput;
    string userIP = "172.23.5.";
    userIP += to_string(userInput);
    cout << "IP being used: " << userIP << endl;
    string fullName = "";
    fullName = my_analitic.get_computer_name(userIP);
    string name = fullName.substr(0, fullName.find(".", 0));

    ConexionesComputadora<string> userPC(userIP, name);

    //Llenar ConexionesEntrantes
    stack<string> entryConnections = my_analitic.get_entry_connections(userIP, lastEntry);
    userPC.setConexionesEntrantes(entryConnections);

    //Llenar ConexionesSalientes
    queue<string> exitConnections = my_analitic.get_exit_connections(userIP, threeConsecutive, threeConsecutiveIp);
    userPC.setConexionesSalientes(exitConnections);

    

    ////////////////// Pregunta 2 //////////////////
    cout << endl << "\tQuestion 2" << endl;
    cout << userPC.getConexionEntrante() << " -> Internal." << endl;
    
    ////////////////// Pregunta 3 //////////////////
    cout << endl << "\tQuestion 3" << endl;
    int numEntry = 0;
    while(!entryConnections.empty())
    {
        numEntry ++;
        entryConnections.pop();
    }

    cout << "Number of entry connections: " << numEntry << endl;

    ////////////////// Pregunta 4 //////////////////
    cout << endl << "\tQuestion 4" << endl;
    int numExit = 0;
    while(!exitConnections.empty())
    {
        numExit ++;
        exitConnections.pop();
    }

    cout << "Number of exit connections: " << numExit << endl;

    //////////////////   Extra    //////////////////
    cout << endl << "\tExtra" << endl;
    if(threeConsecutive)
        cout << "This computer had three consecutive connections to this ip: " << threeConsecutiveIp << endl;
    else
        cout << "This computer didn't have three consecutive connections to the same website." << endl;


    return 0;
}