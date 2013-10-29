//
//  CWarriorUnit1.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-9.
//
//

#include "CWarriorUnit1.h"

CWarriorUnit1::CWarriorUnit1()
{
}



CWarriorUnit1::~CWarriorUnit1()
{
}


bool CWarriorUnit1::init(const string& unitId, bool editorMode)
{
    return CWarriorRole::init(unitId, editorMode);
}



void CWarriorUnit1::think()
{
    CWarriorRole::think();
}



