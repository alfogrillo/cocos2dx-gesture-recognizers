#include "MainScene.h"
#include "ScrollableMenu.h"
#include "PinchScene.h"
#include "PanScene.h"
#include "SwipeScene.h"
#include "ChildScene.h"
#include "ScrollViewScene.h"
#include "EnableScrollViewTest.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto m = ScrollableMenu::create();
    m->setTitle("Select a test");
    m->addMenuEntry<PinchScene>("Pinch, Double tap");
    m->addMenuEntry<SwipeScene>("Swipe, Long Press");
    m->addMenuEntry<PanScene>("Three fingers Pan");
    m->addMenuEntry<ChildScene>("Recognizer as child");
#ifdef COCOS2D_3_11
    m->addMenuEntry<ScrollViewScene>("Custom Scroll View");
#endif
    addChild(m);
    return true;
}
