#pragma once

#include <cocos2d.h>
#include <ui/CocosGUI.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class MainScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);
    
private:
    Size visibleSize {Director::getInstance()->getVisibleSize()};
};

