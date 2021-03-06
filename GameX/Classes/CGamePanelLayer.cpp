//
//  CGamePanelLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-6-12.
//
//

#include "CGamePanelLayer.h"
#include "CGameSceneManager.h"
#include "CTimeProfile.h"

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
        BREAK_IF(!Layer::init());
        
        ControlButton* btnBuild = CBaseLayer::createImageButton("huds/build.png");
        BREAK_IF(!btnBuild);
        btnBuild->setPosition(Point(240, 50));
        btnBuild->addTargetWithActionForControlEvents(this, cccontrol_selector(CGamePanelLayer::onBuild), Control::EventType::TOUCH_UP_INSIDE);
        addChild(btnBuild);
        
//        ControlButton* btnBuild2 = CBaseLayer::createImageButton("build");
//        BREAK_IF(!btnBuild2);
//        btnBuild2->setPosition(Point(270, 50));
//        btnBuild2->addTargetWithActionForControlEvents(this, cccontrol_selector(CGamePanelLayer::onBuild2), CCControlEventTouchUpInside);
//        addChild(btnBuild2);
        return true;
    } while (false);
    
    return false;
}



void CGamePanelLayer::popMenu()
{
    
}



void CGamePanelLayer::onBuild(Object* sender, Control::EventType event)
{
    SCENE_MANAGER->go(ST_LOBBY);
    
    TP_LOG_FLUSH();
//    SOLDIER_MANAGER->buildSoldier(0, "Soldier0");
}




void CGamePanelLayer::onBuild2(Object* sender, Control::EventType event)
{
}
