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
#include "CMonster.h"
#include "TFItemInGame.h"
#include "TFHPBar.h"
#include "CDirectionGun.h"
#include "CScale9SpriteObject.h"
#include "CSpriteObject.h"
#include "CArchersGun.h"
#include "CCircleSensor.h"
#include "CTower.h"
#include "CSoldier.h"
#include "CBallisticBullet.h"
#include "CBallisticGun.h"
#include "CBallisticAOEBullet.h"

#define REGISTER_CLASS(__classname) if (!registerClass(#__classname, FACTOR_SEL(__classname::create))){return false;}
#define FACTOR_SEL(__selector) (FACTORY_CREATE_FUNC)(&__selector)


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
    REGISTER_CLASS(CMonster);
    REGISTER_CLASS(TFItemInGame);
    REGISTER_CLASS(TFHPBar);
    REGISTER_CLASS(CDirectionGun);
    REGISTER_CLASS(CSpriteObject);
    REGISTER_CLASS(CScale9SpriteObject);
    REGISTER_CLASS(CArchersGun);
    REGISTER_CLASS(CCircleSensor);
    REGISTER_CLASS(CTower);
    REGISTER_CLASS(CSoldier);
    REGISTER_CLASS(CBallisticBullet);
    REGISTER_CLASS(CBallisticGun);
    REGISTER_CLASS(CBallisticAOEBullet);
    return true;
}



bool CObjectFactory::registerClass(const string&  className, FACTORY_CREATE_FUNC func)
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



CObjectBase* CObjectFactory::createInstance(const string& className)
{
    MSCF_IT it = FactoryTable_.find(className);
    if (it == FactoryTable_.end())
    {
        return NULL;
    }
    
    return ((*it).second)();
}



