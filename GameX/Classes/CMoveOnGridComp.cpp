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
                const CCPoint& pos = m_paths.back();
                CLogicGrid* pTargetGrid = BKG_MANAGER->getGrid(pos);
                CLogicGrid* pGrid = m_ownerRole->getGrid();
                if (pTargetGrid->getGroundUnit())
                {
                    m_subState = SUB_STATE_IDLE;
                }
                else
                {
                    const CCPoint& curPos = pGrid->getGridPos();
                    CCPoint diff = pos - curPos;
                    CC_ASSERT(fabs(diff.x) <= 1 && fabs(diff.y) <= 1 && !curPos.equals(pos));
                    
                    if (diff.x > 0)
                    {
                        m_ownerRole->setFaceTo(FACE_TO_RIGHT);
                    }
                    else if (diff.x < 0)
                    {
                        m_ownerRole->setFaceTo(FACE_TO_LEFT);
                    }
                    m_ownerRole->playAnimation(ROLE_ANIMATION_MOVE);
                    m_ownerRole->lockState();
                    
                    float speed = 3.f;
                    m_moveTotalTime = pos.getDistance(curPos) / speed;
                    m_moveElapseTime = 0.f;
                    m_moveFrom = BKG_MANAGER->gridToPoint(curPos);
                    m_moveTo = BKG_MANAGER->gridToPoint(pos);
                    
                    m_subState = SUB_STATE_MOVING;
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
                alpha = 1.f;
                m_ownerRole->placeOnGridPos(m_paths.back(), false);
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
        m_paths.pop_back();
    }
    else
    {
        m_ownerRole->setMoveTarget(m_ownerRole->getGrid()->getGridPos());
        m_subState = SUB_STATE_IDLE;
    }
}



void CMoveOnGridComp::findPathIfNeeded()
{
    const CCPoint& targetPos = m_ownerRole->getMovetarget();
    CLogicGrid* pGrid = m_ownerRole->getGrid();
    const CCPoint& curPos = pGrid->getGridPos();
    
    if (!curPos.equals(targetPos))
    {
        PATH_FINDER->findPath(curPos, targetPos, this);
        m_subState = SUB_STATE_PATH_FINDING;
    }
}


