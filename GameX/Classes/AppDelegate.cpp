//
//  TheForceAppDelegate.cpp
//  TheForce
//
//  Created by Ming Zhao on 2/1/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "Common.h"
#include "TFGameObjectManager.h"
#include "CGlobalConfigration.h"
#include "CObjectFactory.h"
#include "CPathManager.h"
#include "TFCollisionMgr.h"
#include "CRole.h"
#include "CBatchNodeManager.h"
#include "CDataCenterManager.h"
#include "CBackgroundManager.h"
#include "CGameSceneManager.h"

#include <time.h>

#include <vector>


USING_NS_CC;

AppDelegate::AppDelegate()
{
    time_t t;
    srand((unsigned) time(&t));
}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    this->setupConfigurationFiles();
    
    this->setupMultipleResolutionSupport();
    
    // create a scene. it's an autorelease object
    do
    {
        BREAK_IF_FAILED(DATA_CENTER->initialize());
        
        BREAK_IF_FAILED(OBJECT_FACTORY->Initialize());

        BREAK_IF_FAILED(GAME_OJBECT_MANAGER->init());
        
        BREAK_IF_FAILED(COLLISION_MANAGER->init());

        BREAK_IF_FAILED(PATH_MANAGER->initialize());
        
        BREAK_IF_FAILED(BATCH_NODE_MANAGER->initialize());
        
        BREAK_IF_FAILED(BKG_MANAGER->initialize());
        
        BREAK_IF_FAILED(SCENE_MANAGER->initialize());
        
        
        SCENE_MANAGER->go(ST_LOBBY);
        
        return true;
    } while (false);
        

    return false;
}



// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}



// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}



void AppDelegate::setupConfigurationFiles()
{
//    const char* udFileName = "GameSettings.plist";
//
//    if (!CCUserDefault::sharedUserDefault()->getBoolForKey("_IS_EXISTED", false))
//    {
//        CCDictionary* dict = CCDictionary::createWithContentsOfFile(udFileName);
//        for (int i = 0; i < GAME_SETTINGS_MAX; i++)
//        {
//            const CCString* value = dict->valueForKey(GAME_SETTINGS_TEXT(i));
//            SaveStringToUserDefault(i, value->getCString());
//        }
//        
//        CCUserDefault::sharedUserDefault()->setBoolForKey("_IS_EXISTED", true);
//        
//        FlushUserDefault;
//    }
}


void AppDelegate::setupMultipleResolutionSupport()
{
    CCSize sizeIphone = CCSizeMake(480, 320);
    CCSize sizeIphoneHD = CCSizeMake(960, 640);
    CCSize sizeIphone5 = CCSizeMake(1136, 640);
    CCSize sizeIpad = CCSizeMake(1024, 768);
    CCSize sizeIpadHD = CCSizeMake(2048, 1536);
    
    CCSize designSize = sizeIphoneHD;
    CCSize resourceSize = sizeIphoneHD;
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;
    
    TargetPlatform platform = CCApplication::sharedApplication()->getTargetPlatform();
    if (platform == kTargetIphone || platform == kTargetIpad)
    {
        CCFileUtils::sharedFileUtils()->setSearchPaths(searchPaths);
        
        if (screenSize.height > 768)
        {
            resourceSize = sizeIpadHD;
            designSize = sizeIpadHD;
            resDirOrders.push_back("resources-ipadhd");
            
            CCBReader::setResolutionScale(4.0f);
        } else if (screenSize.height > 640) {
            resourceSize = sizeIpad;
            designSize = resourceSize;
            resDirOrders.push_back("resources-ipad");
            resDirOrders.push_back("resources-iphonehd");
            
            CCBReader::setResolutionScale(2.0f);
        } else if (screenSize.height > 480) {
            if (screenSize.width > 960) {
                designSize = sizeIphone5;
            }
            else {
                designSize = sizeIphoneHD;
            }
            resourceSize = sizeIphoneHD;
            
            CCBReader::setResolutionScale(2.0f);
            
            resDirOrders.push_back("resources-iphonehd");
        } else {
            CCBReader::setResolutionScale(1.0f);
            
            designSize = sizeIphone;
            resourceSize = sizeIphone; 
            
            resDirOrders.push_back("resources-iphone"); 
        } 
        
        CCFileUtils::sharedFileUtils()->setSearchResolutionsOrder(resDirOrders); 
    } 
    
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->setContentScaleFactor(resourceSize.width / designSize.width); 
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize( 
                                                              designSize.width, designSize.height, 
                                                              kResolutionExactFit); 

    // set texture resoures
    GLOBAL_CONFIG->setTextureSuffix("");
}


