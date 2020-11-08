#ifndef _CONEXIONES_H
#define _CONEXIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list> //doubly linked list
#include "analytics.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Header para clase ConexionesComputadora con el proposito de guardar       //
//las instancias del .csv donde el ip del usuario es la fuente y otras      //
// donde la misma es el destino, en estructuras lineales correspondientes   //
//                                                                          //
//Se utilizo para responder las preguntas 4-6 de la actividad 3             //
//                                                                          //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Fecha de modificacion 07/11/2020                                          //
//////////////////////////////////////////////////////////////////////////////

template <typename T>
class ConexionesComputadora
{
private:
    string ip;
    string nombre;
    stack<T> conexionesEntrantes;
    queue<T> conexionesSalientes;

public:
    ConexionesComputadora(string _ip, Analytics *data)
    {
        ip = _ip;

        string compareVal = "";
        for (int i = 0; i < data->length(); i++)
        {
            compareVal = data->get_registry(i).get_dst_ip();

            if (compareVal == ip)
            {
                conexionesEntrantes.push(data->get_registry(i).get_src_ip());
            }

            compareVal = data->get_registry(i).get_src_ip();
            if (compareVal == ip)
            {
                conexionesSalientes.push(data->get_registry(i).get_dst_ip());
            }
        }
    };

    ~ConexionesComputadora(){};

    //Metodo para recibir el IP de conexion entrante hasta arriba
    //No tiene parametro
    //Regresa el valor T hasta arriba de la pila
    T getConexionEntrante()
    {
        T value = conexionesEntrantes.top();
        conexionesEntrantes.pop();
        return value;
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

    //Metodo para recibir la conexion saliente mas atras
    //No tiene parametro
    //Regresa el valor T hasta en atras de la pila
    T getUltimaConexionSaliente()
    {
        T value = conexionesSalientes.back();
        conexionesSalientes.pop();
        return value;
    }

    //Metodo para imprimir las conexiones salientes
    //No tiene parametro
    //No regresa nada, solo imprime a la terminal todas las conexiones salientes
    void printConexionSaliente()
    {
        while (!conexionesSalientes.empty())
        {
            cout << conexionesSalientes.front() << endl;
            conexionesSalientes.pop();
        }
    }

    //Metodo para imprimir las conexiones entrantes
    //No tiene parametro
    //No regresa nada, solo imprime a la terminal todas las conexiones entrantes
    void printConexionEntrante()
    {
        cout << conexionesEntrantes.size() << endl;
        while (!conexionesEntrantes.empty())
        {
            cout << conexionesEntrantes.top() << endl;
            conexionesEntrantes.pop();
        }
    }

    //Metodo para regresar la cantidad de elementos en conexiones entrantes
    //No tiene parametro
    //Regresa un valor int de la cantidad de elementos en conexiones entrantes
    int conexionEntranteSize()
    {
        return conexionesEntrantes.size();
    }

    //Metodo para regresar la cantidad de elementos en conexiones salientes
    //No tiene parametro
    //Regresa un valor int de la cantidad de elementos en conexiones salientes
    int conexionSalienteSize()
    {
        return conexionesSalientes.size();
    }
};

#endif