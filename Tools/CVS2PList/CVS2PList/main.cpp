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
    printf("Usage: <templatePath> <srcfile> <clientPath> <serverPath>\n");
}



int main(int argc, const char * argv[])
{
    if (argc != 5)
    {
        printUsage();
        return -1;
    }


    string tp = argv[1];
    if (tp[tp.length()-1] != '/')
    {
        tp += '/';
    }
    string srcfn = argv[2];
    string clientPath = argv[3];
    string clientData, clientReader;
    string serverPath = argv[4];
    if (clientPath[clientPath.length()-1] != '/')
    {
        clientPath += '/';
    }
    clientData = clientPath;
    clientData += "Resources/DT";
    clientReader = clientPath;
    clientReader += "Classes/DT";
    if (serverPath[serverPath.length()-1] != '/')
    {
        serverPath += '/';
    }
    serverPath += "DT";
    string basename = *(STL_STRING_HELPER::split(srcfn, "/").rbegin());
    size_t basename_len = basename.length();
    basename.replace(basename_len - 4, 4, "");
    serverPath += basename;
    clientData += basename;
    clientReader += basename;
    CCsv2PListSourceCode o(tp.c_str());
    if (o.openCVS(argv[2]))
    {
        bool ret = false;

        ret = o.outputJSONforServer(serverPath.c_str());
        ret = o.outputJSONforClient(clientData.c_str(), clientReader.c_str());
        
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

