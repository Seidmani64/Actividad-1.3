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

//Metodo para recibir string del IP de un dominio
//Tiene como parametro el nombre del dominio
//Regresa un string del IP del dominio
std::string Analytics::get_domain_ip(std::string domain)
{
    std::string compareVal = "";
    for(int i = 0; i < data.size(); i++)
    {
        compareVal = data[i].get_dst_hostname();
        if(compareVal == domain)
            return data[i].get_dst_ip();
    }
    return "Not Found";
}

std::vector<std::string> Analytics::get_non_domain_names()
{
    std::vector<std::string> names;
    std::string domain = "reto.com";
    std::string computer_name;
    std::string domain_name;
    std::string temp_cn;
    std::string temp_dn;

    for(int i = 0; i < data.size(); i++)
    {
        computer_name = data[i].get_src_hostname();
        domain_name = data[i].get_dst_hostname();
        temp_cn = computer_name.substr(computer_name.find('.') + 1);
        temp_dn = domain_name.substr(domain_name.find('.') + 1);
        if(domain.compare(temp_cn) != 0)
            if(computer_name != "-")
                names.push_back(computer_name);
        if(domain.compare(temp_dn) != 0)
            if(domain_name != "-")
                names.push_back(domain_name);

    }

    return names;
}

//Metodo para llenar una pila con las conexiones entrantes
//Tiene como parametro un string de la ip fuente
//Regresa una pila de conexiones entrantes(strings de ip)
std::vector<std::string> Analytics::get_entry_connections(std::string ip)
{
    std::vector<std::string> connections;
    string compareVal = "";
    for(int i = 0; i < data.size(); i++)
    {
        compareVal = data[i].get_dst_ip();
        if(compareVal == ip)
            connections.push_back(data[i].get_src_ip());
    }
        
    return connections;
}

