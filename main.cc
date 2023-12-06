#include <json/json.h>
#include <json/value.h>

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <filesystem>

std::map<int, double> key_area_hours;

void total_hours()
{
    std::map<int, double>::iterator it;

    for(it = key_area_hours.begin(); it != key_area_hours.end(); it++)
    {
        std::cout <<"Key Area " << it->first << " : " << it->second << " hours\n";
    }
}

void sum_key_areas(int key_area, double hours)
{
   double existing_hours = key_area_hours[key_area];
   hours += existing_hours;
   key_area_hours[key_area] = hours;
}


void read_daily(std::string path)
{
    std::string filename = path;

    Json::Value root;
    Json::Reader jsonReader;

    std::ifstream in(filename);

    if(!in)
    {
        std::string error("Cannot open the file\n");
        error += filename;
        throw std::runtime_error(error);;
    }


    bool parsed = jsonReader.parse(in, root);
    if(!parsed)
    {
        std::string error("Error parsing the string\n");
        throw std::runtime_error(error);
    }

    Json::Value::Members keys = root.getMemberNames();
    
    int ka = root["Key Area"].asInt();
    double time = root["Time (hours)"].asDouble();

    sum_key_areas(ka, time);

    /*
    for(auto key: keys)
    {
        std::cout << key << ": ";
        std::cout << root[key];
        std::cout << '\n';
    }
    */  
}

void scan_files()
{
    std::string path = "./LOG/";
    
    for(const auto& dir: std::filesystem::recursive_directory_iterator(path))
    {
        if(std::filesystem::is_regular_file(dir.path()))
        {
            //std::cout << dir.path() << "\n";
            try
            {
                read_daily(dir.path());
            }
            catch(std::exception err)
            {
                std::cerr << err.what() << '\n'; 
            }
        }
    }
}




int main(int argc, char** argv)
{
    if(argc < 2)
        scan_files();
    else
        read_daily(argv[1]);


    total_hours();

    return 0;
}
