//
//  CObjectFactory.cpp
//  EliminationPlane
//
//  Created by Ray M on 13-4-3.
//
//

#include "CObjectFactory.h"
#include "CObjectBase.h"
#include "CRole.h"
#include "CDirectionBullet.h"
#include "TFItemInGame.h"
#include "TFHPBar.h"
#include "CDirectionGun.h"
#include "CScale9SpriteObject.h"
#include "CSpriteObject.h"
#include "CArchersGun.h"
#include "CCircleSensor.h"
#include "CTower.h"
#include "CBallisticBullet.h"
#include "CBallisticGun.h"
#include "CBallisticAOEBullet.h"
#include "CWarriorRole.h"
#include "CWarriorUnit0.h"
#include "CWarriorUnit1.h"
#include "CWarriorUnit2.h"
#include "CSkillComp.h"

#define REGISTER_CLASS(__classname) if (!registerClass(#__classname, FACTORY_SEL(__classname::create))){return false;}
#define FACTORY_SEL(__selector) (FACTORY_CREATE_FUNC)(&__selector)


IMPLEMENT_SINGLETON(CObjectFactory)

CObjectFactory::CObjectFactory()
{

}



CObjectFactory::~CObjectFactory()
{
    
}


bool CObjectFactory::Initialize()
{
    REGISTER_CLASS(CRole);
    REGISTER_CLASS(CDirectionBullet);
    REGISTER_CLASS(TFItemInGame);
    REGISTER_CLASS(TFHPBar);
    REGISTER_CLASS(CDirectionGun);
    REGISTER_CLASS(CSpriteObject);
    REGISTER_CLASS(CScale9SpriteObject);
    REGISTER_CLASS(CArchersGun);
    REGISTER_CLASS(CCircleSensor);
    REGISTER_CLASS(CTower);
    REGISTER_CLASS(CBallisticBullet);
    REGISTER_CLASS(CBallisticGun);
    REGISTER_CLASS(CBallisticAOEBullet);
    REGISTER_CLASS(CWarriorRole);
    REGISTER_CLASS(CWarriorUnit0);
    REGISTER_CLASS(CWarriorUnit1);
    REGISTER_CLASS(CWarriorUnit2);
    REGISTER_CLASS(CSkillComp);
    return true;
}



bool CObjectFactory::registerClass(const std::string&  className, FACTORY_CREATE_FUNC func)
{
    if (!func)
    {
        return false;
    }
    
    MSCF_CIT it = FactoryTable_.find(className);
    if (it != FactoryTable_.end())
    {
        return false;
    }
    FactoryTable_[className] = func;
    return true;
}



CCObject* CObjectFactory::createInstance(const std::string& className)
{
    MSCF_IT it = FactoryTable_.find(className);
    if (it == FactoryTable_.end())
    {
        return NULL;
    }
    
    return ((*it).second)();
}



