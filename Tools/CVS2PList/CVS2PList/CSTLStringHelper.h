//
//  CSTLStringHelper.h
//  CVS2PList
//
//  Created by 马 俊 on 13-9-10.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __CVS2PList__CSTLStringHelper__
#define __CVS2PList__CSTLStringHelper__

#include <string>
#include <vector>

using namespace std;

namespace STL_STRING_HELPER {
    extern string trim(string &s);
    
    extern string ltrim(string &s);
    
    extern string rtrim(string &s);
    
    //字符串分割函数
    extern std::vector<std::string> split(std::string str,std::string pattern);
    
    
    extern int replace(string& src_str, const string& old_str, const string& new_str);

}

#endif /* defined(__CVS2PList__CSTLStringHelper__) */
