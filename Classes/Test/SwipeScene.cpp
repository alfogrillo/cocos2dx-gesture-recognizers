#include "SwipeScene.h"
#include "Gestures/GestureRecognizerUtils.h"


Scene* SwipeScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SwipeScene::create();
    scene->addChild(layer);
    return scene;
}

bool SwipeScene::init()
{
    if ( LayerColor::initWithColor(Color4B::GRAY) )
    {
        visibleSize = Director::getInstance()->getVisibleSize();
        
        addSprite();
        addLabel();
        addGestureRecognizers();
        
        auto backButt = Button::create("back.png");
        backButt->setPosition({visibleSize.width * 0.9f, visibleSize.height * 0.08f});
        backButt->addTouchEventListener(CC_CALLBACK_2(SwipeScene::goBack, this));
        addChild(backButt);
        return true;
    }
    else
        return false;
}

void SwipeScene::addSprite()
{
    sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize * 0.5f);
    addChild(sprite);
}

void SwipeScene::addGestureRecognizers()
{
    auto swipe = SwipeGestureRecognizer::create();
    swipe->onSwipe = CC_CALLBACK_1(SwipeScene::onSwipe, this);
    addChild(swipe);
    
    float timeout = 0.6f;
    float fingerNumber = 1;
    auto lpress = LongPressGestureRecognizer::create(timeout, fingerNumber);
    lpress->onLongPress = CC_CALLBACK_1(SwipeScene::onLongPress, this);
    addChild(lpress);
}

void SwipeScene::addLabel()
{
    label = Label::createWithTTF("Swipe or touch and\n hold on the sprite", "fonts/Marker Felt.ttf", 60);
    label->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.90f});
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    addChild(label);
}

void SwipeScene::onLongPress(LongPressGestureRecognizer *recognizer)
{
    auto stato = recognizer->getStatus();
    auto location = recognizer->getGestureLocation();
    
    if (stato == GestureStatus::RECOGNIZED)
    {
        if (sprite and nodeContainsThePoint(sprite, location))
        {
                
            Device::vibrate(0.5f);
            if (sprite->getColor() == Color3B::WHITE)
                sprite->runAction(TintTo::create(0.5f, Color3B::YELLOW));
            else
                sprite->runAction(TintTo::create(0.5f, Color3B::WHITE));
            
            if (label)
                label->setString("Long Press Detected");
            
            return;
        }
            
    }
}

void SwipeScene::onSwipe(SwipeGestureRecognizer* recognizer)
{
    auto stato = recognizer->getStatus();
    
    if (stato == GestureStatus::RECOGNIZED)
    {
        auto direction = recognizer->getSwipeDirection();
        MoveBy* move {nullptr};
        string text;
        switch (direction)
        {
            case SwipeGestureRecognizer::SwipeStatus::SWIPE_UP:
                move = MoveBy::create(1.0, {0, 200});
                text = "Swipe up";
                break;
                
            case SwipeGestureRecognizer::SwipeStatus::SWIPE_RIGHT:
                move = MoveBy::create(1.0, {200, 0});
                text = "Swipe right";
                break;
                
            case SwipeGestureRecognizer::SwipeStatus::SWIPE_DOWN:
                move = MoveBy::create(1.0, {0, -200});
                text = "Swipe down";
                break;
                
            case SwipeGestureRecognizer::SwipeStatus::SWIPE_LEFT:
                move = MoveBy::create(1.0, {-200, 0});
                text = "Swipe left";
                break;
            
            default:
                break;
        }
        
        if (sprite and move)
            sprite->runAction(move);
        
        if (label)
            label->setString(text);
    }
}

void SwipeScene::goBack(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}