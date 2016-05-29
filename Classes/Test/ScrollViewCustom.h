#pragma once

#include "EnableScrollViewTest.h"

#ifdef COCOS2D_3_11

using namespace std;

#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace cocos2d::ui;

#include "Gestures/PinchGestureRecognizer.h"
#include "Gestures/TapGestureRecognizer.h"
#include "Gestures/PanGestureRecognizer.h"

#define SCROLL_VIEW_CUSTOM_SCALE_TO_TIME 0.5f
#define SCROLL_VIEW_CUSTOM_MIN_ZOOM 1.0
#define SCROLL_VIEW_CUSTOM_MAX_ZOOM 3.0

#define SAFE_REMOVE_FROM_PARENT(p) do {if(p) (p)->removeFromParent();} while(0)
#define SAFE_REMOVE_FROM_PARENT_NULL(p) do {if(p) (p)->removeFromParent(); (p) = nullptr;} while(0)

#define isScaleAllowed(newScale) ((newScale) >= SCROLL_VIEW_CUSTOM_MIN_ZOOM and (newScale) <= SCROLL_VIEW_CUSTOM_MAX_ZOOM)

class ScrollViewCustom : public cocos2d::ui::ScrollView
{
public:
    CREATE_FUNC(ScrollViewCustom);
    
    /**
     * 
     * @return Zoom factor
     */
    float getContentScale();
    
    /**
     * Set Zoom factor
     * @param s
     */
    void setContentScale(float s);

    void addChild(Node* child) override;
        
    // NB: ScrollView::setInnerContainerSize is NOT virtual!!
    virtual void setInnerContainerSize(const Size& size);
    
    virtual void setTwoFingerPanEnabled(bool enabled);
    virtual void setTapToHomeEnabled(bool enabled);

protected:
    bool init() override;
    void doLayout() override;
 
private:
    Size originalContainerSize;
    bool twoFingersPanEnabled {false};
    Node* baseNode {nullptr};
    PinchGestureRecognizer* pinchRecognizer {nullptr};
    TapGestureRecognizer*   tapRecognizer   {nullptr};
    
    void privateSetInnerContainerSize(const Size& size);
    
    void addPinchGestureRecognizer();
    void addTapGestureRecognizer();
    
    // Event handler
    void onPinch(PinchGestureRecognizer* recognizer);
    void onTap(TapGestureRecognizer* recognizer);
};

#endif