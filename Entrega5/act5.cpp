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
    graph = my_analitic.get_connections_graph();


    cout<<"Test"<<endl;
}