//
//  CMoveOnGridComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-27.
//
//

#include "CMoveOnGridComp.h"
#include "CRole.h"


CMoveOnGridComp::CMoveOnGridComp()
{
    
}



CMoveOnGridComp::~CMoveOnGridComp()
{
    
}



void CMoveOnGridComp::update(float dt)
{
    
}



void CMoveOnGridComp::setParameter(CComponentParameter* parameter)
{
    
}



CRole* CMoveOnGridComp::getOwner()
{
    return dynamic_cast<CRole*>(CComponent::getOwner());
}


