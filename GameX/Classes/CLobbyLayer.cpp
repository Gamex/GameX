//
//  CLobbyLayer.cpp
//  GameX
//
//  Created by 马 俊 on 13-8-28.
//
//

#include "CLobbyLayer.h"
#include "CGameSceneManager.h"

#include "CCPomelo.h"

static class CLobbyLayerRegister
{
public:
    CLobbyLayerRegister()
    {
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CLobbyLayer", CLobbyLayerLoader::loader());
    }
} __reg;




CLobbyLayer::CLobbyLayer()
{

}



CLobbyLayer::~CLobbyLayer()
{
    
}



bool CLobbyLayer::init()
{
    do
    {
        return true;
    } while (false);
    
    return false;
}


SEL_MenuHandler CLobbyLayer::onResolveCCBCCMenuItemSelector(Object * pTarget, const char* pSelectorName)
{
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onFormation", CLobbyLayer::onFormation);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onBattle", CLobbyLayer::onBattle);
    CCB_SELECTORRESOLVER_CCMENUITEM_GLUE(this, "onTestSocket", CLobbyLayer::onTestSocket);
    return nullptr;
}

//函数定义类型为：void pressTitle(Object *pSender);
Control::Handler CLobbyLayer::onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName)
{
//    CCB_SELECTORRESOLVER_CCCONTROL_GLUE( this, "pressTitle", CLobbyLayer::controlButtonTest);
    return nullptr;
}

bool CLobbyLayer::onAssignCCBMemberVariable(Object* pTarget, const char* pMemberVariableName, Node* pNode)
{
//    CCB_MEMBERVARIABLEASSIGNER_GLUE( this, "helloLabel", CCLabelTTF*, helloLabel);
    return false;
}


void CLobbyLayer::onNodeLoaded(Node * pNode, NodeLoader * pNodeLoader)
{
    
}



void CLobbyLayer::onFormation(Object *pSender)
{
    SCENE_MANAGER->go(ST_FORMATION);
}



void CLobbyLayer::onBattle(Object* pSender)
{
    SCENE_MANAGER->go(ST_BATTLE_FIELD);
}


void CLobbyLayer::onTestSocket(Object* pSender)
{
    std::string ip = "192.168.1.4";
    int port = 3010;

    if(0 != POMELO->connect(ip.c_str(), port))
    {
        CCLOG("connect fiald ");
    }
    else
    {
        CCLOG("connect ok");
        const char *route = "connector.entryHandler.entry";
        json_t *msg = json_object();
        json_object_set(msg, "hello pomelo", json_integer(1));
        POMELO->request(route, msg, bind(&CLobbyLayer::onMsg, this, std::placeholders::_1, std::placeholders::_2));
    }
}



void CLobbyLayer::onMsg(Node* node, void* resp)
{
    CCPomeloReponse* ccpomeloresp = (CCPomeloReponse*)resp;
    CCLOG("entryCB %s",json_dumps(ccpomeloresp->docs, JSON_COMPACT));
    
    json_t* msg = json_object_get(ccpomeloresp->docs, "msg");
    
    CCLOG("msg: %s", json_string_value(msg));
//
//    CCPomelo::getInstance()->addListener("onChat",this, callfuncND_selector(HelloWorld::onChat));
//    
//    const char *route = "chat.chatHandler.send";
//    json_t *msg = json_object();
//    json_object_set(msg, "content", json_string("hello CCPomelo"));
//    json_object_set(msg, "target", json_string("*"));
//    CCPomelo::getInstance()->request(route, msg, this,  callfuncND_selector(HelloWorld::sendCB));
}

