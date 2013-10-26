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


bool CWarriorUnit1::init(const string& unitId)
{
    return CWarriorRole::init(unitId);
}



void CWarriorUnit1::think()
{
    CWarriorRole::think();
}



