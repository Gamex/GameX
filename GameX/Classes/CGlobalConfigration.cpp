//
//  CGlobalConfigration.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-20.
//
//

#include "CGlobalConfigration.h"

IMPLEMENT_SINGLETON(CGlobalConfigration);

CGlobalConfigration::CGlobalConfigration()
{
    
}



CGlobalConfigration::~CGlobalConfigration()
{
    
}



void CGlobalConfigration::setTextureSuffix(const string& suffix)
{
    m_textureSuffix = suffix;
}



const string& CGlobalConfigration::getTextureSuffix()
{
    return m_textureSuffix;
}