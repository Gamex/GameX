//
//  CMoveOnGridComp.cpp
//  GameX
//
//  Created by 马 俊 on 13-9-15.
//
//

#include "CMoveOnGridComp.h"
#include "CRole.h"
#include "CBackgroundManager.h"
#include "CPathFinderManager.h"


CMoveOnGridComp::CMoveOnGridComp(void)
: m_ownerRole(NULL)
, m_subState(SUB_STATE_IDLE)
, m_moveElapseTime(0.f)
, m_moveTotalTime(0.f)
{
    m_strName = "MoveOnGridComp";
}



bool CMoveOnGridComp::init()
{
	return true;
}



void CMoveOnGridComp::onEnter()
{
    m_ownerRole = dynamic_cast<CRole*>(getOwner());
    CC_ASSERT(m_ownerRole);
}



void CMoveOnGridComp::onExit()
{
}



void CMoveOnGridComp::update(float dt)
{
    switch (m_subState)
    {
        case SUB_STATE_IDLE:
            findPathIfNeeded();
            break;
        case SUB_STATE_PATH_FINDING:
            break;
        case SUB_STATE_PATH_FOUND:
        {
            if (m_paths.size() > 0)
            {
                CBackgroundManager* bkg = m_ownerRole->getBackGround();
                CC_ASSERT(bkg);
                const CCPoint& pos = m_paths.back();           
                if (bkg->isRoleCanBePlacedOnPos(m_ownerRole, pos))
                {
                    
                    CLogicGrid* pGrid = m_ownerRole->getLogicGrid();
                    const CCPoint& curPos = pGrid->getGridPos();

                    float speed = 3.f;
                    m_moveTotalTime = pos.getDistance(curPos) / speed;
                    m_moveElapseTime = 0.f;
                    m_moveFrom = bkg->gridToWorldPoint(curPos);
                    m_moveTo = bkg->gridToWorldPoint(pos);
                    
                    CCPoint diff = m_moveTo - m_moveFrom;
                    if (diff.x > 0)
                    {
                        if (diff.y > 0)
                        {
                            m_ownerRole->setFaceTo(FACE_TO_RIGHT_UP);
                        }
                        else
                        {
                            m_ownerRole->setFaceTo(FACE_TO_RIGHT_DOWN);
                        }
                    }
                    else if (diff.x < 0)
                    {
                        if (diff.y > 0)
                        {
                            m_ownerRole->setFaceTo(FACE_TO_LEFT_UP);
                        }
                        else
                        {
                            m_ownerRole->setFaceTo(FACE_TO_LEFT_DOWN);
                        }
                    }
                    m_ownerRole->playAnimation(ROLE_ANIMATION_MOVE);
                    m_ownerRole->lockState();
                    
                    m_subState = SUB_STATE_MOVING;
                }
                else
                {
                    m_subState = SUB_STATE_IDLE;
                }
            }
            else
            {
                m_subState = SUB_STATE_IDLE;
                m_ownerRole->playAnimation(ROLE_ANIMATION_IDLE);
            }
            break;
        }
        case SUB_STATE_MOVING:
        {
            m_moveElapseTime += dt;
            float alpha = m_moveElapseTime / m_moveTotalTime;
            if (FLT_GE(alpha, 1.f))
            {
                CBackgroundManager* bkg = m_ownerRole->getBackGround();
                CC_ASSERT(bkg);
                alpha = 1.f;
                bkg->placeRole(m_ownerRole, m_paths.back());
                m_paths.pop_back();
                m_subState = SUB_STATE_PATH_FOUND;
            }
            CCPoint newPos = m_moveFrom.lerp(m_moveTo, m_moveElapseTime / m_moveTotalTime);

            m_ownerRole->setSpritePosition(newPos);
            break;
        }
        default:
            break;
    }
}



void CMoveOnGridComp::onPathReady(const vector<CCPoint>& path)
{
    if (path.size() > 0)
    {
        m_paths = path;
        m_subState = SUB_STATE_PATH_FOUND;
        
        CBackgroundManager* bkg = m_ownerRole->getBackGround();
        CC_ASSERT(bkg);
        bkg->clearAllHightlightGrids();
        vector<CCPoint>::reverse_iterator it = m_paths.rbegin();
        for (; it != m_paths.rend(); ++it)
        {
            bkg->hightlightGrid(*it);
        }
        m_paths.pop_back();
    }
    else
    {
        m_ownerRole->setMoveTarget(m_ownerRole->getLogicGrid()->getGridPos());
        m_subState = SUB_STATE_IDLE;
    }
}



void CMoveOnGridComp::findPathIfNeeded()
{
    const CCPoint& targetPos = m_ownerRole->getMovetarget();
    CLogicGrid* pGrid = m_ownerRole->getLogicGrid();
    const CCPoint& curPos = pGrid->getGridPos();
    
    if (!curPos.equals(targetPos))
    {
        m_ownerRole->findPath(curPos, targetPos, this);
        m_subState = SUB_STATE_PATH_FINDING;
    }
}


