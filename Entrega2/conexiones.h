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

    //Metodo para recibir el IP de conexion entrante hasta arriba
    //No tiene parametro
    //Regresa el valor T hasta arriba de la pila
    T getConexionEntrante()
    {
        T value = conexionesEntrantes.top();
        conexionesEntrantes.pop();
        return value;
    }

    //Metodo para poner un valor T hasta arriba de la pila
    //Toma como parametro el valor en T
    //No regresa nada
    void setConexionEntrante(T val)
    {
        conexionesEntrantes.push(val);
    }

    //Metodo para poner la pila como conexionesEntrantes directamente
    //Toma como parametro una pila de T de las conexiones
    //No regresa nada
    void setConexionesEntrantes(stack<T> connections)
    {
        conexionesEntrantes = connections;
    }

    //Metodo para recibir el IP de conexion saliente hasta en frente
    //No tiene parametro
    //Regresa el valor T hasta en frente de la cola
    T getConexionSaliente()
    {
        T value = conexionesSalientes.front();
        conexionesSalientes.pop();
        return value;
    }

    //Metodo para poner un valor T hasta en frente de la cola
    //Toma como parametro el valor en T
    //No regresa nada
    void setConexionSaliente(T val)
    {
        conexionesSalientes.push(val);
    }

    //Metodo para poner la cola como conexionesSalientes directamente
    //Toma como parametro una cola de T de las conexiones
    //No regresa nada
    void setConexionesSalientes(queue<T> connections)
    {
        conexionesSalientes = connections;
    }

};







#endif