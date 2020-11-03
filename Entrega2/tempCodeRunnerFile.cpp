//Load Files
    Analytics my_analitic;
    
    if (my_analitic.load_data_from_csv("../equipo9.csv") > 0)
        cout << "Loaded data." << endl;
    else
    {
        cout << "ERROR loading input file... Exiting program...";
        return 0;
    }