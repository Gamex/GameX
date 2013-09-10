//
//  CCsv2PListSourceCode.h
//  CVS2PList
//
//  Created by 马 俊 on 13-7-30.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#ifndef __CVS2PList__CCsv2PListSourceCode__
#define __CVS2PList__CCsv2PListSourceCode__

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;

class CCsv2PListSourceCode
{
public:
    CCsv2PListSourceCode();
    virtual ~CCsv2PListSourceCode();
    
    bool openCVS(const char* cvsName);
    void printDebug();
    bool outputCCDictionary2CPP(const char* cppFilename);
    bool outputCCArray2CPP(const char* cppFilename);
protected:
    void clearAll();
    
    typedef vector<string> VS;
    typedef vector<string>::iterator VS_IT;
    typedef vector<string>::const_iterator VS_CIT;
    
    typedef vector<VS> VVS;
    typedef vector<VS>::iterator VVS_IT;
    typedef vector<VS>::const_iterator VVS_CIT;
    
    VS m_keys;
    VVS m_elems;
};

#endif /* defined(__CVS2PList__CCsv2PListSourceCode__) */
