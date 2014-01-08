//
//  CSpriteEx.h
//  GameX
//
//  Created by 马 俊 on 13-12-21.
//
//

#ifndef __GameX__CSpriteEx__
#define __GameX__CSpriteEx__

#include "Common.h"

class CSpriteEx
: public Sprite
, public InputDelegate
{
public:
    CREATE_FUNC(CSpriteEx);
    CSpriteEx();
protected:
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *event) override;
    virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *event) override;
};


class CSpriteExLoader : public SpriteLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CSpriteExLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CSpriteEx);
};

#endif /* defined(__GameX__CSpriteEx__) */
