#include "analytics.cpp"
#include "graph.h"
#include "analytics.h"
#include "log.cpp"
#include "log.h"

using namespace std;

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

    
    

    Graph<pair<string,string>> graph2;
    string anomaly = "249krwpsl2ciatl5u8nb.ru";
    string webTraffic = "protonmail.com";
    for(int i = 0; i<dates.size();i++)
    {
        graph2 = my_analitic.get_webvisits_graph(dates[i]);
        cout<<"The amount of visits to the anomaly on "<<dates[i]<<" is: "<<my_analitic.get_connected_to_site(graph2,anomaly)<<endl;
        cout<<"The amount of visits to the website with large traffic on "<<dates[i]<<" is: "<<my_analitic.get_connected_to_site(graph2,webTraffic)<<endl;
    }


}