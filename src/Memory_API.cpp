// class that stores matrices and json maps. URL is the key and 
// json obj is value. 

#include "Memory_API.h"

using namespace std;


bool jcache::cache_json(string& url, Json::Value& obj)
{
    this->fast_cache[url] = obj;
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
    // TODO: get data file
    // data should be in matrix

}

void jcache::save_cache()
{
    

    // save to file
}

void jcache::to_file_string(stringstream& ret)
{
    for (auto p : this->fast_cache)
    {
        ret << p.first  << this->full_delim << p.second.asString() 
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

void jcache::from_file_string(stringstream& ret)
{
    fstream in(this->cache_filename);
    ret << in.rdbuf();
    in.close();
}

void jcache::parse_line(string& line, stringstream& keybuf, stringstream& valuebuf)
{
    int delim_rpts = 0;

    stringstream delimbuf, keybuf, valuebuf;

    size_t i = 0;

    while (delim_rpts < this->delim_rpts)
    {
        delimbuf << line[i];
        i++;

        if (line[i] == this->simple_delim)
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

void jcache::from_file()
{
    stringstream buf, keybuf, valuebuf;
    this->from_file_string(buf);

    string line;

    while (getline(buf, line))
    {
        parse_line(line, keybuf, valuebuf);

        
    }
}

