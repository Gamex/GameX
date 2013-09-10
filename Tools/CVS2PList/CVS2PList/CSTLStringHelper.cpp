//
//  CSTLStringHelper.cpp
//  CVS2PList
//
//  Created by 马 俊 on 13-9-10.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CSTLStringHelper.h"

namespace STL_STRING_HELPER
{
    

string trim(string &s)
{
    const string &space =" \f\n\t\r\v" ;
    string r=s.erase(s.find_last_not_of(space)+1);
    return r.erase(0,r.find_first_not_of(space));
}

string ltrim(string &s)
{
    const string &space =" \f\n\t\r\v" ;
    return s.erase(0,s.find_first_not_of(space));
}

string rtrim(string &s)
{
    const string &space =" \f\n\t\r\v" ;
    return s.erase(s.find_last_not_of(space)+1);
}



//字符串分割函数
std::vector<std::string> split(std::string str,std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    size_t size=str.size();
    
    for(size_t i = 0; i < size; i++)
    {
        pos=str.find(pattern, i);
        if(pos < size)
        {
            std::string s = str.substr(i, pos-i);
            result.push_back(s);
            i = pos+pattern.size() - 1;
        }
    }
    return result;
}


int replace(string& src_str, const string& old_str, const string& new_str)
{
    int count = 0;
    string::size_type old_str_len = old_str.length();
    string::size_type new_str_len = new_str.length();
    string::size_type pos = 0;
    while( (pos = src_str.find( old_str, pos ) ) != string::npos )
    {
        src_str.replace( pos, old_str_len, new_str );
        pos += new_str_len;
        ++count;
    }
    return count;
}
    
}
