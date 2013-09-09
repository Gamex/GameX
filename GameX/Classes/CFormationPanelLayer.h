//
//  CFormationPanelLayer.h
//  GameX
//
//  Created by 马 俊 on 13-8-29.
//
//

#ifndef __GameX__CFormationPanelLayer__
#define __GameX__CFormationPanelLayer__

#include "CTouchesLayer.h"
#include "CCBReader.h"

#define FRAME_NUM       7           // this is the num that frames were placed in cocosbuilder

class IFormationLayerDelegate
{
public:
    virtual void onFrameSel(int sel) = 0;
    virtual void onSave(class CFormation* fmt) = 0;
};


class CFormationPanelLayer
: public CTouchesLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
    CC_SYNTHESIZE(int, m_curSel, CurSel);
    CC_SYNTHESIZE(IFormationLayerDelegate*, m_delegate, Delegate)
public:
    CREATE_FUNC(CFormationPanelLayer);
    
    CFormationPanelLayer();
    virtual ~CFormationPanelLayer();
    
    virtual bool init();
    
    //CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName) ;
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName) ;
    
    //CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char* pMemberVariableName, CCNode * pNode);
    
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
protected:
    virtual void onBack(CCObject *pSender);
    virtual void onSave(CCObject* pSender);
    virtual void onUp(CCObject *pSender);
    virtual void onDown(CCObject *pSender);
    
    virtual void onFrame(CCObject *pSender);
private:
    CCMenuItem* m_frames[FRAME_NUM];
    int m_firstShownIdx;
};


class CFormationPanelLayerLoader : public cocos2d::extension::CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CFormationPanelLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CFormationPanelLayer);
};

#endif /* defined(__GameX__CFormationPanelLayer__) */
