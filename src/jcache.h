#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <jsoncpp/json/json.h>

class jcache
{
    public:

        jcache();
        jcache(std::string& cache_filename);
        jcache(char* cache_filename);

        ~jcache();

        // takes the url and its corresponding json from user
        // and adds it to the fast_cache map
        bool cache_json(std::string& url, Json::Value& obj);
        
        // given a url a Json value is returned by reference
        void retrieve_json(const std::string& url, Json::Value& ret);
        
        // given a url, a json is returned from the function
        Json::Value retrieve_json(const std::string& url);

        // loads a cache into fast_cache from file
        void load_cache();
        
        // saves fast_cache to a file
        void save_cache();

        // setter for cache filename
        void set_cache_filename(std::string& filename);

    private:

        // the main JSON memory cache
        std::map<std::string, Json::Value> fast_cache;
        
        // filename where the cache is stored when the program is 
        // ended
        std::string cache_filename;

        // custom file deliminator for the cache save file. Must be 
        // the same character repeated
        const char* file_delim = ":::::";
        int   file_delim_size = 5;

        /*
        * SAVING CACHE
        */
        // saves fast_cache to specified file
        void to_file();
        
        // converts fast_cache to stringstream with the specified 
        // deliminator
        void to_file_string(std::stringstream& ret);

        /*
        * LOADING CACHE
        */
        // reads cache file into fast_cache
        void from_file();
        
        // reads file to stringstream
        void from_file_string(std::stringstream& ret);
        
        // takes line from stringstream file buffer and returns by ref
        // the key and value as buffers
        void parse_line(std::string& line, std::stringstream& keybuf, std::stringstream& valuebuf);
        
        // takes keybuffer and valuebuffer. converts value buffer to 
        // Json::Value through Json::reader and addes it to map.
        void add_to_cache(std::stringstream& keybuf, std::stringstream& valuebuf);
};

