#ifndef _ANALYTICS_H
#define _ANALYTICS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stack>
#include <map>
#include <algorithm>
#include <utility>
#include "graph.h"
#include "log.h"
#include "bst.h"
#include "conexiones.h"
#include "../sorter.h"
#include "../search.h"

class Analytics
{
private:
    std::vector<Log> data;

public:
    ~Analytics();
    Analytics();

    int load_data_from_csv(std::string path);
    void print_data();
    int length();
    Log get_registry(int idx);

    std::vector<std::string> get_non_domain_names();
    std::string get_domain_ip(std::string domain);
    std::vector<std::string> get_entry_connections(std::string ip);
    std::map<std::string,int> conexionesPorDia(std::string date);
    std::vector<pair<string, int>> top(int n, std::string fecha);
    std::map<std::string,int> conexionesTotal();
    Graph<std::string> get_connections_graph();
    void is_most_connected(Graph<std::string> graph, std::string ip);
    int get_connections_per_day(Graph<std::string> graph, std::string ip);
    int get_connected_per_day(Graph<std::string> graph, std::string ip);
    Graph<std::pair<std::string,std::string>> get_webvisits_graph();
    int get_connected_to_site(Graph<std::pair<std::string,std::string>> graph, std::string ip);
};


#endif