//
//  CTimeProfile.h
//  GameX
//
//  Created by 马 俊 on 13-10-22.
//
//

#ifndef __GameX__CTimeProfile__
#define __GameX__CTimeProfile__

#include "Common.h"
#include "CSingleton.h"

#define ENABLE_TP       0

#if ENABLE_TP

class CTimeProfile
: public CSingleton<CTimeProfile>
{
public:
    bool init();
    bool begin(int identifier = 0);
    bool log(const char* s, int identifier = 0);
    bool commit(float threld = 0.f);
    float getTime(int identifier = 0);
    
    bool flush();

    CTimeProfile();
    virtual ~CTimeProfile();
    
protected:
    Dictionary* m_log;
    Dictionary* m_tempLog;
    
    MIT m_beginLogTimes;
    MIT m_lastLogTimes;
};

#define TIME_PROFILE        (CTimeProfile::getInstance())
#define TP_INIT()           (TIME_PROFILE->init());
#define TP_LOG_BEGIN(__ID__)         (TIME_PROFILE->begin(__ID__));
#define TP_LOG(__S__, __ID__)           (TIME_PROFILE->log(__S__, __ID__));
#define TP_LOG_COMMIT(__T__)    (TIME_PROFILE->commit(__T__));
#define TP_LOG_FLUSH()          (TIME_PROFILE->flush());


#else


#define TIME_PROFILE
#define TP_INIT()
#define TP_LOG_BEGIN(__ID__)
#define TP_LOG(__S__, __ID__)
#define TP_LOG_COMMIT(__T__)
#define TP_LOG_FLUSH()

#endif

#endif /* defined(__GameX__CTimeProfile__) */
