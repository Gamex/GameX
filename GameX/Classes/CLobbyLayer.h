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
#include "CCBReader/CCBReader.h"

class CLobbyLayer
: public CBaseLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public NodeLoaderListener
{
public:
    CREATE_FUNC(CLobbyLayer);
    
    CLobbyLayer();
    virtual ~CLobbyLayer();
    
    virtual bool init();
    
    //CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName) ;
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName) ;
    
    //CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char* pMemberVariableName, Node * pNode);
    
    virtual void onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader);
protected:
    virtual void onFormation(Object *pSender);
    virtual void onBattle(Object* pSender);
private:
};


class CLobbyLayerLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CLobbyLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CLobbyLayer);
};


#endif /* defined(__GameX__CLobbyLayer__) */
