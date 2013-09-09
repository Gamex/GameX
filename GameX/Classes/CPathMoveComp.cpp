//
//  CPathMoveComp.cpp
//  EliminationPlane
//
//  Created by 马 俊 on 13-6-5.
//
//

#include "CPathMoveComp.h"
#include "CPathManager.h"
#include "CPath.h"
#include "Common.h"

CPathMoveComp::CPathMoveComp()
{
    
}



CPathMoveComp::~CPathMoveComp()
{
    
}



void CPathMoveComp::setParameter(CComponentParameter* parameter)
{
    string name;
    if (parameter->getStringParameter(PARAM_PATH_NAME, name))
    {
        path_ = PATH_MANAGER->getPathByName(name);
        elapse_ = 0.f;
        splineIdx_ = 0;
    }
}



void CPathMoveComp::update(float dt)
{
    do
    {
        BREAK_IF(getOwner() == NULL);

        const float INTV = 0.01f;
        elapse_ += dt;
        if (elapse_ >= INTV)
        {
            elapse_ -= INTV;
            if (path_)
            {
                CCArray* spline = path_->getSpline();
                CCPoint* pt = dynamic_cast<CCPoint*>(spline->objectAtIndex(splineIdx_));
                getOwner()->setSpritePosition(*pt);
                splineIdx_++;
                
                if (splineIdx_ >= spline->count())
                {
                    getOwner()->die();
                }
            }
        }
    }while (false);
}


CVisibleObject* CPathMoveComp::getOwner()
{
    return dynamic_cast<CVisibleObject*>(CComponent::getOwner());
}
