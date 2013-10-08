//
//  CBkgLayerBase.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-5.
//
//

#include "CBkgLayerBase.h"

#define INVALIDE_TAP_POS        CCPoint(FLT_MAX, FLT_MAX)

CBkgLayerBase::CBkgLayerBase()
: m_bkgGrd(NULL)
, m_batchNode(NULL)
, m_pathFinder(NULL)
, m_layer(NULL)
, m_lastLength(0.f)
, m_touches(NULL)
{

}



CBkgLayerBase::~CBkgLayerBase()
{
    setBkgGrd(NULL);
    setBatchNode(NULL);
    CC_SAFE_DELETE(m_pathFinder);
    CC_SAFE_RELEASE(m_touches);
}



bool CBkgLayerBase::initBkgLayerBase(const char* batchNodeName)
{
    do
    {
        m_layer = dynamic_cast<CCLayer*>(this);
        CC_ASSERT(m_layer);
        
        setBatchNode(CBatchNodeManager::create());
        BREAK_IF_FAILED(m_batchNode);
        BREAK_IF_FAILED(m_batchNode->loadBatchNodeInitData(batchNodeName));
        
        setBkgGrd(CBackgroundManager::create());
        BREAK_IF_FAILED(m_bkgGrd);
        
        m_bkgGrd->attachBackgroundTo(m_layer);
        m_batchNode->attachToParent(m_bkgGrd, 0);
        
        
        m_pathFinder = new CPathFinderManager;
        m_pathFinder->setBkg(m_bkgGrd);
        
        m_tapStartPoint = INVALIDE_TAP_POS;
        m_scaleCenterGridPos = INVALIDE_TAP_POS;
        
        m_touches = CCArray::create();
        CC_SAFE_RETAIN(m_touches);
        return true;
    } while (false);
    
    return false;
}



void CBkgLayerBase::bkgLayerBaseTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCSetIterator it;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        CCTouch* tch = (CCTouch*)*it;
        if (!m_touches->containsObject(tch))
        {
            m_touches->addObject(tch);
        }
    }
}



void CBkgLayerBase::bkgLayerBaseTouchesMoved(CCSet* touches, CCEvent* event)
{
    switch (m_touches->count())
    {
        case 1:
        {
            CCArray* tch = m_touches;
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = m_layer->convertToNodeSpace(point1);

            if (!m_tapStartPoint.equals(INVALIDE_TAP_POS))
            {
                CCPoint offset = location1 -  m_tapStartPoint;
                m_bkgGrd->moveMap(offset);
            }
            m_tapStartPoint = location1;

            break;
        }

        case 2:
        {
            CCArray* tch = m_touches;
            CCTouch* t1 = (CCTouch*)tch->objectAtIndex(0);
            CCTouch* t2 = (CCTouch*)tch->objectAtIndex(1);
            
            CCPoint point1 = CCDirector::sharedDirector()->convertToUI(t1->getLocationInView());
            CCPoint location1 = m_layer->convertToNodeSpace(point1);
            
            CCPoint point2 = CCDirector::sharedDirector()->convertToUI(t2->getLocationInView());
            CCPoint location2 = m_layer->convertToNodeSpace(point2);
            
            
            if (m_scaleCenterGridPos.equals(INVALIDE_TAP_POS))
            {
                m_lastLength = (location2 - location1).getLengthSq();
                CCPoint center = CCDirector::sharedDirector()->getWinSize();
                center = center * 0.5f;
                m_scaleCenterGridPos = m_bkgGrd->screenPointToGrid(center);
            }
            else
            {
                float len = (location2 - location1).getLengthSq();
                
                if (len > m_lastLength)
                {
                    // zoom out
                    m_bkgGrd->addMapScale(0.05, m_scaleCenterGridPos);
                }
                else if (len < m_lastLength)
                {
                    // zoom in
                    m_bkgGrd->addMapScale(-0.05, m_scaleCenterGridPos);
                }
                
                m_lastLength = len;
            }
            break;
        }
        default:
            break;
    }
}



void CBkgLayerBase::bkgLayerBaseTouchesEnded(CCSet* touches, CCEvent* event)
{
    m_tapStartPoint = INVALIDE_TAP_POS;
    m_scaleCenterGridPos = INVALIDE_TAP_POS;
    
    CCSetIterator it;
    
    for( it = touches->begin(); it != touches->end(); it++)
    {
        CCTouch* tch = (CCTouch*)*it;

        m_touches->removeObject(tch);
    }
}



void CBkgLayerBase::update(float dt)
{
    m_bkgGrd->update(dt);
    
//    static float s = 1.f;
//    static float delta = 0.05f;
//    s += delta;
//    if (FLT_GE(s, 2.f) || FLT_LE(s, .5f))
//    {
//        delta *= -1;
//    }
//    m_bkgGrd->scaleMap(s);
}
