//
//  CHomeLayer.h
//  GameX
//
//  Created by 马 俊 on 13-12-8.
//
//

#ifndef __GameX__CHomeLayer__
#define __GameX__CHomeLayer__

#include "CTouchesLayer.h"
#include "CSingleton.h"
#include "CBackgroundManager.h"
#include "CBkgLayerBase.h"

USING_NS_CC;
using namespace std;


class CHomeLayer
: public CTouchesLayer
, public CBkgLayerBase
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public NodeLoaderListener
{
public:
    CREATE_FUNC(CHomeLayer);
    CHomeLayer();
    virtual ~CHomeLayer();
    
    virtual bool init() override;
    void update(float dt);
    
    virtual void touchesBegan(const std::vector<Touch*>& touches, Event* event) override;
    virtual void touchesMoved(const std::vector<Touch*>& touches, Event* event) override;
    virtual void touchesEnded(const std::vector<Touch*>& touches, Event* event) override;
    
    //CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName) override;
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName) override;
    
    //CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char* pMemberVariableName, Node * pNode) override;
    
    virtual void onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader) override;
protected:
    virtual void onMenu(Object* sender, Control::EventType event);
    virtual void onBack(Object* sender, Control::EventType event);
    
    void refreshMainMenu();
    void toggleMainMenu();
    
    void onShopItemClicked(Object* obj, Control::EventType type);
    void onBuildCommitClicked(Object* obj, Control::EventType type);
    
    void reqHomeInfo();
private:
    class CRole* m_curSelRole = nullptr;
    Point m_curSelGrid;
    
    CCNode* m_mainMenuRoot = nullptr;

    class CRole* m_buildingRole = nullptr;
};


class CHomeLayerLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CHomeLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CHomeLayer);
};

#endif /* defined(__GameX__CHomeLayer__) */
