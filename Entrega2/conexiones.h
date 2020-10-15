#ifndef _CONEXIONES_H
#define _CONEXIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list> //doubly linked list

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Header para clase ConexionesComputadora con el proposito de guardar       //
//las instancias del .csv donde el ip del usuario es la fuente y otras      //
// donde la misma es el destino, en estructuras lineales correspondientes   //
//                                                                          //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Fecha de creacion 12/10/2020                                              //
//////////////////////////////////////////////////////////////////////////////

template<typename T>
class ConexionesComputadora
{
private:
    string ip;
    string nombre;
    stack<T> conexionesEntrantes;
    queue<T> conexionesSalientes;

public:
    ConexionesComputadora(string _ip, string _nombre) {
        ip = _ip;
        nombre = _nombre;

    };
    ~ConexionesComputadora() {};

    T getConexionEntrante()
    {
        T value = conexionesEntrantes.top();
        conexionesEntrantes.pop();
        return value;
    }

    void setConexionEntrante(T val)
    {
        conexionesEntrantes.push(val);
    }

    void setConexionesEntrantes(stack<string> connections)
    {
        conexionesEntrantes = connections;
    }

    T getConexionSaliente()
    {
        T value = conexionesSalientes.front();
        conexionesSalientes.pop();
        return value;
    }

    void setConexionSaliente(T val)
    {
        conexionesSalientes.push(val);
    }

    void setConexionesSalientes(queue<string> connections)
    {
        conexionesSalientes = connections;
    }

};







#endif