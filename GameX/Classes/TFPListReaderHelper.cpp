//
//  TFPListReaderHelper.cpp
//  TheForce
//
//  Created by Ray M on 13-3-7.
//  Copyright (c) 2013年 Tencent. All rights reserved.
//

#include "TFPListReaderHelper.h"


// string toolkit
void TFPListReaderHelper::split(std::string src, const char* token, CCArray& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
        {
            CCString* s = CCString::create(src.substr(nbegin, src.length()-nbegin));
            vect.addObject(s);
        }
        else
        {
            CCString* s = CCString::create(src.substr(nbegin, nend-nbegin));
            vect.addObject(s);
        }
        nbegin = nend + strlen(token);
    }
}

// first, judge whether the form of the string like this: {x,y}
// if the form is right,the string will be split into the parameter strs;
// or the parameter strs will be empty.
// if the form is right return true,else return false.
bool TFPListReaderHelper::splitWithForm(const char* pStr, CCArray& strs)
{
    bool bRet = false;
    
    do
    {
        BREAK_IF(!pStr);
        
        // string is empty
        std::string content = pStr;
        BREAK_IF(content.length() == 0);
        
        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');
        
        // don't have '{' and '}'
        BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
        // '}' is before '{'
        BREAK_IF(nPosLeft > nPosRight);
        
        std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        // nothing between '{' and '}'
        BREAK_IF(pointStr.length() == 0);
        
        int nPos1 = pointStr.find('{');
        int nPos2 = pointStr.find('}');
        // contain '{' or '}'
        BREAK_IF(nPos1 != (int)std::string::npos || nPos2 != (int)std::string::npos);
        
        split(pointStr, ",", strs);
        
        bRet = true;
    } while (0);
    
    return bRet;
}
