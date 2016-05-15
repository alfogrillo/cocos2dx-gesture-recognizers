#pragma once

#include "cocos2d.h"
using namespace cocos2d;

#include <ui/CocosGUI.h>
using namespace cocos2d::ui;

// Gestures
#include "Gestures/GestureRecognizer.h"
#include "Gestures/PinchGestureRecognizer.h"
#include "Gestures/TapGestureRecognizer.h"
#include "Gestures/SwipeGestureRecognizer.h"
#include "Gestures/LongPressGestureRecognizer.h"
#include "Gestures/PanGestureRecognizer.h"

#include <string>
using namespace std;

class SwipeScene : public LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SwipeScene);
    
private:
    void addSprite();
    void addGestureRecognizers();
    void addLabel();
    
    // callbacks
    void onSwipe(SwipeGestureRecognizer* recognizer);
    void onLongPress(LongPressGestureRecognizer* recognizer);
    void goBack(Ref* sender, Widget::TouchEventType type);
    
    Label* label {nullptr};
    Size visibleSize;
    Sprite* sprite {nullptr};
};