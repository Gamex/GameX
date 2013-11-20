//
//  CLoginLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-11-20.
//
//

#include "CLoginLayer.h"

static class CLoginLayerRegister
{
public:
    CLoginLayerRegister()
    {
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CLoginLayer", CLoginLayerLoader::loader());
    }
} __reg;



CLoginLayer::CLoginLayer()
: m_editUserNameLayer(nullptr)
, m_editPasswordLayer(nullptr)
{
}



CLoginLayer::~CLoginLayer()
{
}



SEL_MenuHandler CLoginLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onLogin", CLoginLayer::onLogin);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onCancel", CLoginLayer::onCancel);
//    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTestSocket", CLobbyLayer::onTestSocket);
    return nullptr;
}

//函数定义类型为：void pressTitle(Object *pSender);
Control::Handler CLoginLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onLogin", CLoginLayer::onLogin);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onCancel", CLoginLayer::onCancel);
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CLobbyLayer::controlButtonTest);
    return nullptr;
}

bool CLoginLayer::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_edtUserNameLayer", Layer*, m_editUserNameLayer);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "m_edtPasswordLayer", Layer*, m_editPasswordLayer);
    return false;
}


void CLoginLayer::onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader)
{
    SpriteFrame *pFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("huds/hp_bar_bg0.png");
    CC_ASSERT(pFrame);
    Size sz = pFrame->getRect().size;
    Scale9Sprite* s9s = Scale9Sprite::createWithSpriteFrameName("huds/hp_bar_bg0.png", Rect(1, 1, sz.width-2, sz.height-2));
    
    EditBox* userName = EditBox::create(m_editUserNameLayer->getContentSize(), s9s);
    CC_ASSERT(userName);
    userName->setAnchorPoint(Point(0.f, 0.f));
    m_editUserNameLayer->addChild(userName);
    
    s9s = Scale9Sprite::createWithSpriteFrameName("huds/hp_bar_bg0.png", Rect(1, 1, sz.width-2, sz.height-2));
    EditBox* password = EditBox::create(m_editPasswordLayer->getContentSize(), s9s);
    CC_ASSERT(password);
    password->setAnchorPoint(Point(0.f, 0.f));
    m_editPasswordLayer->addChild(password);
}




bool CLoginLayer::init()
{
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("huds.plist");
    
	return true;
}



void CLoginLayer::onLogin(Object* sender, Control::EventType event)
{
}



void CLoginLayer::onCancel(Object* sender, Control::EventType event)
{
}



