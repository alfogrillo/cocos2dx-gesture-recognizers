#include "PanScene.h"
#include "Gestures/GestureRecognizerUtils.h"


Scene* PanScene::createScene()
{
    auto scene = Scene::create();
    auto layer = PanScene::create();
    scene->addChild(layer);
    return scene;
}

bool PanScene::init()
{
    if ( LayerColor::initWithColor(Color4B::GRAY) )
    {
        visibleSize = Director::getInstance()->getVisibleSize();
        
        addSprite();
        addLabel();
        addGestureRecognizers();
        
        auto backButt = Button::create("back.png");
        backButt->setPosition({visibleSize.width * 0.9f, visibleSize.height * 0.08f});
        backButt->addTouchEventListener(CC_CALLBACK_2(PanScene::goBack, this));
        addChild(backButt);
        return true;
    }
    else
        return false;
}

void PanScene::addSprite()
{
    sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(visibleSize * 0.5f);
    addChild(sprite);
}

void PanScene::addGestureRecognizers()
{
    float fingers = 3;
    auto pan = PanGestureRecognizer::create(fingers);
    pan->onPan = CC_CALLBACK_1(PanScene::onPan, this);
    addChild(pan);
}

void PanScene::addLabel()
{
    label = Label::createWithTTF("Drag three fingers", "fonts/Marker Felt.ttf", 60);
    label->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.90f});
    label->setHorizontalAlignment(TextHAlignment::CENTER);
    addChild(label);
}

void PanScene::onPan(PanGestureRecognizer *recognizer)
{
    auto stato = recognizer->getStatus();
    auto location = recognizer->getGestureLocation();
    
    if (stato == GestureStatus::CHANGED)
    {
        if (sprite)
            sprite->setPosition(sprite->getPosition() + recognizer->getTraslation());
    }
}

void PanScene::goBack(Ref* sender, Widget::TouchEventType type)
{
    if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
    {
        Director::getInstance()->popScene();
    }
}