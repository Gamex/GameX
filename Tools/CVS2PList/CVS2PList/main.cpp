//
//  main.cpp
//  CVS2PList
//
//  Created by 马 俊 on 13-7-30.
//  Copyright (c) 2013年 马 俊. All rights reserved.
//

#include "stdio.h"
#include "CCsv2PListSourceCode.h"
#include "CSTLStringHelper.h"

void printUsage()
{
    printf("Usage: -<cpp> -<a|d> <templatePath> <srcfile> <destPath>\n");
}


enum OUTPUT_LANGUAGE
{
    OUTPUT_LANGUAGE_CPP,
};

enum OUTPUT_TYPE
{
    OUTPUT_TYPE_ARRAY,
    OUTPUT_TYPE_DICTIONARY,
};

int main(int argc, const char * argv[])
{
    if (argc != 6)
    {
        printUsage();
        return -1;
    }
    
    OUTPUT_LANGUAGE ol;
    OUTPUT_TYPE ot;
    
    if (strcmp(argv[1], "-cpp") == 0)
    {
        ol = OUTPUT_LANGUAGE_CPP;
    }
    else
    {
        printUsage();
        return -1;
    }
    
    if (strcmp(argv[2], "-a") == 0)
    {
        ot = OUTPUT_TYPE_ARRAY;
    }
    else if (strcmp(argv[2], "-d") == 0)
    {
        ot = OUTPUT_TYPE_DICTIONARY;
    }
    else
    {
        printUsage();
        return -1;
    }
    // insert code here...
    string tp = argv[3];
    if (tp[tp.length()-1] != '/')
    {
        tp += '/';
    }
    string srcfn = argv[4];
    string fn = argv[5];
    if (fn[fn.length()-1] != '/')
    {
        fn += '/';
    }
    fn += "DT";
    string basename = *(STL_STRING_HELPER::split(srcfn, "/").rbegin());
    size_t basename_len = basename.length();
    basename[basename_len - 3] = 'h';
    basename[basename_len - 2] = '\0';
    fn += basename;
    CCsv2PListSourceCode o(tp.c_str());
    if (o.openCVS(argv[4]))
    {
        bool ret = false;
        switch (ot)
        {
            case OUTPUT_TYPE_ARRAY:
                ret = o.outputCCArray2CPP(fn.c_str());
                break;
            case OUTPUT_TYPE_DICTIONARY:
                ret = o.outputCCDictionary2CPP(fn.c_str());
                break;
        }
        
        if (!ret)
        {
            printf("can't open dest file!");
            return -1;
        }
    }
    else
    {
        printf("can't open source!");
        return -1;
    }
    return 0;
}

