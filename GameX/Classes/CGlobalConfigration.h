//
//  CGlobalConfigration.h
//  GameX
//
//  Created by 马 俊 on 13-8-20.
//
//

#ifndef __GameX__CGlobalConfigration__
#define __GameX__CGlobalConfigration__

#include "CSingleton.h"
#include <string>


using namespace std;

class CGlobalConfigration : public CSingleton<CGlobalConfigration>
{
public:
    CGlobalConfigration();
    virtual ~CGlobalConfigration();

    void setTextureSuffix(const string& suffix);
    const string& getTextureSuffix();
protected:
private:
    string m_textureSuffix;
};


#define GLOBAL_CONFIG       (CGlobalConfigration::getInstance())

#endif /* defined(__GameX__CGlobalConfigration__) */
