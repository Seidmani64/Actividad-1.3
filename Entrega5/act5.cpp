#include "analytics.cpp"
#include "graph.h"
#include "analytics.h"
#include "log.cpp"
#include "log.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//Autores del Programa:                                                     //
//Ian Seidman Sorsby A01028650                                              //
//Gianluca Beltrán Bianchi A01029098                                        //
//                                                                          //
//Programa para realizar pruebas de la cantidad y tipos de conexiones       //
//dentro de un sistema a traves de grafos y sus metodos dentro de la clase  //
//Analytics y el archivo de datos nuevo9.csv                                //
//                                                                          //
//Fecha de creacion 26/11/2020                                              //
//////////////////////////////////////////////////////////////////////////////

int main()
{
    //Load Files
    Analytics my_analitic;
    
    if (my_analitic.load_data_from_csv("nuevo9.csv") > 0)
        cout << "Loaded data." << endl;
    else
    {
        cout << "ERROR loading input file... Exiting program...";
        return 0;
    }


    /////////////////////////////////// Preguntas 1 y 2 ///////////////////////////////
    Graph<string> graph;
    vector<string> dates = my_analitic.get_all_dates();
    string ip = "";
    cout<<"\nWhich IP do you want to get the connections for?"<<endl;
    cin>>ip;
    for(int i = 0; i<dates.size(); i++)
    {
        graph = my_analitic.get_connections_graph(dates[i]);
        cout<<"The amount of connections sent on "<<dates[i]<<" for your IP is: "<<my_analitic.get_connections_per_day(graph,ip)<<endl;
        my_analitic.is_most_connected(graph,ip);
        cout<<"The amount of connections recieved on "<<dates[i]<<" for your IP is: "<<my_analitic.get_connected_per_day(graph,ip)<<endl;
        cout<<endl;
    }

    
    
    /////////////////////////////////// Preguntas 3 y 4 ///////////////////////////////
    Graph<pair<string,string>> graph2;
    string anomaly = "249krwpsl2ciatl5u8nb.ru";
    vector<string> sites = my_analitic.get_all_sites();
    string mostVisitedSite = my_analitic.most_visited_site(sites);
    int webIdx = -1;
    for(int i = 0; i<dates.size();i++)
    {
        graph2 = my_analitic.get_webvisits_graph(dates[i]);
        webIdx = my_analitic.get_site_idx(graph2,anomaly);
        cout<<"The amount of visits to the anomaly on "<<dates[i]<<" is: "<<my_analitic.get_connected_to_site(graph2,webIdx)<<endl;
        webIdx = my_analitic.get_site_idx(graph2,mostVisitedSite);
        cout<<"The amount of visits to the website with large traffic on "<<dates[i]<<" is: "<<my_analitic.get_connected_to_site(graph2,webIdx)<<endl;
        cout<<endl;
    }

}