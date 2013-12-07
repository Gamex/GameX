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
    enum DATA_TYPE
    {
        DATA_TYPE_INT,
        DATA_TYPE_FLOAT,
        DATA_TYPE_STRING,
    };
    CCsv2PListSourceCode(const char* tp);
    virtual ~CCsv2PListSourceCode();
    
    bool openCVS(const char* cvsName);
    void printDebug();
    bool outputJSONforServer(const char* jsonFilename);
    bool outputJSONforClient(const char* jsonDataFilename, const char* jsonReaderFilename);
    
    void addJSONReaderVar(DATA_TYPE type, const string& var);
    bool outputJSONReaderCPP(const char* cppFilename);
protected:
    void clearAll();
    
    typedef vector<string> VS;
    typedef vector<string>::iterator VS_IT;
    typedef vector<string>::const_iterator VS_CIT;
    
    typedef vector<VS> VVS;
    typedef vector<VS>::iterator VVS_IT;
    typedef vector<VS>::const_iterator VVS_CIT;
    
    vector<DATA_TYPE> m_types;
    VS m_keys;
    VVS m_elems;
    
    string m_jsonReaderBlock1;
    string m_jsonReaderBlock2;
    
    string m_templatePath;
};

#endif /* defined(__CVS2PList__CCsv2PListSourceCode__) */
