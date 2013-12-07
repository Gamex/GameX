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
#import "JSONKit.h"

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
                    vector<string> tmp = STL_STRING_HELPER::split(lines[lineNo], delim);
                    for (int i = 0; i < tmp.size(); ++i)
                    {
                        if (tmp[i].compare("int") == 0)
                        {
                            m_types.push_back(DATA_TYPE_INT);
                        }
                        else if (tmp[i].compare("float") == 0)
                        {
                            m_types.push_back(DATA_TYPE_FLOAT);
                        }
                        else
                        {
                            m_types.push_back(DATA_TYPE_STRING);
                        }
                    }
                    
                    m_types.erase(m_types.begin());
                    break;
                }
                case 2:
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
                    
                    bool ok = false;
                    for (int i = 0; i < vs.size(); ++i)
                    {
                        if (vs[i].size() > 0)
                        {
                            ok = true;
                            break;
                        }
                    }
                    if (ok)
                    {
                        m_elems.push_back(vs);
                    }
                    break;
                }
            }
        }
        
        
        ret = true;
    } while (false);
    
    fclose(fp);
    return ret;
}



bool CCsv2PListSourceCode::outputJSONforServer(const char* jsonFilename)
{
    NSMutableDictionary* dict = [NSMutableDictionary dictionary];
    
    for (int i = 0; i < m_elems.size(); ++i)
    {
        NSMutableDictionary* elem = [NSMutableDictionary dictionary];
        for (int j = 1; j < m_keys.size(); ++j)
        {
            string key = m_keys[j];
            string::size_type pos;
            pos = key.find("(b)");
            if (pos == string::npos)
            {
                pos = key.find("(s)");
            }
            
            if (pos != string::npos && pos == key.size() - 3)
            {
                key = key.substr(0, pos);
                
                
                NSString* skey = [NSString stringWithFormat:@"%s", key.c_str()];
                NSString* sobj = [NSString stringWithFormat:@"%s", m_elems[i][j].c_str()];
                id obj;
                switch (m_types[j]) {
                    case DATA_TYPE_INT:
                        obj = [NSNumber numberWithInt:[sobj intValue]];
                        break;
                    case DATA_TYPE_FLOAT:
                        obj = [NSNumber numberWithFloat:[sobj floatValue]];
                        break;
                    default:
                        obj = sobj;
                        [obj retain];
                        break;
                }
                
                [elem setObject:obj forKey:skey];
                [skey release];
                [obj release];
                [sobj release];
            }
        }
        
        if ([elem count] > 0)
        {
            NSString* skey = [NSString stringWithFormat:@"%s", m_elems[i][0].c_str()];
            if ([dict objectForKey:skey] != nil)
            {
                return false;
            }
            [dict setObject:elem forKey:skey];
        }
        
        [elem release];
    }

    NSData* jd = [dict JSONDataWithOptions:JKSerializeOptionValidFlags error:nil];
    [dict release];
    NSString* fn = [NSString stringWithFormat:@"%s.json", jsonFilename];
    [jd writeToFile:fn atomically:NO];
    [fn release];
    [jd release];
    return true;
}



