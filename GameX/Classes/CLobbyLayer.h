//
//  CLobbyLayer.h
//  GameX
//
//  Created by 马 俊 on 13-8-28.
//
//

#ifndef __GameX__CLobbyLayer__
#define __GameX__CLobbyLayer__

#include "CBaseLayer.h"
#include "CCBReader.h"

class CLobbyLayer
: public CBaseLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    CREATE_FUNC(CLobbyLayer);
    
    CLobbyLayer();
    virtual ~CLobbyLayer();
    
    virtual bool init();
    
    //CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) ;
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) ;
    
    //CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
protected:
    virtual void onFormation(CCObject *pSender);
    virtual void onBattle(CCObject* pSender);
private:
};


class CLobbyLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CLobbyLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CLobbyLayer);
};


#endif /* defined(__GameX__CLobbyLayer__) */
