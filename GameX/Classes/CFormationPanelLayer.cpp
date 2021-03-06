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
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CFormationPanelLayer", CFormationPanelLayerLoader::loader());
    }
} __reg;


CFormationPanelLayer::CFormationPanelLayer()
: m_firstShownIdx(0)
, m_delegate(nullptr)
{
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        m_frames[i] = nullptr;
    }
}



CFormationPanelLayer::~CFormationPanelLayer()
{
    CC_SAFE_RELEASE(m_allRoles);
}



bool CFormationPanelLayer::init()
{
    do
    {
//        setTouchEnabled(true);
        
        m_editRoleIds.push_back("1001");
        m_editRoleIds.push_back("1002");
        m_editRoleIds.push_back("1003");
//        m_editRoleIds.push_back("4");
//        m_editRoleIds.push_back("5");
//        m_editRoleIds.push_back("6");
//        m_editRoleIds.push_back("7");
//        m_editRoleIds.push_back("8");
//        m_editRoleIds.push_back("9");
//        m_editRoleIds.push_back("10");
//        m_editRoleIds.push_back("11");
//        m_editRoleIds.push_back("12");

        m_allRoles = Array::createWithCapacity(m_editRoleIds.size());
        CC_SAFE_RETAIN(m_allRoles);
        for (int i = 0; i < m_editRoleIds.size(); ++i)
        {
            const DTUnit::_Data* unitData = DTUNIT->getData(m_editRoleIds[i]);
            CC_ASSERT(unitData);
            CRole* role = dynamic_cast<CRole*>(OBJECT_FACTORY->createInstance(unitData->className));
            CC_ASSERT(role);
            role->init(m_editRoleIds[i], true);

            m_allRoles->addObject(role);
        }
        return true;
    } while (false);
    
    return false;
}


SEL_MenuHandler CFormationPanelLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBack", CFormationPanelLayer::onBack);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSave", CFormationPanelLayer::onSave);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLoad", CFormationPanelLayer::onLoad);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onSave1", CFormationPanelLayer::onSave1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLoad1", CFormationPanelLayer::onLoad1);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onUp", CFormationPanelLayer::onUp);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onDown", CFormationPanelLayer::onDown);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF0", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF1", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF2", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF3", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF4", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF5", CFormationPanelLayer::onFrame);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onF6", CFormationPanelLayer::onFrame);
    
    return nullptr;
}

//函数定义类型为：void pressTitle(Object *pSender);
Control::Handler CFormationPanelLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CFormationPanelLayer::controlButtonTest);
    return nullptr;
}

bool CFormationPanelLayer::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
    for (int i = 0; i < FRAME_NUM; ++i)
    {
        char s[20];
        sprintf(s, "m_f%d", i);
        CCB_MEMBERVARIABLEASSIGNER_GLUE(this, s, MenuItem*, m_frames[i]);
    }

    return false;
}


void CFormationPanelLayer::onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader)
{
    setFrameShowRole(0);
}



void CFormationPanelLayer:: onBack(Object *pSender)
{
    SCENE_MANAGER->go(ST_LOBBY);
}



void CFormationPanelLayer:: onSave(Object *pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation();
    fmt->m_elements.clear();
    fmt->m_filename = "f.fmt";
    if (m_delegate)
    {
        m_delegate->onSave(fmt);
    }
    
}



void CFormationPanelLayer::onLoad(Object *pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation();
    fmt->m_elements.clear();
    fmt->m_filename = "f.fmt";
    if (m_delegate)
    {
        m_delegate->onLoad(fmt);
    }
    
}



void CFormationPanelLayer::onSave1(Object* pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation1();
    fmt->m_elements.clear();
    fmt->m_filename = "f1.fmt";
    if (m_delegate)
    {
        m_delegate->onSave(fmt);
    }
}



void CFormationPanelLayer::onLoad1(Object* pSender)
{
    CFormation* fmt = FORMATION_MANAGER->getFormation1();
    fmt->m_elements.clear();
    fmt->m_filename = "f1.fmt";
    if (m_delegate)
    {
        m_delegate->onLoad(fmt);
    }
}




void CFormationPanelLayer:: onUp(Object *pSender)
{
}



void CFormationPanelLayer:: onDown(Object *pSender)
{
}



void CFormationPanelLayer:: onFrame(Object *pSender)
{
    MenuItem* menu = dynamic_cast<MenuItem*>(pSender);
    CC_ASSERT(menu);
    
    
    m_curSel = menu->getTag() - MENU_FRAME_TAG_START;
    

    if (m_delegate)
    {
        int index = m_curSel + m_firstShownIdx;
        CC_ASSERT(index < m_editRoleIds.size());
        m_delegate->onFrameSel(m_editRoleIds[index]);
    }
}



void CFormationPanelLayer::setFrameShowRole(int fromIdx)
{
    CC_ASSERT(fromIdx < m_allRoles->count());
    
    m_firstShownIdx = fromIdx;
    int i;
    for (i = 0; i < FRAME_NUM; ++ i)
    {
#ifdef DEBUG
        if (m_frames[i]->getChildByTag(TAG_ROLE))
        {
#endif
        m_frames[i]->removeChildByTag(TAG_ROLE, false);
            
#ifdef DEBUG
        }
#endif
        int index = i + fromIdx;
        if (index < m_allRoles->count())
        {
            m_frames[i]->setEnabled(true);
            CRole* role = (CRole*)m_allRoles->getObjectAtIndex(index);
            CC_ASSERT(role);
            Size sz = m_frames[i]->getContentSize();
            role->setSpritePosition(Point(sz.width / 2.f, sz.height / 2.f));
            role->attachSpriteTo(m_frames[i], 0, TAG_ROLE);
            role->setFaceTo(FACE_TO_LEFT_DOWN);
            role->playAnimation(ROLE_ANIMATION_IDLE);
        }
        else
        {
            m_frames[i]->setEnabled(false);
        }
    }

}



void CFormationPanelLayer::touchBegan(Point position)
{
}



void CFormationPanelLayer::touchMoved(Point position)
{
}



void CFormationPanelLayer::touchEnded(Point position)
{
}

