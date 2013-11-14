//
//  ICCBAnimationDelegate.h
//  GameX
//
//  Created by 马 俊 on 13-10-22.
//
//

#ifndef GameX_ICCBAnimationDelegate_h
#define GameX_ICCBAnimationDelegate_h

class ICCBAnimationDelegate
{
public:
    virtual void onSkillHit(Node* obj){};
    virtual void onSkillOver(Node* obj){};
    virtual void onDyingOver(Node* obj){};
};

#endif
