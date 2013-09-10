//
//  CCsv2PListSourceCode.cpp
//  CVS2PList
//
//  Created by 马 俊 on 13-7-30.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CCsv2PListSourceCode.h"
#import <Foundation/Foundation.h>
#include <assert.h>
#include "CSTLStringHelper.h"

#define BREAK_IF(__condi__) \
if (__condi__)\
{\
break;\
}


#define SOURCE_FILE_BUF_MAX         (1024*1024*10)      // 10 M




CCsv2PListSourceCode::CCsv2PListSourceCode(const char* tp)
: m_templatePath(tp)
{
    
}



CCsv2PListSourceCode::~CCsv2PListSourceCode()
{
    
}



void CCsv2PListSourceCode::clearAll()
{
    m_keys.clear();
    m_elems.clear();
}



bool CCsv2PListSourceCode::openCVS(const char* cvsName)
{
    bool ret = false;
    FILE* fp = fopen(cvsName, "rb");
    do
    {
        BREAK_IF(!fp);
        clearAll();
        
        fseek(fp, 0, SEEK_END);
        long len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        
        char* s = new char[len+1];
        s[len] = 0;
        fread(s, len, 1, fp);
        
        const string enter = "\r";
        VS lines = STL_STRING_HELPER::split(string(s), enter);
        delete []s;
        s = NULL;
        
        const string delim = ";";
        int lineNo = 0;
        for (; lineNo < lines.size(); ++lineNo)
        {
            switch (lineNo)
            {
                case 0:
                    break;
                case 1:
                {
                    m_keys = STL_STRING_HELPER::split(lines[lineNo], delim);
                    m_keys.erase(m_keys.begin());       // 第一列用于文本描述，所以删除不用
                    break;
                }
                default:
                {
                    VS vs = STL_STRING_HELPER::split(lines[lineNo], delim);
                    vs.erase(vs.begin());               // 第一列用于文本描述，所以删除不用
                    assert(vs.size() == m_keys.size());
                    m_elems.push_back(vs);
                    break;
                }
            }
        }
        
        
        ret = true;
    } while (false);
    
    fclose(fp);
    return ret;
}



void CCsv2PListSourceCode::printDebug()
{
    int i, j;
    for (i = 0; i < m_keys.size(); ++i)
    {
        printf("%s\t\t", m_keys[i].c_str());
    }
    printf("\n");
    
    for (i = 0; i < m_elems.size(); ++i)
    {
        for (j = 0; j < m_elems[i].size(); ++j)
        {
            printf("%s\t\t", m_elems[i][j].c_str());
        }
        printf("\n");
    }
}




bool CCsv2PListSourceCode::outputCCDictionary2CPP(const char* cppFilename)
{
    
    NSString* path = [NSString stringWithFormat:@"%s", m_templatePath.c_str()];
    NSArray* templateFilenames = [NSArray arrayWithObjects:
                                [NSString stringWithFormat:@"%@%@", path, @"templateDictionaryH.txt"],
                                [NSString stringWithFormat:@"%@%@", path, @"templateDictionary__BLOCK_1__.txt"],
                                [NSString stringWithFormat:@"%@%@", path, @"templateDictionary__BLOCK_1_1__.txt"],
                                [NSString stringWithFormat:@"%@%@", path, @"templateDictionary__BLOCK_2__.txt"],
                                nil];
    

    auto_ptr<char> buf(new char[SOURCE_FILE_BUF_MAX]);
    
    string source;
    string block1;
    string block1_1;
    string block2;
    
    string* strings[] = {&source, &block1, &block1_1, &block2};
      
    for (int i = 0; i < (int)[templateFilenames count]; ++i)
    {
        memset(buf.get(), 0, SOURCE_FILE_BUF_MAX);
        NSString* fn = [templateFilenames objectAtIndex:i];
        char cfn[260];
        [fn getCString:cfn maxLength:260 encoding:NSUTF8StringEncoding];
        FILE* fp = fopen(cfn, "rb");
        assert(fp);
        fseek(fp, 0, SEEK_END);
        int len = (int)ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fread(buf.get(), len, 1, fp);
        fclose(fp);
        *(strings[i]) = buf.get();
    }
    
    
    bool ret = false;
    do
    {
        BREAK_IF(cppFilename == NULL);
        vector<string> v1 = STL_STRING_HELPER::split(cppFilename, ".");
        string& str = v1[v1.size() - 2];
        string className = *(STL_STRING_HELPER::split(str, "/").rbegin());
        string outputStr(source);
        string b1, b1_1, b2;
        int i, j;
        
        for (j = 0; j < m_elems.size(); ++j)
        {
            for (i = 1; i < m_keys.size(); ++i)
            {
                if (!m_keys[i].empty())
                {
                    sprintf(buf.get(), block1_1.c_str(), m_elems[j][i].c_str(), m_keys[i].c_str());
                    b1_1 += buf.get();
                }
            }
            sprintf(buf.get(), block1.c_str(), m_elems[j][0].c_str());
            b1 += buf.get();
            STL_STRING_HELPER::replace(b1, "#__BLOCK_1_1__", b1_1);
            
            b1_1.clear();
        }
        
        for (i = 1; i < m_keys.size(); ++i)
        {
            if (!m_keys[i].empty())
            {
                string::const_pointer key = m_keys[i].c_str();
                sprintf(buf.get(), block2.c_str(), key, key, key, key);
                b2 += buf.get();
            }
        }
        
        STL_STRING_HELPER::replace(outputStr, "#__CLASS_NAME__", className);
        STL_STRING_HELPER::replace(outputStr, "#__BLOCK_1__", b1);
        STL_STRING_HELPER::replace(outputStr, "#__BLOCK_2__", b2);
        b2.clear();
        
        FILE* fp = fopen(cppFilename, "wt");
        if (fp)
        {
            fputs(outputStr.c_str(), fp);
        }
        else
        {
            printf("Can't open file: %s", cppFilename);
            break;
        }
        ret = true;
    } while(false);
    
    return ret;
}


