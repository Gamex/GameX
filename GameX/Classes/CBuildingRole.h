//
//  CBuildingRole.h
//  GameX
//
//  Created by 马 俊 on 13-12-11.
//
//

#ifndef __GameX__CBuildingRole__
#define __GameX__CBuildingRole__

#include "CRole.h"
#include "CHPBar.h"
#include "ICCBAnimationDelegate.h"



class CBuildingRole
: public CRole
{
public:
    FACTORY_CREATE_FUNC(CBuildingRole);
    
    virtual ~CBuildingRole();
    virtual bool init(const string& unitId, bool editorMode = false);
    
    virtual void update(float dt);
    
    virtual SEL_CallFuncN onResolveCCBCCCallFuncSelector(Object * pTarget, const char* pSelectorName);

    virtual void addComponentsForStates() override;
    
    virtual bool playAnimation(const std::string& name) override;
protected:

    
private:
    
};

#endif /* defined(__GameX__CBuildingRole__) */
