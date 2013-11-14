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
#include "CSingleton.h"
#include "CBackgroundManager.h"
#include "CGamePanelLayer.h"
#include "CBkgLayerBase.h"

USING_NS_CC;
using namespace std;


class CBattleFieldLayer
: public CTouchesLayer
, public CBkgLayerBase
{
    CC_SYNTHESIZE_RETAIN(CGamePanelLayer*, m_pGamePanelLayer, GamePanelLayer);
public:
    CREATE_FUNC(CBattleFieldLayer);
    CBattleFieldLayer();
    virtual ~CBattleFieldLayer();
    
    virtual bool init();
    void update(float dt);

    virtual void touchesBegan(const std::vector<Touch*>& touches, Event* event);
    virtual void touchesMoved(const std::vector<Touch*>& touches, Event* event);
    virtual void touchesEnded(const std::vector<Touch*>& touches, Event* event);
protected:

    void initListener();
    void removeAllListener();
    void onGameOver(Object* obj);

    bool loadConfig();
    bool loadFormation();

private:
    bool m_bMapMoved;
    CRole* m_curSelRole;
};

//#define BATTLE_FIELD_LAYER (CBattleFieldLayer::getInstance())
//#define ITEM_IN_GAME_MANAGER (CBattleFieldLayer::getInstance()->getItemInGameMgr())

#endif // /* defined(__TheForce__TFBattleFieldLayer__) */
