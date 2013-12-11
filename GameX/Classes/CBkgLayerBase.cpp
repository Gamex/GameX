//
//  CBkgLayerBase.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-5.
//
//

#include "CBkgLayerBase.h"

#define INVALIDE_TAP_POS        Point(FLT_MAX, FLT_MAX)

CBkgLayerBase::CBkgLayerBase()
: m_bkgGrd(nullptr)
, m_batchNode(nullptr)
, m_pathFinder(nullptr)
, m_layer(nullptr)
, m_lastLength(0.f)
{

}



CBkgLayerBase::~CBkgLayerBase()
{
    setBkgGrd(nullptr);
    setBatchNode(nullptr);
    CC_SAFE_DELETE(m_pathFinder);
    
    vector<Touch*>::iterator it = m_touches.begin();
    for (; it != m_touches.end(); ++it)
    {
        CC_SAFE_RELEASE(*it);
    }
    m_touches.clear();
}



bool CBkgLayerBase::initBkgLayerBase(const char* batchNodeName, const char* backgroundTmxName, const char* tileTmxName)
{
    do
    {
        m_layer = dynamic_cast<Layer*>(this);
        CC_ASSERT(m_layer);
        
        setBatchNode(CBatchNodeManager::create());
        BREAK_IF_FAILED(m_batchNode);
        BREAK_IF_FAILED(m_batchNode->loadBatchNodeInitData(batchNodeName));
        
        setBkgGrd(CBackgroundManager::create());
        BREAK_IF_FAILED(m_bkgGrd);
        m_bkgGrd->changeMap(backgroundTmxName, tileTmxName);
        
        m_bkgGrd->attachBackgroundTo(m_layer);
        m_batchNode->attachToParent(m_bkgGrd, 0);
        
        
        m_pathFinder = new CPathFinderManager;
        m_pathFinder->setBkg(m_bkgGrd);
        
        m_tapStartPoint = INVALIDE_TAP_POS;
        m_scaleCenterGridPos = INVALIDE_TAP_POS;

        return true;
    } while (false);
    
    return false;
}



void CBkgLayerBase::bkgLayerBaseTouchesBegan(const std::vector<Touch*>& touches, Event* event)
{
    std::vector<Touch*>::const_iterator it;
    
    for( it = touches.begin(); it != touches.end(); it++)
    {
        Touch* tch = (Touch*)*it;
        std::vector<Touch*>::iterator it_ = find(m_touches.begin(), m_touches.end(), tch);
        if (it_ == m_touches.end())
        {
            CC_SAFE_RETAIN(tch);
            m_touches.push_back(tch);
        }
    }
}



void CBkgLayerBase::bkgLayerBaseTouchesMoved(const std::vector<Touch*>& touches, Event* event)
{
    switch (m_touches.size())
    {
        case 1:
        {
            Touch* t1 = touches[0];
            Point point1 = Director::getInstance()->convertToUI(t1->getLocationInView());
            Point location1 = m_layer->convertToNodeSpace(point1);

            if (!m_tapStartPoint.equals(INVALIDE_TAP_POS))
            {
                Point offset = location1 -  m_tapStartPoint;
                m_bkgGrd->moveMap(offset);
            }
            m_tapStartPoint = location1;

            break;
        }

        case 2:
        {
            Touch* t1 = m_touches[0];
            Touch* t2 = m_touches[1];
            
            Point point1 = Director::getInstance()->convertToUI(t1->getLocationInView());
            Point location1 = m_layer->convertToNodeSpace(point1);
            
            Point point2 = Director::getInstance()->convertToUI(t2->getLocationInView());
            Point location2 = m_layer->convertToNodeSpace(point2);
            
            
            if (m_scaleCenterGridPos.equals(INVALIDE_TAP_POS))
            {
                m_lastLength = (location2 - location1).getLengthSq();
                Point center = Point(Director::getInstance()->getWinSize());
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



void CBkgLayerBase::bkgLayerBaseTouchesEnded(const std::vector<Touch*>& touches, Event* event)
{
    m_tapStartPoint = INVALIDE_TAP_POS;
    m_scaleCenterGridPos = INVALIDE_TAP_POS;
    
    std::vector<Touch*>::const_iterator it;
    
    for( it = touches.begin(); it != touches.end(); it++)
    {
        Touch* tch = (Touch*)*it;

        std::vector<Touch*>::iterator it_ = find(m_touches.begin(), m_touches.end(), tch);
        
        if (it_ != m_touches.end())
        {
            m_touches.erase(it_);
        }
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
