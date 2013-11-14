//
//  CTimeProfile.cpp
//  GameX
//
//  Created by 马 俊 on 13-10-22.
//
//

#include "CTimeProfile.h"

#if ENABLE_TP

#define LOG_FILE_NAME       "log.plist"


IMPLEMENT_SINGLETON(CTimeProfile);


CTimeProfile::CTimeProfile()
{
}



CTimeProfile::~CTimeProfile()
{
    CC_SAFE_RELEASE(m_log);
    CC_SAFE_RELEASE(m_tempLog);
}



bool CTimeProfile::init()
{
    do
    {
        m_log = Dictionary::create();
        CC_SAFE_RETAIN(m_log);
        
        m_tempLog = Dictionary::create();
        CC_SAFE_RETAIN(m_tempLog);
        
        timeval& t1 = m_beginLogTimes[0];
        timeval& t2 = m_lastLogTimes[0];
        CCTime::gettimeofdayCocos2d(&t1, nullptr);
        t2 = t1;
        
        return true;
    } while (false);
    
	return false;
}


bool CTimeProfile::begin(int identifier)
{
    do
    {
        timeval& t1 = m_beginLogTimes[identifier];
        timeval& t2 = m_lastLogTimes[identifier];
            
        CCTime::gettimeofdayCocos2d(&t1, nullptr);
        t2 = t1;

        return true;
    } while (false);
    
    return false;
}



bool CTimeProfile::log(const char* s, int identifier)
{
    do
    {
        MIT_IT it = m_beginLogTimes.find(identifier);
        BREAK_IF(it == m_lastLogTimes.end());
        timeval& t = (*it).second;
        
        timeval tp;
        CCTime::gettimeofdayCocos2d(&tp, nullptr);
        double diff = CCTime::timersubCocos2d(&t, &tp);
        t = tp;
        String* key = String::createWithFormat("%ld : %d - %f %s", tp.tv_sec, tp.tv_usec, diff, diff > 10 ? "<---" : "");

        m_tempLog->setObject(String::create(s), key->getCString());
        
        return true;
    } while (false);
    
    return false;
}



bool CTimeProfile::commit(float threld)
{
    do
    {
        timeval tp;
        CCTime::gettimeofdayCocos2d(&tp, nullptr);
        
        float t = CCTime::timersubCocos2d(&(m_beginLogTimes[0]), &tp);
        CCLOG("t: %f", t);
        if (t > threld)
        {
            CCDictElement* elem;
            CCDICT_FOREACH(m_tempLog, elem)
            {
                m_log->setObject(elem->getObject(), elem->getStrKey());
            }
        }
        m_tempLog->removeAllObjects();
        return true;
    } while (false);
    
    return false;
}



bool CTimeProfile::flush()
{
    do
    {
        string path = FileUtils::getInstance()->getWritablePath();
        path += LOG_FILE_NAME;
        m_log->writeToFile(path.c_str());
        return true;
    } while (false);
    
    return false;
}


#endif
