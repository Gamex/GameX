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
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CLobbyLayer", CLobbyLayerLoader::loader());
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


SEL_MenuHandler CLobbyLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFormation", CLobbyLayer::onFormation);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattle", CLobbyLayer::onBattle);
    return nullptr;
}

//函数定义类型为：void pressTitle(Object *pSender);
Control::Handler CLobbyLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CLobbyLayer::controlButtonTest);
    return nullptr;
}

bool CLobbyLayer::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "helloLabel", CCLabelTTF*, helloLabel);
    return false;
}


void CLobbyLayer::onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader)
{
    
}



void CLobbyLayer::onFormation(Object *pSender)
{
    SCENE_MANAGER->go(ST_FORMATION);
}



void CLobbyLayer::onBattle(Object* pSender)
{
    SCENE_MANAGER->go(ST_BATTLE_FIELD);
}





