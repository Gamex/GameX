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
#include "CCBReader/CCBReader.h"

#define FRAME_NUM       7           // this is the num that frames were placed in cocosbuilder

class IFormationLayerDelegate
{
public:
    virtual void onFrameSel(const std::string& unitId) = 0;
    virtual void onSave(class CFormation* fmt) = 0;
    virtual void onLoad(class CFormation* fmt) = 0;
};


class CFormationPanelLayer
: public CTouchesLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public NodeLoaderListener
{
    CC_SYNTHESIZE(int, m_curSel, CurSel);
    CC_SYNTHESIZE(IFormationLayerDelegate*, m_delegate, Delegate)
public:
    CREATE_FUNC(CFormationPanelLayer);
    
    CFormationPanelLayer();
    virtual ~CFormationPanelLayer();
    
    virtual bool init();
    
    //CCBSelectorResolver
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName) ;
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName) ;
    
    //CCBMemberVariableAssigner
    virtual bool onAssignCCBMemberVariable(Object * pTarget, const char* pMemberVariableName, Node * pNode);
    
    virtual void onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader);

protected:
    virtual void touchBegan(Point position);
    virtual void touchMoved(Point position);
    virtual void touchEnded(Point position);
    
    virtual void onBack(Object *pSender);
    virtual void onSave(Object* pSender);
    virtual void onLoad(Object* pSender);
    virtual void onSave1(Object* pSender);
    virtual void onLoad1(Object* pSender);
    virtual void onUp(Object *pSender);
    virtual void onDown(Object *pSender);
    
    virtual void onFrame(Object *pSender);
    
    virtual void setFrameShowRole(int fromIdx);
private:
    VS m_editRoleIds;     // 可在阵型中编辑的兵种名字，将来是从玩家解锁的兵种中得来，这里暂时写死
    Array* m_allRoles;                // 与m_editRoleNames一一对应
    MenuItem* m_frames[FRAME_NUM];

    int m_firstShownIdx;
};


class CFormationPanelLayerLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CFormationPanelLayerLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CFormationPanelLayer);
};

#endif /* defined(__GameX__CFormationPanelLayer__) */
