//
//  CBattleFieldLayer.h
//  TheForce
//
//  Created by Ming Zhao on 2/1/13.
//  Copyright Tencent 2013. All rights reserved.
//
#ifndef __TheForce__TFBattleFieldLayer__
#define __TheForce__TFBattleFieldLayer__

#include "CTouchesLayer.h"
#include "CArchersGun.h"
#include "CSingleton.h"
#include "CBackgroundManager.h"
#include "CGamePanelLayer.h"

USING_NS_CC;
using namespace std;


class CBattleFieldLayer : public CTouchesLayer
{
    CC_SYNTHESIZE_RETAIN(CGamePanelLayer*, m_pGamePanelLayer, GamePanelLayer);
public:
    CREATE_FUNC(CBattleFieldLayer);
    CBattleFieldLayer();
    virtual ~CBattleFieldLayer();
    
    virtual bool init();
    void update(float dt);

    virtual void gbTouchesBegan(CCPoint position);
    virtual void gbTouchesMoved(CCPoint position);
    virtual void gbTouchesEnded(CCPoint position);
//	virtual void gbTapGesture(CCPoint position);

protected:

    void initListener();
    void removeAllListener();
    void onGameOver(CCObject* obj);

    bool loadConfig();
    bool loadFormation();
private:
    float wipeY_;
    bool m_isGameOver;
};

//#define BATTLE_FIELD_LAYER (CBattleFieldLayer::getInstance())
//#define ITEM_IN_GAME_MANAGER (CBattleFieldLayer::getInstance()->getItemInGameMgr())

#endif // /* defined(__TheForce__TFBattleFieldLayer__) */