bool CCsv2PListSourceCode::outputCCArray2CPP(const char* cppFilename)
{
    
    NSString* path = [NSString stringWithFormat:@"%s", m_templatePath.c_str()];
    NSArray* templateFilenames = [NSArray arrayWithObjects:
                                  [NSString stringWithFormat:@"%@%@", path, @"templateArrayH.txt"],
                                  [NSString stringWithFormat:@"%@%@", path, @"templateArray__BLOCK_1__.txt"],
                                  [NSString stringWithFormat:@"%@%@", path, @"templateArray__BLOCK_1_1__.txt"],
                                  [NSString stringWithFormat:@"%@%@", path, @"templateArray__BLOCK_2__.txt"],
                                  nil];
    
    
    auto_ptr<char> buf(new char[SOURCE_FILE_BUF_MAX]);
    
    string source;
    string block1;
    string block1_1;
    string block2;
    
    string* strings[] = {&source, &block1, &block1_1, &block2};
    
    for (int i = 0; i < (int)[templateFilenames count]; ++i)
    {
        memset(buf.get(), 0, SOURCE_FILE_BUF_MAX);
        NSString* fn = [templateFilenames objectAtIndex:i];
        char cfn[260];
        [fn getCString:cfn maxLength:260 encoding:NSUTF8StringEncoding];
        FILE* fp = fopen(cfn, "rb");
        assert(fp);
        fseek(fp, 0, SEEK_END);
        int len = (int)ftell(fp);
        fseek(fp, 0, SEEK_SET);
        fread(buf.get(), len, 1, fp);
        fclose(fp);
        *(strings[i]) = buf.get();
    }

    bool ret = false;
    do
    {
        BREAK_IF(cppFilename == NULL);
        vector<string> v1 = STL_STRING_HELPER::split(cppFilename, ".");
        string& str = v1[v1.size() - 2];
        string className = *(STL_STRING_HELPER::split(str, "/").rbegin());
        string outputStr(source);
        string b1, b1_1, b2;
        int i, j;
        
        auto_ptr<char> buf(new char[SOURCE_FILE_BUF_MAX]);
        
        for (j = 0; j < m_elems.size(); ++j)
        {
            for (i = 0; i < m_keys.size(); ++i)
            {
                if (!m_keys[i].empty())
                {
                    sprintf(buf.get(), block1_1.c_str(), m_elems[j][i].c_str(), m_keys[i].c_str());
                    b1_1 += buf.get();
                }
            }
            b1 += block1;
            STL_STRING_HELPER::replace(b1, "#__BLOCK_1_1__", b1_1);
            b1_1.clear();
        }
        
        for (i = 1; i < m_keys.size(); ++i)
        {
            if (!m_keys[i].empty())
            {
                string::const_pointer key = m_keys[i].c_str();
                sprintf(buf.get(), block2.c_str(), key, key, key, key);
                b2 += buf.get();
            }
        }
        
        STL_STRING_HELPER::replace(outputStr, "#__CLASS_NAME__", className);
        STL_STRING_HELPER::replace(outputStr, "#__BLOCK_1__", b1);
        STL_STRING_HELPER::replace(outputStr, "#__BLOCK_2__", b2);
        b2.clear();
        
        FILE* fp = fopen(cppFilename, "wt");
        if (fp)
        {
            fputs(outputStr.c_str(), fp);
        }
        else
        {
            printf("Can't open file: %s", cppFilename);
            break;
        }
        ret = true;
    } while(false);
    
    return ret;
}
