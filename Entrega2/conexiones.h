#ifndef _CONEXIONES_H
#define _CONEXIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list> //doubly linked list

using namespace std;

class ConexionesComputadora
{
private:
    string ip;
    string nombre;
    //stack, queue o list <string> conexionesEntrantes;
    //stack, queue o list <string> conexionesSalientes;

public:
    ConexionesComputadora(string _ip, string _nombre) {
        ip = _ip;
        nombre = _nombre;
    };
    ~ConexionesComputadora() {};
};







#endif