bool CCsv2PListSourceCode::outputJSONforClient(const char* jsonDataFilename, const char* jsonReaderFilename)
{
    NSMutableDictionary* dict = [NSMutableDictionary dictionary];

    for (int i = 0; i < m_elems.size(); ++i)
    {
        NSMutableDictionary* elem = [NSMutableDictionary dictionary];
        for (int j = 1; j < m_keys.size(); ++j)
        {
            string key = m_keys[j];
            string::size_type pos;
            bool ok = false;
            pos = key.find("(b)");
            if (pos != string::npos && pos == key.size() - 3)
            {
                ok = true;
                key = key.substr(0, pos);
            }
            if (!ok)
            {
                pos = key.find("(s)");
                if (pos == string::npos)
                {
                    ok = true;
                }
            }
            
            if (ok)
            {
                if (key.size() > 0 || m_elems[i][j].size() > 0)
                {
                    NSString* skey = [NSString stringWithFormat:@"%s", key.c_str()];
                    NSString* sobj = [NSString stringWithFormat:@"%s", m_elems[i][j].c_str()];
                    id obj;
                    switch (m_types[j]) {
                        case DATA_TYPE_INT:
                            obj = [NSNumber numberWithInt:[sobj intValue]];
                            break;
                       case DATA_TYPE_FLOAT:
                            obj = [NSNumber numberWithFloat:[sobj floatValue]];
                            break;
                        default:
                            obj = sobj;
                            [obj retain];
                            break;
                    }

                    if (i == 0)
                    {
                        addJSONReaderVar(m_types[j], key);
                    }
                    
                    [elem setObject:obj forKey:skey];
                    [skey release];
                    [obj release];
                    [sobj release];
                }
            }
        }
        
        if ([elem count] > 0)
        {
            NSString* skey = [NSString stringWithFormat:@"%s", m_elems[i][0].c_str()];
            if ([dict objectForKey:skey] != nil)
            {
                return false;
            }
            [dict setObject:elem forKey:skey];
        }
        
        [elem release];
    }
    
    NSData* jd = [dict JSONDataWithOptions:JKSerializeOptionValidFlags error:nil];
    [dict release];
    NSString* fn = [NSString stringWithFormat:@"%s.json", jsonDataFilename];
    [jd writeToFile:fn atomically:NO];
    [fn release];
    [jd release];
    
    string sfn = jsonReaderFilename;
    sfn += ".h";
    outputJSONReaderCPP(sfn.c_str());
    return true;
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



void CCsv2PListSourceCode::addJSONReaderVar(DATA_TYPE type, const string& var)
{
    char s[512];
    switch (type) {
        case DATA_TYPE_INT:
            sprintf(s, "\t\tint %s;\n", var.c_str());
            m_jsonReaderBlock1 += s;
            sprintf(s, "\t\t\td->%s = json_integer_value(json_object_get(value, \"%s\"));\n", var.c_str(), var.c_str());
            m_jsonReaderBlock2 += s;
            break;
        case DATA_TYPE_FLOAT:
            sprintf(s, "\t\tfloat %s;\n", var.c_str());
            m_jsonReaderBlock1 += s;
            sprintf(s, "\t\t\t{json_t* o = json_object_get(value, \"%s\"); d->%s = (float)(json_is_real(o) ? json_real_value(o) : json_integer_value(o));}\n", var.c_str(), var.c_str());
            m_jsonReaderBlock2 += s;
            break;
        case DATA_TYPE_STRING:
            sprintf(s, "\t\tstring %s;\n", var.c_str());
            m_jsonReaderBlock1 += s;
            sprintf(s, "\t\t\td->%s = json_string_value(json_object_get(value, \"%s\"));\n", var.c_str(), var.c_str());
            m_jsonReaderBlock2 += s;
            break;
        default:
            break;
    }
}



bool CCsv2PListSourceCode::outputJSONReaderCPP(const char* cppFilename)
{    
    string fn = m_templatePath;
    fn += "templateJsonReader.txt";
    
    auto_ptr<char> buf(new char[SOURCE_FILE_BUF_MAX]);
    
    string source;
    FILE* fp = fopen(fn.c_str(), "rb");
    assert(fp);
    fseek(fp, 0, SEEK_END);
    int len = (int)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    fread(buf.get(), len, 1, fp);
    fclose(fp);
    source = buf.get();
    
    do
    {
        vector<string> v1 = STL_STRING_HELPER::split(cppFilename, ".");
        string& str = v1[v1.size() - 2];
        string className = *(STL_STRING_HELPER::split(str, "/").rbegin());
        
        STL_STRING_HELPER::replace(source, "#__CLASS_NAME__", className);
        STL_STRING_HELPER::replace(source, "#__BLOCK_1__", m_jsonReaderBlock1);
        STL_STRING_HELPER::replace(source, "#__BLOCK_2__", m_jsonReaderBlock2);
        
        FILE* fp = fopen(cppFilename, "wt");
        if (fp)
        {
            fputs(source.c_str(), fp);
        }
        else
        {
            printf("Can't open file: %s", cppFilename);
            break;
        }
        return true;
    } while (false);
    
	return false;
}




