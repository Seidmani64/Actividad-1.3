#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream> 
#include <list>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

template <class T>
class GraphVertex
{
private:
    T val;
    std::vector<int> adj;
public: 
    ~GraphVertex() {};
    GraphVertex() {};
    GraphVertex(T _val) {val = _val;};

    T get_val() {return val;};
    void set_val(T _val) {val = _val;};

    std::vector<int> get_adj() {return adj;};
    void add_to_adj(int idx) {adj.push_back(idx);};
};

// A B C D E F G H
// 0 1 2 3 4 5 6 7
// Lista adj a: 1, 2, 3
// Lista adj b: 0
// Lista adj c: 0, 3


template <class T>
class Graph
{
private:
    std::vector<GraphVertex<T> > nodes;
    bool is_directed;

public:
    ~Graph() {};
    Graph() {is_directed=false;};
    Graph(bool directed) {is_directed = directed;};

    int add_node(T val)
    {
        GraphVertex<T> node(val);
        bool cond = true;
        for(int j = 0; j<nodes.size(); j++)
            if(nodes[j].get_val() == val)
                cond = false;
        if(cond)
        {
            nodes.push_back(node);
            std::cout<<"The value of the node is: "<<val<<std::endl;
            return nodes.size()-1;
        }
        else
            for(int i = 0; i < nodes.size(); i++)
                if(node.get_val()==nodes[i].get_val())
                    return i;
        return -1;
        
    };

    void add_edge(int src, int dst)
    {
        nodes[src].add_to_adj(dst);
        if (!is_directed)
            nodes[dst].add_to_adj(src);
    };

    void BFS(int start_vertex)
    {
        std::vector<int> visited;
        std::queue<int> searching;
        std::vector<int> temp;
        bool condition = true;
        do
        {
            if(condition)
            {
                std::cout<<nodes[start_vertex].get_val()<<" ";
                temp = nodes[start_vertex].get_adj();
                for(int i = 0; i < temp.size(); i++)
                {
                    searching.push(temp[i]);
                }
                visited.push_back(start_vertex);
                start_vertex = searching.front();
                searching.pop();
                for(int i = 0; i < visited.size(); i++)
                {
                    if(visited[i]==start_vertex)
                    {
                        condition = false;
                        i = visited.size();
                    }
                    else condition = true;
                }
            }
            else
            {
                start_vertex = searching.front();
                searching.pop();
                for(int i = 0; i < visited.size(); i++)
                {
                    if(visited[i]==start_vertex)
                    {
                        condition = false;
                        i = visited.size();
                    }
                    else condition = true;
                }
            }
            

        } while (searching.empty() != true);
        
    };

    void DFS(int start_vertex)
    {
        std::vector<int> visited;
        std::stack<int> searching;
        std::vector<int> temp;
        bool condition = true;
        do
        {
            if(condition)
            {
                std::cout<<nodes[start_vertex].get_val()<<" ";
                temp = nodes[start_vertex].get_adj();
                for(int i = 0; i < temp.size(); i++)
                {
                    searching.push(temp[i]);
                }
                visited.push_back(start_vertex);
                start_vertex = searching.top();
                searching.pop();
                for(int i = 0; i < visited.size(); i++)
                {
                    if(visited[i]==start_vertex)
                    {
                        condition = false;
                        i = visited.size();
                    }
                    else condition = true;
                }
            }
            else
            {
                start_vertex = searching.top();
                searching.pop();
                for(int i = 0; i < visited.size(); i++)
                {
                    if(visited[i]==start_vertex)
                    {
                        condition = false;
                        i = visited.size();
                    }
                    else
                    {
                        condition = true;
                        searching.push(0);
                    }
                }
            }
            

        } while (searching.empty() != true);

        
    }
};

#endif