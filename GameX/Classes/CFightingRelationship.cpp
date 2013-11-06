//
//  CFightingRelationship.cpp
//  GameX
//
//  Created by 马 俊 on 13-7-24.
//
//

#include "Common.h"
#include "CFightingRelationship.h"

IMPLEMENT_SINGLETON(CFightingRelationship);


CFightingRelationship::CFightingRelationship()
{
    
}



CFightingRelationship::~CFightingRelationship()
{
    
}



void CFightingRelationship::update(float dt)
{
//    CCLOG("villain count: %d", m_villains.size());
//    CCLOG("victim count: %d", m_victims.size());
//    CCLOG("---------------------------");
}


void CFightingRelationship::add(IFightingRelation* villain, IFightingRelation* victim)
{
    CC_ASSERT(villain);
    CC_ASSERT(victim);
    
//    IFightingRelation::_FIGHTING_RELATION_TYPE villainType = villain->getRelationType();
//    IFightingRelation::_FIGHTING_RELATION_TYPE victimType = victim->getRelationType();
//    
//    MRVR_IT villain_it = m_villains.find(villain);
//    MRVR_IT victim_it = m_victims.find(victim);
    
//    switch (villainType)
//    {
//        case IFightingRelation::RELATION_1v1:
//        {
//            switch (victimType)
//            {
//                case IFightingRelation::RELATION_1v1:
//                    if (villain_it != m_villains.end() || victim_it != m_victims.end())
//                    {
//                        return;
//                    }
//                    break;
//                case IFightingRelation::RELATION_1vN:
//                    return;
//                    break;
//                case IFightingRelation::RELATION_Nv1:
//                    return;
//                    break;
//            }
//            break;
//        }
//        case IFightingRelation::RELATION_1vN:
//        {
//            switch (victimType)
//            {
//                case IFightingRelation::RELATION_1v1:
//                    return;
//                    break;
//                case IFightingRelation::RELATION_1vN:
//                    return;
//                    break;
//                case IFightingRelation::RELATION_Nv1:
//                    return;
//                    break;
//            }
//            break;
//        }
//        case IFightingRelation::RELATION_Nv1:
//        {
//            switch (victimType)
//            {
//                case IFightingRelation::RELATION_1v1:
//                    return;
//                    break;
//                case IFightingRelation::RELATION_1vN:
//                    return;
//                    break;
//                case IFightingRelation::RELATION_Nv1:
//                    return;
//                    break;
//            }
//            break;
//        }
//    }
    
    m_victims[victim].push_back(villain);
    m_villains[villain].push_back(victim);
}




void CFightingRelationship::removeAllRelation(IFightingRelation* role)
{
    removeAllVictims(role);
    removeAllVillains(role);
}



void CFightingRelationship::removeAllVictims(IFightingRelation* role)
{
    MRVR_IT it = m_victims.find(role);
    if (it != m_victims.end())
    {
        VR& vr = (*it).second;
        VR_IT vr_it = vr.begin();
        for (; vr_it != vr.end(); ++vr_it)
        {
            removeObjFrom(m_villains, *vr_it, role);
        }
        m_victims.erase(it);
    }
}



void CFightingRelationship::removeAllVillains(IFightingRelation* role)
{
    MRVR_IT it = m_villains.find(role);
    if (it != m_villains.end())
    {
        VR& vr = (*it).second;
        VR_IT vr_it = vr.begin();
        for (; vr_it != vr.end(); ++vr_it)
        {
            removeObjFrom(m_victims, *vr_it, role);
        }
        m_villains.erase(it);
    }
}



IFightingRelation* CFightingRelationship::getFirstVillain(IFightingRelation* role)
{
    IFightingRelation* ret = NULL;
    MRVR_IT it = m_victims.find(role);
    if (it != m_victims.end())
    {
        VR& vr = (*it).second;
        if (vr.size() > 0)
        {
            VR_IT vr_it = vr.begin();
            ret = *vr_it;
            ret->m_fightingRelationIterator = vr_it;
        }
    }
    
    return ret;
}



IFightingRelation* CFightingRelationship::getNextVillain(IFightingRelation* role, IFightingRelation* preVictim)
{
    IFightingRelation* ret = NULL;
    MRVR_IT it = m_victims.find(role);
    if (it != m_victims.end())
    {
        VR& vr = (*it).second;
        if (vr.size() > 0)
        {
            VR_IT vr_it = preVictim->m_fightingRelationIterator;
            vr_it++;
            if (vr_it != vr.end())
            {
                ret = *vr_it;
                ret->m_fightingRelationIterator = vr_it;
            }
        }
    }
    
    return ret;
}



IFightingRelation* CFightingRelationship::getFirstVictim(IFightingRelation* role)
{
    IFightingRelation* ret = NULL;
    MRVR_IT it = m_villains.find(role);
    if (it != m_villains.end())
    {
        VR& vr = (*it).second;
        if (vr.size() > 0)
        {
            VR_IT vr_it = vr.begin();
            ret = *vr_it;
            ret->m_fightingRelationIterator = vr_it;
        }
    }
    
    return ret;
}



IFightingRelation* CFightingRelationship::getNextVictim(IFightingRelation* role, IFightingRelation* preVillain)
{
    IFightingRelation* ret = NULL;
    MRVR_IT it = m_villains.find(role);
    if (it != m_villains.end())
    {
        VR& vr = (*it).second;
        if (vr.size() > 0)
        {
            VR_IT vr_it = preVillain->m_fightingRelationIterator;
            vr_it++;
            if (vr_it != vr.end())
            {
                ret = *vr_it;
                ret->m_fightingRelationIterator = vr_it;
            }
        }
    }
    
    return ret;
}



void CFightingRelationship::removeObjFrom(MRVR& mrvr, IFightingRelation* key, IFightingRelation* toBeDel)
{
    MRVR_IT it = mrvr.find(key);
    if (it != mrvr.end())
    {
        VR& vr = (*it).second;
        VR_IT vr_it = find(vr.begin(), vr.end(), toBeDel);
        if (vr_it != vr.end())
        {
            vr.erase(vr_it);
        }
        if (vr.size() == 0)
        {
            mrvr.erase(it);
        }
    }
}
