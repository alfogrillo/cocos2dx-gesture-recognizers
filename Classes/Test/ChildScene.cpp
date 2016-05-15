#include "ChildScene.h"
#include "Gestures/GestureRecognizerUtils.h"


Scene* ChildScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ChildScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChildScene::init()
{
    if ( LayerColor::initWithColor(Color4B::GRAY) )
    {
        visibleSize = Director::getInstance()->getVisibleSize();
        
        addSprite();
        addLabel();
        addGestureRecognizers();
        addDebugButton();
        
        auto backButt = Button::create("back.png");
        backButt->setPosition({visibleSize.width * 0.9f, visibleSize.height * 0.08f});
        backButt->addTouchEventListener(CC_CALLBACK_2(ChildScene::goBack, this));
        addChild(backButt);
        return true;
    }
    else
        return false;
}

void ChildScene::addSprite()
{
    sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize * 0.5f);
    addChild(sprite);
    
    auto rotateBy = RotateBy::create(20.0f, 360);
    sprite->runAction(RepeatForever::create(rotateBy));
}

void ChildScene::addDebugButton() 
{
    debugButton = Button::create();
    debugButton->setAnchorPoint({0, 0.5f});
    debugButton->setTitleFontName("fonts/Marker Felt.ttf");
    debugButton->setTitleFontSize(50);
    debugButton->setTitleText("Tap debug: ON");
    debugButton->setPositionX(20);
    debugButton->setPositionY(visibleSize.height * 0.08f);
    debugButton->addTouchEventListener(CC_CALLBACK_2(ChildScene::onDebugPressed, this));
    addChild(debugButton);
}


void ChildScene::addGestureRecognizers()
{
    uint fingerCount = 1;
    uint tapNumber   = 2;
    auto tap = TapGestureRecognizer::create(fingerCount, tapNumber);
    tap->onTap = CC_CALLBACK_1(ChildScene::onTap, this);
    tap->setDebugMode(true);
    sprite->addChild(tap, 0, TAP_RECONIZER_NAME);
}

void ChildScene::addLabel()
{
    label = Label::createWithTTF("Double tap should work\nonly inside the sprite", "fonts/Marker Felt.ttf", 60);
    label->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.90f});
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    addChild(label);
}


void ChildScene::onTap(TapGestureRecognizer* recognizer)
{
    auto stato = recognizer->getStatus();
    auto location = recognizer->getGestureLocation();
    
    if (stato == GestureStatus::RECOGNIZED)
    {
        if (sprite)
        {
            float time = 0.3f;
            auto sto1 = ScaleTo::create(time, 1.2f);
            auto sto2 = ScaleTo::create(time, 1.0f);
            sprite->runAction(Sequence::createWithTwoActions(sto1, sto2));
        }
        
        if (label) {
            label->setString("Double tap detected");
            auto cb  = [this]{label->setString("Make a gesture");};
            auto delay = DelayTime::create(1.0f);
            auto call  = CallFunc::create(cb);
            label->runAction(Sequence::createWithTwoActions(delay, call));
        }
    }
}

void ChildScene::goBack(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}

void ChildScene::onDebugPressed(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto tapRecognizer = sprite->getChildByName<TapGestureRecognizer*>(TAP_RECONIZER_NAME);
        if (tapRecognizer) 
        {
            if (tapRecognizer->isDebugModeEnabled())
            {
                tapRecognizer->setDebugMode(false);
                debugButton->setTitleText("Tap debug: OFF");
            }
            else
            {
                tapRecognizer->setDebugMode(true);
                debugButton->setTitleText("Tap debug: ON");
            }
        }
    }
}