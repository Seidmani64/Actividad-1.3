#include <vector>
#include "analytics.h"
#include "log.h"
#include "analytics.cpp"
#include "log.cpp"

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


    vector<string> names;
    names = my_analitic.get_non_domain_names();
    for(int i = 0; i < names.size(); i++)
        cout<<"Computer name: "<<names[i]<<endl;

    cout<<"Test complete."<<endl;

    return 0;
}