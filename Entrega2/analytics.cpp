#include "analytics.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Programa para leer del csv y guardarlo en una clase log                   //
//con el proposito de poder sacar datos de cada registro y poder comparar   //
//y buscar instancias o valores particulares dentro del csv                 //
//Autor Original: Leonardo Chang                                            //                                                                          
//                                                                          //
//Autores de modificaciones:                                                //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Fecha de modificacion 12/10/2020                                          //
//////////////////////////////////////////////////////////////////////////////

Analytics::~Analytics()
{}

Analytics::Analytics()
{}

//Metodo para leer datos del csv a traves de getline y guardarlos en un objeto
//de tipo Log, luego dentro de un vector data
//Tiene como parametro un string de la ubicacion del archivo csv
//Regresa un int -1 si hubo un error y un 1 si logro cargar los datos
int Analytics::load_data_from_csv(std::string path)
{
    ifstream file(path);
    if (!file.is_open())
        return -1;
    
    string line, a1, a2, a3, a4, a5, a6, a7, a8;
    while (getline(file, line))
    {
        stringstream ss(line);
        getline(ss, a1, ',');
        getline(ss, a2, ',');
        getline(ss, a3, ',');
        getline(ss, a4, ',');
        getline(ss, a5, ',');
        getline(ss, a6, ',');
        getline(ss, a7, ',');
        getline(ss, a8, ',');

        Log alog(a1, a2, a3, a4, a5, a6, a7, a8);
        data.push_back(alog);
    }
    return 1;
}

//Metodo para imprimir cada registro en una linea
//No tiene parametros
//No regresa un valor, solo imprime en la terminal
void Analytics::print_data()
{
    for (size_t i = 0; i < data.size(); i++)
    {
        data[i].print();
    }    
}

//Metodo para encontra la cantidad de registros en el csv
//No tiene parametros
//Regresa un int de la cantidad de registros
int Analytics::length() 
{
    return data.size();
}

//Metodo para recibir objeto Log de una linea del registro
//Tiene como parametro el indice del registro
//Regresa un objeto Log del indice de registro
Log Analytics::get_registry(int idx)
{
    return data[idx];
}

//Metodo para encontrar el usuario asociado con un ip fuente
//Tiene como parametro un string de la ip fuente
//Regresa un string del nombre completo(incluyendo.reto) o NULL si no se encontro
std::string Analytics::get_computer_name(std::string ip)
{
    Search<Log> my_search;
        Log dummy_log;
        dummy_log.set_src_ip(ip);
        int search_res = my_search.search_sequential(data, dummy_log, &Log::compare_src_ip);
        if (search_res >= 0)
            return data[search_res].get_src_hostname();    
    return "NULL";
}


//Metodo para llenar una pila con las conexiones entrantes
//Tiene como parametro un string de la ip fuente
//Regresa una pila de conexiones entrantes(strings de ip)
std::stack<std::string> Analytics::get_entry_connections(std::string ip, int &lastEntry)
{
    std::stack<std::string> connections;
    string compareVal = "";
    for(int i = 0; i < data.size(); i++)
    {
        compareVal = data[i].get_dst_ip();
        if(compareVal == ip)
        {
            connections.push(data[i].get_src_ip());
            lastEntry = i;
        }
    }
        
    return connections;
}

//Metodo para llenar una cola con las conexiones salientes
//Tiene como parametro un string de la ip fuente
//Regresa una cola de conexiones salientes(strings de ip)
std::queue<std::string> Analytics::get_exit_connections(std::string ip, int &lastExit, bool &threeConsecutive, std::string &threeConsecutiveIp)
{
    std::queue<std::string> connections;
    string compareVal = "";
    string temp = data[0].get_dst_ip();;
    int count = 0;
    threeConsecutive = false;
    for(int i = 0; i < data.size(); i++)
    {
        compareVal = data[i].get_src_ip();
        if(compareVal == ip)
        {
            connections.push(data[i].get_dst_ip());
            lastExit = i;
            temp = data[i].get_dst_ip();

            if(data[i].get_dst_ip() == temp)
            {
                count ++;
                if(count == 3)
                {
                threeConsecutive = true;
                threeConsecutiveIp = data[i].get_dst_ip();
                }
            }
        }
        
        temp = data[i].get_dst_ip();
    }
        
    return connections;
}

