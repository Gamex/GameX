//
//  Common.h
//  TheForce
//
//  Created by Ming Zhao on 2/11/13.
//  Copyright (c) 2013 Tencent. All rights reserved.
//

#ifndef TheForce_Common_h
#define TheForce_Common_h

#pragma mark - Math

#define FLT_EQUAL(x, y) (fabsf((x) - (y)) < FLT_EPSILON)
#define FLT_LE(x, y)    ((x) < (y) || fabsf((x) - (y)) < FLT_EPSILON)
#define FLT_GE(x, y)    ((x) > (y) || fabsf((x) - (y)) < FLT_EPSILON)

#pragma mark - Colors

#define COLOR4B_TRANSPARENT         (ccc4(0, 0, 0, 0))
#define COLOR4B_DARK_TRANSPARENT    (ccc4(0, 0, 0, 220))

#pragma mark - Notifications

//#define NOTIFICATION_TRANSIT_MESSAGE        "NotificationTransitMessage"

#pragma mark - Textures

enum GameArts
{
    GA_ACTORS = 0,
    GA_BULLETS,
    GA_SCENES,
    GA_HUDS,
    GAME_ARTS_MAX
};

#define GAME_ARTS_TEXT(val) ((string[]) {"ga_actors", \
                                         "ga_bullets", \
                                         "ga_scenes", \
                                         "ga_huds",\
                                         "", \
                                        }[(val)])

enum GameFonts
{
    GAME_FONTS_MESSAGE = 0,
    GAME_FONTS_MAX
};

enum LAYERS
{
    LAYERS_NONE = 0,
    LAYERS_LOBBY,
    LAYERS_FORMATION,
    LAYERS_GAME_BATTLE_FIELD,
    LAYERS_SETTINGS,
    LAYERS_UPGRADE,
    LAYERS_MAX,
};


#define GAME_FONTS_TEXT(val)    ((string[]) {"yahei", \
                                             "", \
                                            }[(val)])



#pragma mark - User defaults

enum GameSettings
{
    GAME_SETTINGS_NULL = 0,
    GAME_SETTINGS_MAX,
};
#define GAME_SETTINGS_TEXT(val)  ((string[]) {"GAME_SETTINGS_NULL", \
                                              "", \
                                             }[(val)])

#define SaveStringToUserDefault(key, value) \
        CCUserDefault::sharedUserDefault()->setStringForKey(GAME_SETTINGS_TEXT((key)).c_str(), (value))
#define SaveIntegerToUserDefault(key, value) \
        CCUserDefault::sharedUserDefault()->setIntegerForKey(GAME_SETTINGS_TEXT((key)).c_str(), (value))
#define SaveBooleanToUserDefault(key, value) \
        CCUserDefault::sharedUserDefault()->setBoolForKey(GAME_SETTINGS_TEXT((key)).c_str(), (value))
#define LoadStringFromUserDefault(key, dVal) \
        CCUserDefault::sharedUserDefault()->getStringForKey(GAME_SETTINGS_TEXT((key)).c_str(), (dVal))
#define LoadIntegerFromUserDefault(key, dVal) \
        CCUserDefault::sharedUserDefault()->getIntegerForKey(GAME_SETTINGS_TEXT((key)).c_str(), (dVal))
#define LoadBooleanFromUserDefault(key, dVal) \
        CCUserDefault::sharedUserDefault()->getBoolForKey(GAME_SETTINGS_TEXT((key)).c_str(), (dVal))
#define FlushUserDefault      CCUserDefault::sharedUserDefault()->flush()


#pragma mark - 

#define BREAK_IF(__condi__) \
if (__condi__)\
{\
    break;\
}


#define BREAK_IF_FAILED(__condi__) \
if (false == (__condi__))\
{\
__CCLOGWITHFUNCTION("File: %s, Line: %d", __FILE__, __LINE__);\
break;\
}


#define D_TO_A(__x__)       (__x__ * CCBReader::getResolutionScale())

#pragma mark -- Collision

class CObjectBase;
class TFCollisionProtocol;
typedef void (CObjectBase::*COLLISION_HANDLER)(TFCollisionProtocol*);
#define collision_handler_selector(_SELECTOR) (COLLISION_HANDLER)(&_SELECTOR)

enum GBCollisionType {
    CT_INVALID = -1,
    CT_HERO = 0,
    CT_MONSTER,
    CT_COIN,
    CT_BULLET,
    CT_SENSOR,
    CT_SOLDIER,
};

#pragma mark -- cocos2d-x headers
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

