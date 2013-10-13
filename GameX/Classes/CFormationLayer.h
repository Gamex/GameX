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
#include "CBkgLayerBase.h"

class CFormationLayer
: public CTouchesLayer
, public IFormationLayerDelegate
, public CBkgLayerBase
{
public:
    CREATE_FUNC(CFormationLayer);
    
    CFormationLayer();
    virtual ~CFormationLayer();
    
    virtual bool init();

    virtual void update(float dt);
protected:
    virtual void touchesBegan(CCSet* touches, CCEvent* event);
    virtual void touchesMoved(CCSet* touches, CCEvent* event);
    virtual void touchesEnded(CCSet* touches, CCEvent* event);
    
    virtual void onFrameSel(const std::string& unitName);
    virtual void onSave(class CFormation* fmt);
    virtual void onLoad(class CFormation* fmt);
    
    virtual void clearFormation();
    void clearAll();

private:
    CCNode* m_roleNode;
    CFormationPanelLayer* m_panel;
    class CRole* m_curSelRole;
    
    CCPoint m_curSelGrid;

};


#endif /* defined(__GameX__CFormationLayer__) */
