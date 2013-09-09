//
//  CLobbyLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-28.
//
//

#include "CLobbyLayer.h"
#include "CGameSceneManager.h"

static class CLobbyLayerRegister
{
public:
    CLobbyLayerRegister()
    {
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "CLobbyLayer", CLobbyLayerLoader::loader());
    }
} __reg;




CLobbyLayer::CLobbyLayer()
{

}



CLobbyLayer::~CLobbyLayer()
{
    
}



bool CLobbyLayer::init()
{
    do
    {
        return true;
    } while (false);
    
    return false;
}


SEL_MenuHandler CLobbyLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFormation", CLobbyLayer::onFormation);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattle", CLobbyLayer::onBattle);
    return NULL;
}

//函数定义类型为：void pressTitle(CCObject *pSender);
SEL_CCControlHandler CLobbyLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CLobbyLayer::controlButtonTest);
    return NULL;
}

bool CLobbyLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "helloLabel", CCLabelTTF*, helloLabel);
    return false;
}


void CLobbyLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    
}



void CLobbyLayer::onFormation(CCObject *pSender)
{
    SCENE_MANAGER->go(ST_FORMATION);
}



void CLobbyLayer::onBattle(CCObject* pSender)
{
    SCENE_MANAGER->go(ST_BATTLE_FIELD);
}





