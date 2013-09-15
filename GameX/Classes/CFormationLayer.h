//
//  CFormationLayer.h
//  GameX
//
//  Created by 马 俊 on 13-8-28.
//
//

#ifndef __GameX__CFormationLayer__
#define __GameX__CFormationLayer__

#include "CTouchesLayer.h"
#include "CFormationPanelLayer.h"
#include "CBackgroundManager.h"

class CFormationLayer
: public CTouchesLayer
, public IFormationLayerDelegate
{
public:
    CREATE_FUNC(CFormationLayer);
    
    CFormationLayer();
    virtual ~CFormationLayer();
    
    virtual bool init();

    virtual void update(float dt);
protected:
    virtual void touchBegan(CCPoint position);
    virtual void touchMoved(CCPoint position);
    virtual void touchEnded(CCPoint position);
    
    virtual void onFrameSel(const string& objName);
    virtual void onSave(class CFormation* fmt);
    virtual void onLoad(class CFormation* fmt);
    
    virtual void clearFormation();
    void clearAll();
private:
    CCNode* m_roleNode;
    CFormationPanelLayer* m_panel;
    class CRole* m_curSelRole;
    
    CGridPos m_curSelGrid;
};


#endif /* defined(__GameX__CFormationLayer__) */
