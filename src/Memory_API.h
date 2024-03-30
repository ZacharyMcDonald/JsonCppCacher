#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>


typedef std::vector<std::vector<std::string>> matrix;


class jcache
{
    public:
        bool cache_json(std::string& url, Json::Value& obj);


        void retrieve_json(const std::string& url, Json::Value& ret);
        Json::Value retrieve_json(const std::string& url);

        void load_cache();
        void save_cache();


    private:

        std::map<std::string, Json::Value> fast_cache;
        string cache_filename;

        void to_file();
        void from_file();
        void to_file_string(std::stringstream& ret);
        void from_file_string(std::stringstream& ret);
        void parse_line(std::string& line, std::stringstream& keybuf, std::stringstream& valuebuf);
        char* full_delim = ":::::";
        char  simple_delim = ':';
        int delim_rpts = 5;

};