#pragma mark -- Pomelo
#include "jansson.h"
#include "pomelo.h"

#pragma mark -- stl headers and typedefs for stl container
#include <set>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <algorithm>
#include <functional>


using namespace std;

typedef std::vector<unsigned int> VUI;
typedef std::vector<unsigned int>::iterator VUI_IT;
typedef std::vector<unsigned int>::const_iterator VUI_CIT;

typedef std::vector<std::string> VS;
typedef std::vector<std::string>::iterator VS_IT;
typedef std::vector<std::string>::const_iterator VS_CIT;

typedef std::set<std::string> SS;
typedef std::set<std::string>::iterator SS_IT;
typedef std::set<std::string>::const_iterator SS_CIT;

typedef std::set<class CRole*> SR;
typedef std::set<class CRole*>::iterator SR_IT;
typedef std::set<class CRole*>::const_iterator SR_CIT;

typedef std::queue<class CRole*> QR;

typedef std::map<std::string, SpriteBatchNode*> MSSBN;              // batch node name -> batch node object
typedef std::map<std::string, SpriteBatchNode*>::iterator MSSBN_IT;
typedef std::map<std::string, SpriteBatchNode*>::const_iterator MSSBN_CIT;

typedef std::vector<class IFightingRelation*> VR;
typedef std::vector<class IFightingRelation*>::iterator VR_IT;
typedef std::vector<class IFightingRelation*>::const_iterator VR_CIT;

typedef std::map<class IFightingRelation*, VR> MRVR;
typedef std::map<class IFightingRelation*, VR>::iterator MRVR_IT;
typedef std::map<class IFightingRelation*, VR>::const_iterator MRVR_CIT;


typedef std::vector<class CFormationElement*> VFE;
typedef std::vector<class CFormationElement*>::iterator VFE_IT;
typedef std::vector<class CFormationElement*>::const_iterator VFE_CIT;


typedef std::map<int, SS> VSS;
typedef std::map<int, SS>::iterator VSS_IT;
typedef std::map<int, SS>::const_iterator VSS_CIT;


typedef std::queue<class _FinderTask*> QFT;

typedef std::set<class TFCollisionProtocol*> LRB;
typedef std::set<class TFCollisionProtocol*>::iterator LRB_IT;
typedef std::set<class TFCollisionProtocol*>::const_iterator LRB_CIT;

typedef std::vector<LRB> MILRB;
typedef std::vector<LRB>::iterator MILRB_IT;
typedef std::vector<LRB>::const_iterator MILRB_CIT;


typedef std::map<GBCollisionType, COLLISION_HANDLER> MICH;
typedef std::map<GBCollisionType, COLLISION_HANDLER>::iterator MICH_IT;
typedef std::map<GBCollisionType, COLLISION_HANDLER>::const_iterator MICH_CIT;


typedef std::map<class CRole*, float> MRF;
typedef std::map<class CRole*, float>::iterator MRF_IT;
typedef std::map<class CRole*, float>::const_iterator MRF_CIT;


typedef std::map<int, string> MIS;
typedef std::map<int, string>::iterator MIS_IT;
typedef std::map<int, string>::const_iterator MIS_CIT;


typedef std::map<int, timeval> MIT;
typedef std::map<int, timeval>::iterator MIT_IT;
typedef std::map<int, timeval>::const_iterator MIT_CIT;


typedef std::set<class ICCBAnimationDelegate*> SAD;
typedef std::set<class ICCBAnimationDelegate*>::iterator SAD_IT;
typedef std::set<class ICCBAnimationDelegate*>::const_iterator SAD_CIT;


typedef std::set<class CObjectBase*> SOB;
typedef std::set<class CObjectBase*>::iterator SOB_IT;
typedef std::set<class CObjectBase*>::const_iterator SOB_CIT;

typedef std::vector<class CNodeContainer*> VNC;
typedef std::vector<class CNodeContainer*>::iterator VNC_IT;
typedef std::vector<class CNodeContainer*>::const_iterator VNC_CIT;

typedef std::map<int, class CVisibleObject*> MISVO;
typedef std::map<int, class CVisibleObject*>::iterator MISVO_IT;
typedef std::map<int, class CVisibleObject*>::const_iterator MISVO_CIT;

#pragma mark --debug

#ifdef DEBUG
#define MARK_ROLE(__R__) (__R__)->setMark(true);
#define UNMARK_ROLE(__R__) (__R__)->setMark(false);

#else

#define MARK_ROLE(__R__)
#define UNMARK_ROLE(__R__)

#endif
#endif
