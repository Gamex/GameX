//
//  CGamePanelLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-12.
//
//

#include "CGamePanelLayer.h"
#include "CGameSceneManager.h"

CGamePanelLayer::CGamePanelLayer()
{
    
}



CGamePanelLayer::~CGamePanelLayer()
{
    
}



bool CGamePanelLayer::init()
{
    do
    {
        BREAK_IF(!CCLayer::init());
        
//        CCControlButton* btnBuild = CBaseLayer::createImageButton("build");
//        BREAK_IF(!btnBuild);
//        btnBuild->setPosition(ccp(240, 50));
//        btnBuild->addTargetWithActionForControlEvents(this, cccontrol_selector(CGamePanelLayer::onBuild), CCControlEventTouchUpInside);
//        addChild(btnBuild);
//        
//        CCControlButton* btnBuild2 = CBaseLayer::createImageButton("build");
//        BREAK_IF(!btnBuild2);
//        btnBuild2->setPosition(ccp(270, 50));
//        btnBuild2->addTargetWithActionForControlEvents(this, cccontrol_selector(CGamePanelLayer::onBuild2), CCControlEventTouchUpInside);
//        addChild(btnBuild2);
        return true;
    } while (false);
    
    return false;
}



void CGamePanelLayer::popMenu()
{
    
}



void CGamePanelLayer::onBuild(CCObject* sender, CCControlEvent event)
{
    SCENE_MANAGER->go(ST_LOBBY);
//    SOLDIER_MANAGER->buildSoldier(0, "Soldier0");
}




void CGamePanelLayer::onBuild2(CCObject* sender, CCControlEvent event)
{
}
