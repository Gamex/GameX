//
//  CBuildingRole.cpp
//  GameX
//
//  Created by 马 俊 on 13-12-11.
//
//

#include "CBuildingRole.h"
#include "CDataCenterManager.h"

CBuildingRole::~CBuildingRole()
{
}



bool CBuildingRole::init(const string& unitId, bool editorMode)
{
    do
    {
        BREAK_IF(!CRole::init(unitId, editorMode));
        
//        const DTUnit::_Data* unitData = DTUNIT->getData(unitId);
//        CC_ASSERT(unitData);

        return true;
    } while (false);
    
    return false;
}



void CBuildingRole::addComponentsForStates()
{
    // override the base function
}



void CBuildingRole::update(float dt)
{
}



SEL_CallFuncN CBuildingRole::onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName)
{
    return nullptr;
}



bool CBuildingRole::playAnimation(const std::string& name)
{    
    return CSpriteObject::playAnimation(name);
}

