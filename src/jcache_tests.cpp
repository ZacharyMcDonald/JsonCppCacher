#include <gtest/gtest.h>

#include "jcache.h"

using namespace std;

TEST (cache_retrieve, retrieve_by_reference)
{
    string url("www.database.com/iamdatabase/");

    Json::Value obj;

    jcache test_cache;

    test_cache.cache_json(url, obj);

    string out_url(url);
    Json::Value out_obj;
    
    test_cache.retrieve_json(url, out_obj);

    ASSERT_EQ(out_obj, obj);
    ASSERT_EQ(out_url, url);
}

TEST (cache_retrieve, retrieve_by_return)
{
    string url("www.database.com/iamdatabase/");

    Json::Value obj;

    jcache test_cache;

    test_cache.cache_json(url, obj);

    string out_url(url);
    Json::Value out_obj = test_cache.retrieve_json(url);

    ASSERT_EQ(out_obj, obj);
    ASSERT_EQ(out_url, url);
}

TEST (load_from_file, small_cache_url)
{
    string url("www.smallcache.org/testurl/");

    Json::Value obj;

    jcache test_cache("test_caches/small_cache.jcache");

    cout << "loading cache from file" << endl;
    test_cache.load_cache();
}