//
//  CState.h
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#ifndef __TheForce__TFStateBase__
#define __TheForce__TFStateBase__


#define STATE_NONE          -1

class CState
{
public:
	CState();
	virtual ~CState();
	
	virtual int getCurrentState() const;
	virtual bool changeState(int state);
    virtual void lockState();
    virtual void unlockState();
    
protected:
	virtual void onEnterState(int state);
	virtual void onLeaveState(int state);
	virtual void clearState();
private:
    int m_currentState;
    int m_nextState;
    bool m_isStateLocked;
};

#endif /* defined(__TheForce__TFStateBase__) */
