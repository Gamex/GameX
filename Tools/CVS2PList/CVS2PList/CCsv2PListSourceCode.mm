//
//  CCsv2PListSourceCode.cpp
//  CVS2PList
//
//  Created by 马 俊 on 13-7-30.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "CCsv2PListSourceCode.h"
#include <assert.h>
#import "GBSettingFilePath.h"


#define BREAK_IF(__condi__) \
if (__condi__)\
{\
break;\
}


#define SOURCE_FILE_BUF_MAX         (1024*1024*10)      // 10 M


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


CCsv2PListSourceCode::CCsv2PListSourceCode()
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
        VS lines = ::split(string(s), enter);
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
                    m_keys = ::split(lines[lineNo], delim);
                    m_keys.erase(m_keys.begin());       // 第一列用于文本描述，所以删除不用
                    break;
                }
                default:
                {
                    VS vs = ::split(lines[lineNo], delim);
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
//    const char* source = "\
//namespace %s\n\
//{\n\
//void loadData2CCDictionary(CCDictionary** dictionary)\n\
//{\n\
//\tif (NULL == dictionary)\n\
//\t{\n\
//\t\treturn;\n\
//\t}\n\
//\t*dictionary = CCDictionary::create();\n\
//\n\
//\n\
//%s\
//}\n\
//CCDictionary* getData(CCDictionary* dict, const string& key)\n\
//{\n\
//\tCC_ASSERT(dict);\n\
//\treturn dynamic_cast<CCDictionary*>(dict->objectForKey(key));\n\
//}\n\
//CCString* getValueOf(CCDictionary* dict, const string& key, const string& subKey)\n\
//{\n\
//\tCC_ASSERT(dict);\n\
//\tCCDictionary* sub = getData(dict, key);\n\
//\tif (sub)\n\
//\t{\n\
//\t\treturn dynamic_cast<CCString*>(sub->objectForKey(subKey));\n\
//\t}\n\
//\treturn NULL;\n\
//}\n\
//CCString* getValueOf(CCDictionary* subDict, const string& subKey)\n\
//{\n\
//\tCC_ASSERT(subDict);\n\
//\treturn dynamic_cast<CCString*>(subDict->objectForKey(subKey));\n\
//}\n\
//%s\n\
//}";
//
//    const char* repeatBlock1 = "\
//\t{\n\
//\t\tCCDictionary* elem = CCDictionary::create();\n\
//\n\
//%s\
//\n\
//\t\t(*dictionary)->setObject(elem, \"%s\");\n\
//\t}\n\
//";
//    
//    const char* repeatBlock2 = "\
//\t\telem->setObject(CCString::create(\"%s\"), \"%s\");\n\
//";
//    
//    const char* functionsBlock = "\
//CCString* get_%s_Value(CCDictionary* dict, const string& key)\n\
//{\n\
//\treturn getValueOf(dict, key, \"%s\");\n\
//}\n\
//CCString* get_%s_Value(CCDictionary* subDict)\n\
//{\n\
//\treturn getValueOf(subDict, \"%s\");\n\
//}\n\
//";
    
    NSString* path = [GBSettingFilePath sharedFilePath].path;
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
        string className = *(split(*(split(cppFilename, ".").begin()), "/").rbegin());
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
            ::replace(b1, "#__BLOCK_1_1__", b1_1);
            
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
        
        ::replace(outputStr, "#__CLASS_NAME__", className);
        ::replace(outputStr, "#__BLOCK_1__", b1);
        ::replace(outputStr, "#__BLOCK_2__", b2);
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
//    const char* source = "\
//namespace %s\n\
//{\n\
//void loadData2CCArray(CCArray** array)\n\
//{\n\
//\tif (NULL == array)\n\
//\t{\n\
//\t\treturn;\n\
//\t}\n\
//\t*array = CCArray::create();\n\
//\n\
//\n\
//%s\
//}\n\
//CCDictionary* getData(CCArray* array, int key)\n\
//{\n\
//\tCC_ASSERT(array);\n\
//\tif(key < 0 || key >= array->count()) return NULL;\n\
//\treturn dynamic_cast<CCDictionary*>(array->objectAtIndex(key));\n\
//}\n\
//CCString* getValueOf(CCArray* array, int key, const string& subKey)\n\
//{\n\
//\tCC_ASSERT(array);\n\
//\tCCDictionary* sub = getData(array, key);\n\
//\tif (sub)\n\
//\t{\n\
//\t\treturn dynamic_cast<CCString*>(sub->objectForKey(subKey));\n\
//\t}\n\
//\treturn NULL;\n\
//}\n\
//CCString* getValueOf(CCDictionary* subDict, const string& subKey)\n\
//{\n\
//\tCC_ASSERT(subDict);\n\
//\treturn dynamic_cast<CCString*>(subDict->objectForKey(subKey));\n\
//}\n\
//%s\n\
//}";
//    
//    const char* repeatBlock1 = "\
//\t{\n\
//\t\tCCDictionary* elem = CCDictionary::create();\n\
//\n\
//%s\
//\n\
//\t\t(*array)->addObject(elem);\n\
//\t}\n\
//";
//    
//    const char* repeatBlock2 = "\
//\t\telem->setObject(CCString::create(\"%s\"), \"%s\");\n\
//";
//    
//    const char* functionsBlock = "\
//CCString* get_%s_Value(CCArray* array, int key)\n\
//{\n\
//\treturn getValueOf(array, key, \"%s\");\n\
//}\n\
//CCString* get_%s_Value(CCDictionary* subDict)\n\
//{\n\
//\treturn getValueOf(subDict, \"%s\");\n\
//}\n\
//";
    
    NSString* path = [GBSettingFilePath sharedFilePath].path;
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
        
        string className = *(split(*(split(cppFilename, ".").begin()), "/").rbegin());
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
            ::replace(b1, "#__BLOCK_1_1__", b1_1);
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
        
        ::replace(outputStr, "#__CLASS_NAME__", className);
        ::replace(outputStr, "#__BLOCK_1__", b1);
        ::replace(outputStr, "#__BLOCK_2__", b2);
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
