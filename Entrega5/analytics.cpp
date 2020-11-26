#include "analytics.h"


using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Programa para leer del csv y guardarlo en una clase log                   //
//con el proposito de poder sacar datos de cada registro y poder comparar   //
//y buscar instancias o valores particulares dentro del csv                 //
//Nuevos metodos fueron agregados para crear grafos y analizarlos           //
//Autor Original: Leonardo Chang                                            //                                                                          
//                                                                          //
//Autores de modificaciones:                                                //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Fecha de modificacion 26/11/2020                                          //
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
string Analytics::get_domain_ip(string domain)
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

//Metodo para encontrar todas las fechas del .csv
//No tiene parametro
//Regresa un vector de strings de cada fecha
vector<string> Analytics::get_all_dates()
{
    vector<string> dates;
    for(int i = 0; i < data.size(); i++)
        if(find(dates.begin(),dates.end(),data[i].get_date())==dates.end())
            dates.push_back(data[i].get_date());
        
    return dates;
}

//Metodo para crear un grafo de las conexiones internas de una fecha
//Tiene como parametro un string de la fecha
//Regresa un grafo de strings en la que los nodos tienen valor de string IP y las aristas son sus conexiones
Graph<string> Analytics::get_connections_graph(string date)
{
    Graph<string> graph(true);
    string ipInterna = "172.23.5.";
    string ipSrcCompare = "";
    string ipDstCompare = "";
    int srcIdx = -1;
    int dstIdx = -1;
    for(int i = 0; i < data.size(); i++)
    {
        ipSrcCompare = data[i].get_src_ip();
        ipSrcCompare = ipSrcCompare.substr(0, ipSrcCompare.find(".", 7)+1);
        ipDstCompare = data[i].get_dst_ip();
        ipDstCompare = ipDstCompare.substr(0, ipDstCompare.find(".", 7)+1);



        if(((ipSrcCompare.compare(ipInterna)==0)&&(ipDstCompare.compare(ipInterna)==0))&&(data[i].get_date().compare(date)==0))
        {
            srcIdx = graph.add_node(data[i].get_src_ip());
            dstIdx = graph.add_node(data[i].get_dst_ip());
            graph.add_edge(srcIdx,dstIdx);
        }


    }

    return graph;
}

//Metodo para encontrar la cantidad de conexiones salientes que tiene una ip
//Tiene como parametro un grafo de strings de todas las conexiones y un string de la ip
//Regresa un int de la cantidad de conexiones salientes de la ip
int Analytics::get_connections_per_day(Graph<string> graph, string ip)
{
    for(int i = 0; i < graph.get_nodes().size(); i++)
    {
        if(ip.compare(graph.get_nodes()[i].get_val())== 0)
            return graph.get_nodes()[i].get_adj().size();
    }
    return 0;
}

//Metodo para revisar si una ip tiene la mayor cantidad de conexiones salientes del grafo
//Tiene como parametro el grafo de las conexiones y un string de la ip
//No regresa nada, pero imprime a la terminal un mensaje correspondiente si tiene la mayor cantidad o no
void Analytics::is_most_connected(Graph<string> graph, string ip)
{
    int originalConnections = get_connections_per_day(graph, ip);
    int compareConnections = -1;
    bool nothing_printed = true;
    for(int i = 0; i < graph.get_nodes().size(); i++)
    {
        compareConnections = get_connections_per_day(graph,graph.get_nodes()[i].get_val());
        if((compareConnections >= originalConnections)&&(graph.get_nodes()[i].get_val().compare(ip)!=0))
            {
                std::cout<<"The IP does not have the most connections per day."<<std::endl;
                nothing_printed = false;
                i = graph.get_nodes().size();
            }
    }
    if(nothing_printed)
        std::cout<<"The IP does have the most connections per day."<<std::endl;

}

//Metodo para encontrar la cantidad de conexiones entrantes de una ip
//Tiene como parametro el grafo de conexiones y un string de ip
//Regresa un int de la cantidad de conexiones entrantes de la ip
int Analytics::get_connected_per_day(Graph<string> graph, string ip)
{
    int ipIdx = -1;
    int count = 0;

    for(int i = 0; i < graph.get_nodes().size(); i++)
        if(graph.get_nodes()[i].get_val().compare(ip) == 0)
            ipIdx = i;

    for(int i = 0; i < graph.get_nodes().size(); i++)
        for(int j =0; j < graph.get_nodes()[i].get_adj().size();j++)
            if(graph.get_nodes()[i].get_adj()[j]==ipIdx)
                count++;
        

   
    return count;
}

//Metodo para crear un grafo de visitas de una pagina web por dia
//Tiene como parametro un string de la fecha
//Regresa un grafo de pairs de string,string en el que cada nodo es un par
//  La primer parte del par es un string de la IP de la computadora
//  La segunda parte del par es un string del hostname de la computadora
//  Cada arista son las conexiones entre computadoras
Graph<pair<string,string>> Analytics::get_webvisits_graph(string date)
{
    Graph<pair<string,string>> graph(true);
    pair<string,string> srcVal;
    pair<string,string> dstVal;
    string ipInterna = "172.23.5.";
    string webPort1 = "443";
    string webPort2 = "465";
    string webPort3 = "80";
    string webPort4 = "993";
    string portCompare = "";
    int srcIdx = -1;
    int dstIdx = -1;
    for(int i = 0; i < data.size(); i++)
    {
        portCompare = data[i].get_dst_port();

        if(((portCompare.compare(webPort1)==0)||(portCompare.compare(webPort2)==0)||(portCompare.compare(webPort3)==0)||(portCompare.compare(webPort4)==0))&&(data[i].get_date().compare(date)==0))
        {
            srcVal = make_pair(data[i].get_src_ip(),data[i].get_src_hostname());
            dstVal = make_pair(data[i].get_dst_ip(),data[i].get_dst_hostname());
            srcIdx = graph.add_node(srcVal);
            dstIdx = graph.add_node(dstVal);
            graph.add_edge(srcIdx,dstIdx);
        }


    }

    return graph;
}


//Metodo para encontrar el indice de una pagina web dentro del grafo
//Tiene como parametro el grafo de conexiones web de tipo pair<string,string> y un string del hostname de la pagina
//Regresa un int del indice del nodo con ese hostname dentro del grafo
int Analytics::get_site_idx(Graph<pair<string,string>> graph, string webName)
{
    int webIdx = -1;
    string webFound = "";

    for(int i = 0; i < graph.get_nodes().size(); i++)
    {
        webFound = graph.get_nodes()[i].get_val().second;
        if(webFound.compare(webName) == 0)
            webIdx = i;
    }

    return webIdx;
}

//Metodo para encontrar la cantidad de conexiones entrantes a un sitio 
//Tiene como parametro el grafo de las conexiones de tipo pair<string,string> y un int del indice del nodo con ese hostname
//Regresa un int de la cantidad de conexiones entrantes al sitio que le corresponda el indice
int Analytics::get_connected_to_site(Graph<pair<string,string>> graph, int idx)
{
    int count = 0;

    for(int i = 0; i < graph.get_nodes().size(); i++)
        for(int j =0; j < graph.get_nodes()[i].get_adj().size();j++)
            if(graph.get_nodes()[i].get_adj()[j]==idx)
                count++;
        

   
    return count;
}