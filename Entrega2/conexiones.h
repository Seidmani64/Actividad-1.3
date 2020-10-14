#ifndef _CONEXIONES_H
#define _CONEXIONES_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <list> //doubly linked list

using namespace std;

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

};







#endif