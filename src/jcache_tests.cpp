#include <gtest/gtest.h>

#include "jcache.h"

using namespace std;

TEST (cache_retrieve, retrieve_by_reference)
{
    string url("www.database.com/iamdatabase/");

    Json::Value obj;

    jcache test_cache;

    test_cache.cache_json(url, obj);

    string out_url;
    Json::Value out_obj;
    
    test_cache.retrieve_json(out_url, out_obj);

    ASSERT_EQ(out_url, url);
    ASSERT_EQ(out_obj, obj);
}

