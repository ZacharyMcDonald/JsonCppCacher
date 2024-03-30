// class that stores matrices and json maps. URL is the key and 
// json obj is value. 

#include "jcache.h"

using namespace std;

/*********************************************************************
**                             PUBLIC                               **
*********************************************************************/

jcache::jcache()
{

}

jcache::jcache(string& cache_filename)
{
    this->cache_filename = cache_filename;
}

jcache::jcache(char* cache_filename)
{
    this->cache_filename = cache_filename;
}

jcache::~jcache()
{

}

bool jcache::cache_json(string& url, Json::Value& obj)
{
    this->fast_cache[url] = obj;
    return true;
}

void jcache::retrieve_json(const string& url, Json::Value& ret)
{
    ret = this->fast_cache[url];
}

Json::Value jcache::retrieve_json(const string& url)
{
    return this->fast_cache[url];
}

void jcache::load_cache()
{
    this->from_file();
}

void jcache::save_cache()
{
    this->to_file();
}

void jcache::set_cache_filename(string& filename)
{
    this->cache_filename = filename;
}

/*********************************************************************
**                            PRIVATE                               **
*********************************************************************/

/*
* SAVING CACHE
*/
void jcache::to_file_string(stringstream& ret)
{
    for (auto p : this->fast_cache)
    {
        ret << p.first  << this->file_delim << p.second.asString() 
            << '\n'; 
    }
}

void jcache::to_file()
{
    stringstream s;
    this->to_file_string(s);    

    ofstream out(this->cache_filename);
    out << s.rdbuf();
    out.close();
}
/*
* END SAVING CACHE
*/

/*
* LOADING CACHE
*/
void jcache::from_file_string(stringstream& ret)
{
    fstream in(this->cache_filename);
    ret << in.rdbuf();
    in.close();
}

void jcache::parse_line(string& line, stringstream& keybuf, stringstream& valuebuf)
{
    int delim_rpts = 0;

    stringstream delimbuf;

    size_t i = 0;

    while (delim_rpts < this->file_delim_size)
    {
        delimbuf << line[i];
        i++;

        if (line[i] == this->file_delim[0])
        {
            delim_rpts++;
            continue;
        }
        
        delim_rpts = 0;
        
        keybuf << delimbuf.rdbuf();
        
        delimbuf.clear();
    }

    valuebuf << line.substr(i, line.size() - i);
}

void jcache::add_to_cache(stringstream& keybuf, stringstream& valuebuf)
{
    Json::Value value;
    Json::Reader reader;
    reader.parse(valuebuf, value);
    this->fast_cache[keybuf.str()] = value;
}

void jcache::from_file()
{
    stringstream filebuf, keybuf, valuebuf;
    this->from_file_string(filebuf);

    string line;

    while (getline(filebuf, line))
    {
        parse_line(line, keybuf, valuebuf);
        add_to_cache(keybuf,valuebuf);
    }
}
/*
* END LOADING CACHE
*/

// End of file