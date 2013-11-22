//
//  CLoginLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-11-20.
//
//

#include "CLoginLayer.h"
#include "CCPomelo.h"
#include "CGameSceneManager.h"
#include "CMessageBoxLayer.h"

static class CLoginLayerRegister
{
public:
    CLoginLayerRegister()
    {
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CLoginLayer", CLoginLayerLoader::loader());
    }
} __reg;



CLoginLayer::CLoginLayer()
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
    m_userName = createEdit("huds/hp_bar_bg0.png", m_editUserNameLayer->getContentSize());
    CC_ASSERT(m_userName);
    m_userName->setAnchorPoint(Point(0.f, 0.f));
    m_editUserNameLayer->addChild(m_userName);
    m_userName->setInputMode(EditBox::InputMode::SINGLE_LINE);

    m_password = createEdit("huds/hp_bar_bg0.png", m_editPasswordLayer->getContentSize());
    CC_ASSERT(m_password);
    m_password->setAnchorPoint(Point(0.f, 0.f));
    m_editPasswordLayer->addChild(m_password);
    m_password->setInputMode(EditBox::InputMode::SINGLE_LINE);
    m_password->setInputFlag(EditBox::InputFlag::PASSWORD);
    
#if DEBUG
    m_userName->setText("test1");
    m_password->setText("123");
#endif

}




bool CLoginLayer::init()
{
    SpriteFrameCache* sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("huds.plist");
    
	return true;
}



void CLoginLayer::onLogin(Object* sender, Control::EventType event)
{
    std::string ip = "10.73.9.36";
    int port = 3017;

    CMessageBoxLayer* mb = CMessageBoxLayer::create();
    mb->setMsg("Connecting...");
    mb->doModal();

    if (0 != POMELO->asyncConnect(ip.c_str(), port, [&, mb](Node* node, void* resp)
                         {
                             CCPomeloReponse* pr = (CCPomeloReponse*)resp;
                             if (pr->status != 0)
                             {
                                 CCLOG("not connected!");
                                 mb->closeModal();
                                 return;
                             }
                             CCLOG("connect ok");
                             const char *route = "gate.gateHandler.queryEntry";
                             json_t *msg = json_object();
                             json_object_set(msg, "userName", json_string(m_userName->getText()));
                             json_object_set(msg, "password", json_string(m_password->getText()));
                             POMELO->request(route, msg, [&, mb](Node* node, void* resp){
                                 CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
                                 CCLOG("entryCB %s",json_dumps(ccpomeloresp->docs, JSON_COMPACT));
                                 
                                 json_t* host = json_object_get(ccpomeloresp->docs, "host");
                                 
                                 CCLOG("host: %s", json_string_value(host));
                                 
                                 mb->closeModal();
                             });
                         }))
    {
        mb->closeModal();
    }
}



void CLoginLayer::onCancel(Object* sender, Control::EventType event)
{
    SCENE_MANAGER->go(ST_LOBBY);
}



