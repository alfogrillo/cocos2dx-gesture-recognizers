#include "PinchScene.h"
#include "Gestures/GestureRecognizerUtils.h"


Scene* PinchScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PinchScene::create();
    scene->addChild(layer);
    return scene;
}

bool PinchScene::init()
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
        backButt->addTouchEventListener(CC_CALLBACK_2(PinchScene::goBack, this));
        addChild(backButt);
        return true;
    }
    else
        return false;
}

void PinchScene::addSprite()
{
    sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize * 0.5f);
    addChild(sprite);
}

void PinchScene::addDebugButton() 
{
    debugButton = Button::create();
    debugButton->setAnchorPoint({0, 0.5f});
    debugButton->setTitleFontName("fonts/Marker Felt.ttf");
    debugButton->setTitleFontSize(50);
    debugButton->setTitleText("Pinch debug: OFF");
    debugButton->setPositionX(20);
    debugButton->setPositionY(visibleSize.height * 0.08f);
    debugButton->addTouchEventListener(CC_CALLBACK_2(PinchScene::onDebugPressed, this));
    addChild(debugButton);
}


void PinchScene::addGestureRecognizers()
{    
    auto pinch  = PinchGestureRecognizer::create();
    pinch->onPinch = CC_CALLBACK_1(PinchScene::onPinch, this);
    addChild(pinch, 0, PINCH_RECONIZER_NAME);
    
    uint fingerCount = 1;
    uint tapNumber   = 2;
    auto tap = TapGestureRecognizer::create(fingerCount, tapNumber);
    tap->onTap = CC_CALLBACK_1(PinchScene::onTap, this);
    addChild(tap);
}

void PinchScene::addLabel()
{
    label = Label::createWithTTF("Pinch the sprite or\ndouble tap anywhere", "fonts/Marker Felt.ttf", 60);
    label->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.90f});
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    addChild(label);
}

void PinchScene::onPinch(PinchGestureRecognizer* recognizer)
{
    auto stato = recognizer->getStatus();
    auto location = recognizer->getGestureLocation();
    
    static bool filterTouch {true};
    if (stato == GestureStatus::BEGAN)
    {
        //CCLOG("Pinch Began");
        if (sprite)
            filterTouch = not nodeContainsThePoint(sprite, location);
    }
    else if (stato == GestureStatus::CHANGED)
    {
        auto factor = recognizer->getPinchFactor();
        auto angle  = recognizer->getPinchRotation();
        auto trasl  = recognizer->getPinchTraslation();
        //CCLOG("Pinch factor: %f", factor);
        //CCLOG("Traslation: %f, %f", trasl.x, trasl.y);
        if (sprite and not filterTouch) 
        {
            sprite->setScale   (sprite->getScale()    * factor);
            sprite->setRotation(sprite->getRotation() + angle);
            sprite->setPosition(sprite->getPosition() + trasl);
        }
    }
    else if (stato == GestureStatus::RECOGNIZED)
    {
        filterTouch = true;
        //CCLOG("Pinch End");
    }
}

void PinchScene::onTap(TapGestureRecognizer* recognizer)
{
    auto stato = recognizer->getStatus();
    auto location = recognizer->getGestureLocation();
    
    if (stato == GestureStatus::RECOGNIZED)
    {
        if (sprite)
        {
            float time = 0.8f;
            auto sto = ScaleTo::create(time, 1);
            auto rto = RotateTo::create(time, 0);
            auto mto = MoveTo::create(time, visibleSize * 0.5f);
            sprite->runAction(Spawn::create(sto, rto, mto, NULL));
        }
        
        if (label)
            label->setString("Double tap detected");
    }
}

void PinchScene::goBack(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}

void PinchScene::onDebugPressed(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        auto pinchRecognizer = getChildByName<PinchGestureRecognizer*>(PINCH_RECONIZER_NAME);
        if (pinchRecognizer) 
        {
            if (pinchRecognizer->isDebugModeEnabled())
            {
                pinchRecognizer->setDebugMode(false);
                debugButton->setTitleText("Pinch debug: OFF");
            }
            else
            {
                pinchRecognizer->setDebugMode(true);
                debugButton->setTitleText("Pinch debug: ON");
            }
        }
    }
}