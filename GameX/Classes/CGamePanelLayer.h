//
//  CGamePanelLayer.h
//  GameX
//
//  Created by 马 俊 on 13-6-12.
//
//

#ifndef __GameX__CGamePanelLayer__
#define __GameX__CGamePanelLayer__

#include "CBaseLayer.h"

class CGamePanelLayer : public CBaseLayer
{
public:
    CREATE_FUNC(CGamePanelLayer);
    
    CGamePanelLayer();
    virtual ~CGamePanelLayer();
    
    virtual bool init();
    
    virtual void popMenu();
protected:
    virtual void onBuild(CCObject* sender, CCControlEvent event);
    virtual void onBuild2(CCObject* sender, CCControlEvent event);
private:
};

#endif /* defined(__GameX__CGamePanelLayer__) */
