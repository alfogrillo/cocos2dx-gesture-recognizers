#pragma once

#include "EnableScrollViewTest.h"

#ifdef COCOS2D_3_11

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

class ScrollViewScene : public LayerColor
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ScrollViewScene);
    
private:
    Size visibleSize;
    void addScrollView();
    
    void goBack(Ref* sender, Widget::TouchEventType type);
};

#endif