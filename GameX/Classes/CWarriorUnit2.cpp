//
//  CWarriorUnit2.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-9.
//
//

#include "CWarriorUnit2.h"

CWarriorUnit2::CWarriorUnit2()
{
}



CWarriorUnit2::~CWarriorUnit2()
{
}



void CWarriorUnit2::think()
{
    CWarriorRole::think();
}



bool CWarriorUnit2::playAnimation(const std::string& name)
{
    CWarriorRole::playAnimation(name);
}