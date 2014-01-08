//
//  CSpriteEx.cpp
//  GameX
//
//  Created by 马 俊 on 13-12-21.
//
//

#include "CSpriteEx.h"


static class CSpriteExRegister
{
public:
    CSpriteExRegister()
    {
        NodeLoaderLibrary::getInstance()->registerNodeLoader( "CSpriteEx", CSpriteExLoader::loader());
    }
} __reg;


CSpriteEx::CSpriteEx()
{
    InputDelegate::setTouchEnabled(true);
}



void CSpriteEx::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    Point pt = touches[0]->getLocation();
    CCLOG("%f, %f", pt.x, pt.y);
}



void CSpriteEx::onTouchesMoved(const std::vector<Touch*>& touches, Event *event)
{
}



void CSpriteEx::onTouchesEnded(const std::vector<Touch*>& touches, Event *event)
{
}




