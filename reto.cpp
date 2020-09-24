#include "ADT.h"
#include "sorter.h"
#include "search.h"
#include <vector>
#include<regex>

using namespace std;

template <typename T>
bool compareIP(T &a, T &b)
{
    if(a == "-" && b != "-"){return true;}
    else if(a != "-" && b == "-"){return false;}
    else if(a == "-" && b == "-"){return false;}

    string f1 = regex_replace(a, regex(R"([\D])"),"");
    string f2 = regex_replace(b, regex(R"([\D])"),"");

    int firstIP = stoi(f1);
    int secondIP = stoi(f2);

    if(firstIP < secondIP){return true;}
    return false;
}

template <typename T>
bool compareHostname(T &a, T &b)
{
    if(a<b)
    {
        return true;
    }
    return false;
}

int main() 
{
    ADT<string> test("equipo9.csv");
    vector<string> hostnames;

    for(size_t i = 0; i < test.data.size(); i++)
    {
        hostnames.push_back(test.data[i][4]);
    }

    InsertionSort<string> hostSort;
    hostSort.sort(hostnames,&compareHostname);

    Search<string> find;
    int elementIdx = find.orderedSeq1(hostnames,"betty.reto.com", &compareHostname); 
    cout<<elementIdx<<endl;
    cout<<hostnames[elementIdx]<<endl;

    return 0;
}