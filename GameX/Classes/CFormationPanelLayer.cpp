//
//  CFormationPanelLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-29.
//
//

#include "CFormationPanelLayer.h"
#include "CGameSceneManager.h"
#include "CGlobalConfigration.h"
#include "CFormationManager.h"
#include "CWarriorRole.h"
#include "CDataCenterManager.h"

#define MENU_FRAME_TAG_START            100         // the tag is defined in cocosbuilder

#define TAG_ROLE                        711


static class CFormationPanelLayerRegister
{
public:
    CFormationPanelLayerRegister()
    {
        CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader( "CFormationPanelLayer", CFormationPanelLayerLoader::loader());
    }
} __reg;


CFormationPanelLayer::CFormationPanelLayer()
: m_firstShownIdx(0)
, m_delegate(NULL)
{
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        m_frames[i] = NULL;
    }
}



CFormationPanelLayer::~CFormationPanelLayer()
{
    
}



bool CFormationPanelLayer::init()
{
    do
    {
        m_editRoleNames.push_back("1");
        m_editRoleNames.push_back("2");
//        m_editRoleNames.push_back("3");
//        m_editRoleNames.push_back("4");
//        m_editRoleNames.push_back("5");
//        m_editRoleNames.push_back("6");
//        m_editRoleNames.push_back("7");
//        m_editRoleNames.push_back("8");
//        m_editRoleNames.push_back("9");
//        m_editRoleNames.push_back("10");
//        m_editRoleNames.push_back("11");
//        m_editRoleNames.push_back("12");

        m_allRoles = CCArray::createWithCapacity(m_editRoleNames.size());
        for (int i = 0; i < m_editRoleNames.size(); ++i)
        {
            CCDictionary* dict = DTUNIT->getData(m_editRoleNames[i]);
            CCString* name = DTUNIT->get_resourceID_Value(dict);
            CRole* role = dynamic_cast<CRole*>(CObjectBase::createObject(name->getCString()));
            CC_ASSERT(role);
            m_allRoles->addObject(role);
        }
        return true;
    } while (false);
    
    return false;
}


SEL_MenuHandler CFormationPanelLayer::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBack", CFormationPanelLayer::onBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSave", CFormationPanelLayer::onSave);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLoad", CFormationPanelLayer::onLoad);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUp", CFormationPanelLayer::onUp);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDown", CFormationPanelLayer::onDown);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF0", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF1", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF2", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF3", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF4", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF5", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF6", CFormationPanelLayer::onFrame);
    
    return NULL;
}

//函数定义类型为：void pressTitle(CCObject *pSender);
SEL_CCControlHandler CFormationPanelLayer::onResolveCCBCCControlSelector(CCObject * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CFormationPanelLayer::controlButtonTest);
    return NULL;
}

bool CFormationPanelLayer::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        char s[20];
        sprintf(s, "m_f%d", i);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, s, CCMenuItem*, m_frames[i]);
    }

    return false;
}


void CFormationPanelLayer::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    setFrameShowRole(0);
}



void CFormationPanelLayer:: onBack(CCObject *pSender)
{
    SCENE_MANAGER->go(ST_LOBBY);
}



void CFormationPanelLayer:: onSave(CCObject *pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation();
    fmt->m_elements.clear();
    
    if (m_delegate)
    {
        m_delegate->onSave(fmt);
    }
    
}



void CFormationPanelLayer::onLoad(CCObject *pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation();
    fmt->m_elements.clear();
    
    if (m_delegate)
    {
        m_delegate->onLoad(fmt);
    }
    
}



void CFormationPanelLayer:: onUp(CCObject *pSender)
{
}



void CFormationPanelLayer:: onDown(CCObject *pSender)
{
}



void CFormationPanelLayer:: onFrame(CCObject *pSender)
{
    CCMenuItem* menu = dynamic_cast<CCMenuItem*>(pSender);
    CC_ASSERT(menu);
    
    
    m_curSel = menu->getTag() - MENU_FRAME_TAG_START;
    

    if (m_delegate)
    {
        int index = m_curSel + m_firstShownIdx;
        CC_ASSERT(index < m_editRoleNames.size());
        m_delegate->onFrameSel(m_editRoleNames[index]);
    }
}



void CFormationPanelLayer::setFrameShowRole(int fromIdx)
{
    CC_ASSERT(fromIdx < m_allRoles->count());
    
    m_firstShownIdx = fromIdx;
    int i;
    for (i = 0; i < FRAME_NUM; ++ i)
    {
        m_frames[i]->removeChildByTag(TAG_ROLE, false);
        int index = i + fromIdx;
        if (index < m_allRoles->count())
        {
            m_frames[i]->setEnabled(true);
            CRole* role = (CRole*)m_allRoles->objectAtIndex(index);
            CC_ASSERT(role);
            CCSize sz = m_frames[i]->getContentSize();
            role->setSpritePosition(ccp(sz.width / 2.f, sz.height / 2.f));
            role->attachSpriteTo(m_frames[i], 0, TAG_ROLE);
            role->setfaceTo(FACE_TO_LEFT);
            role->changeState(ROLE_STATE_IDLE);
        }
        else
        {
            m_frames[i]->setEnabled(false);
        }
    }

}


