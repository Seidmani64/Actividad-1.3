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
    Graph<std::string> get_connections_graph(std::string date);
    std::vector<std::string> get_all_dates();
    void is_most_connected(Graph<std::string> graph, std::string ip);
    int get_connections_per_day(Graph<std::string> graph, std::string ip);
    int get_connected_per_day(Graph<std::string> graph, std::string ip);
    Graph<std::pair<std::string,std::string>> get_webvisits_graph(std::string date);
    int get_site_idx(Graph<std::pair<std::string,std::string>> graph, std::string webName);
    int get_connected_to_site(Graph<std::pair<std::string,std::string>> graph, int idx);

    int get_visits_per_site(std::string site);
    std::vector<std::string> get_all_sites();
    std::string most_visited_site(std::vector<std::string> sites);
};


#endif