#include "log.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Programa para guardar cada registro del csv como un ADT y poder           //
//utilizarlo dentro de la clase analytics para buscar y modificar           //
//cada registro individualmente a traves de comparacion de logs             //
//                                                                          //
//Autor Original: Leonardo Chang                                            //                                                                          //
//                                                                          //
//Autores de modificaciones:                                                //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Fecha de modificacion 12/10/2020                                          //
//////////////////////////////////////////////////////////////////////////////

Log::~Log()
{}

Log::Log()
{
    date = "";
    time = "";
    src_ip = "";
    src_port = "";
    src_hostname = "";
    dst_ip = "";
    dst_port = "";
    dst_hostname = "";
}

Log::Log(std::string pdate,
        std::string ptime,
        std::string psrc_ip,
        std::string psrc_port,
        std::string psrc_hostname,
        std::string pdst_ip,
        std::string pdst_port,
        std::string pdst_hostname)
{
    date = pdate;
    time = ptime;
    src_ip = psrc_ip;
    src_port = psrc_port;
    src_hostname = psrc_hostname;
    dst_ip = pdst_ip;
    dst_port = pdst_port;
    dst_hostname = pdst_hostname;
}

void Log::print()
{
    cout << date << ", ";
    cout << time << ", ";
    cout << src_ip << ", ";
    cout << src_port << ", ";
    cout << src_hostname << ", ";
    cout << dst_ip << ", ";
    cout << dst_port << ", ";
    cout << dst_hostname << endl;
}

bool Log::compare_src_hostname(Log &a, Log &b)
{
    stringstream ssa(a.get_src_hostname());
    string h1, h2;
    getline(ssa, h1, '.');
    stringstream ssb(b.get_src_hostname());
    getline(ssb, h2, '.');
    
    return h1 == h2;
}

//Metodo para comparar los IPs fuente de dos logs a traves de los getters
//de los mismos logs, usualmente utilizando un log dummy con un solo valor de ip
bool Log::compare_src_ip(Log &a, Log &b)
{
    stringstream ssa(a.get_src_ip());
    string h1, h2;
    getline(ssa, h1, ',');
    stringstream ssb(b.get_src_ip());
    getline(ssb, h2, ',');
    
    return h1 == h2;
}


//Metodo para comparar los IPs destino de dos logs a traves de los getters
//de los mismos logs, usualmente utilizando un log dummy con un solo valor de ip
bool Log::compare_dst_ip(Log &a, Log &b)
{
    stringstream ssa(a.get_dst_ip());
    string h1, h2;
    getline(ssa, h1, ',');
    stringstream ssb(b.get_dst_ip());
    getline(ssb, h2, ',');
    
    return h1 == h2;
}

bool Log::compare_equal_than(int &a, int &b)
{
    return a == b;
}
