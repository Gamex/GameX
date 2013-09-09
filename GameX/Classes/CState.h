//
//  CState.h
//  TheForce
//
//  Created by 马 俊 on 13-1-24.
//
//

#ifndef __TheForce__TFStateBase__
#define __TheForce__TFStateBase__

#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class CComponent;
class CComponentParameter;

class CState
{
public:
	CState();
	virtual ~CState();
	
	virtual string getCurrentState() const;
	virtual bool changeState(const string& state, CComponentParameter* parameter = NULL, bool force = false);
    virtual void lockState();
    virtual void unlockState();

    virtual void updateComponents(float dt);
    virtual void addComponentForState(const string& state, CComponent* component);
    virtual void removeState(const string& state);
    virtual void removeComponentFromState(const string& state, CComponent* component);
    virtual void setComponentParameter(CComponentParameter* pamaremter);
    
protected:
	virtual void onEnterState(const string& s);
	virtual void onLeaveState(const string& s);
	virtual void clearState();
private:
    typedef set<CComponent*> SC;
    typedef set<CComponent*>::iterator SC_IT;
    typedef set<CComponent*>::const_iterator SC_CIT;
    
    typedef map<string, SC> MSC;
    typedef map<string, SC>::iterator MSC_IT;
    typedef map<string, SC>::const_iterator MSC_CIT;
    
    MSC components_;
    string currentState_;
    bool isStateLocked_;
};

#endif /* defined(__TheForce__TFStateBase__) */
