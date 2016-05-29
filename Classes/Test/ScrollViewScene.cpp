#include "ScrollViewScene.h"

#ifdef COCOS2D_3_11
#include "Gestures/GestureRecognizerUtils.h"
#include "ScrollViewCustom.h"


Scene* ScrollViewScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ScrollViewScene::create();
    scene->addChild(layer);
    return scene;
}

bool ScrollViewScene::init()
{
    if ( LayerColor::initWithColor(Color4B::BLACK) )
    {
        visibleSize = Director::getInstance()->getVisibleSize();
        
        addScrollView();
        
        auto backButt = Button::create("back.png");
        backButt->setPosition({visibleSize.width * 0.9f, visibleSize.height * 0.08f});
        backButt->addTouchEventListener(CC_CALLBACK_2(ScrollViewScene::goBack, this));
        addChild(backButt);
        return true;
    }
    else
        return false;
}

void ScrollViewScene::addScrollView()
{
    auto sv = ScrollViewCustom::create();
    sv->setContentSize(visibleSize);
    sv->setInnerContainerSize(visibleSize);
    sv->setTwoFingerPanEnabled(true);
    sv->setTapToHomeEnabled(true);
    sv->setAnchorPoint(Vec2::ZERO);
    sv->setDirection(cocos2d::ui::ScrollView::Direction::BOTH);
    addChild(sv);
    
    auto sprite = Sprite::create("image.png");
    sprite->setNormalizedPosition({0.5f, 0.5f});
    //sv->setInnerContainerSize(sprite->getContentSize());
    sv->addChild(sprite);
}

void ScrollViewScene::goBack(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}

#endif