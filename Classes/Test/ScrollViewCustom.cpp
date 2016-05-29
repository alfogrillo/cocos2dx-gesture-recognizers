#include "ScrollViewCustom.h"

#ifdef COCOS2D_3_11
bool ScrollViewCustom::init() 
{
    if (cocos2d::ui::ScrollView::init())
    {
        baseNode = Node::create();
        baseNode->setAnchorPoint(Vec2::ZERO);
        ScrollView::addChild(baseNode);
        addPinchGestureRecognizer();
        return true;
    }
    else
        return false;
}

void ScrollViewCustom::addChild(Node* child) 
{
    baseNode->addChild(child);
}

void ScrollViewCustom::setInnerContainerSize(const Size& size) 
{
    //CCLOG("ScrollViewCustom::setInnerContainerSize");
    originalContainerSize = size;
    ScrollView::setInnerContainerSize(size);
}

void ScrollViewCustom::privateSetInnerContainerSize(const Size& size) 
{
    const auto position = getInnerContainerPosition();
    ScrollView::setInnerContainerSize(size);
    setInnerContainerPosition(position);
}

void ScrollViewCustom::setTwoFingerPanEnabled(bool enabled) 
{
    twoFingersPanEnabled = enabled;
    if (twoFingersPanEnabled)
        setTouchEnabled(false);
}

void ScrollViewCustom::setTapToHomeEnabled(bool enabled) 
{
    if (enabled)
    {
        if (not tapRecognizer)
            addTapGestureRecognizer();
    }
    else
    {
        SAFE_REMOVE_FROM_PARENT_NULL(tapRecognizer);
    }
}

void ScrollViewCustom::doLayout()
{
    //CCLOG("ScrollViewCustom::doLayout");
    if (pinchRecognizer) {
        pinchRecognizer->setContentSize(getContentSize()); // recognizer size match wit ScrollView size
        pinchRecognizer->setPosition(-getInnerContainerPosition()); // recognizer need to remain in orignal position!
    }
    
    if (tapRecognizer) {
        tapRecognizer->setContentSize(getContentSize());
        tapRecognizer->setPosition(-getInnerContainerPosition());
    }
    
    if (baseNode)
        baseNode->setContentSize(getContentSize());
    
    ScrollView::doLayout();
}

float ScrollViewCustom::getContentScale() 
{
    if (baseNode)
        return baseNode->getScale();
    else
        return 1.0f;
}

void ScrollViewCustom::setContentScale(float s) 
{
    if ( baseNode and isScaleAllowed(s) ) {
        baseNode->setScale(s);
        privateSetInnerContainerSize(originalContainerSize * s); // inner size match with base node bounding box (considering the scale)
    }
}

void ScrollViewCustom::addPinchGestureRecognizer() 
{
    pinchRecognizer = PinchGestureRecognizer::create();
    //pinchRecognizer->setDebugMode(true);
    pinchRecognizer->onPinch = CC_CALLBACK_1(ScrollViewCustom::onPinch, this);
    ScrollView::addChild(pinchRecognizer);
}

void ScrollViewCustom::addTapGestureRecognizer() 
{
    const auto fingers = 1;
    const auto tapNum  = 2;
    tapRecognizer = TapGestureRecognizer::create(fingers, tapNum);
    tapRecognizer->onTap = CC_CALLBACK_1(ScrollViewCustom::onTap, this);
    ScrollView::addChild(tapRecognizer);
}

#pragma mark - Event handler

void ScrollViewCustom::onPinch(PinchGestureRecognizer* recognizer) 
{
    auto stato = recognizer->getStatus();
    if (stato == GestureStatus::BEGAN)
    {
        if (not twoFingersPanEnabled) // no scroll during the pinch when single scroll finger is enabled
            recognizer->setSwallowTouches(true);
    }
    if (stato == GestureStatus::CHANGED)
    {
        auto f = recognizer->getPinchFactor();
        auto newScale = getContentScale() * f;
                
        if (isScaleAllowed(newScale))
        {
            auto posBefore = getInnerContainer()->convertToNodeSpace(recognizer->getGestureLocation());
            setContentScale(newScale);
            auto posAfter = posBefore * f;
            auto delta = posBefore - posAfter;
            
            if (twoFingersPanEnabled) 
                delta = delta + recognizer->getPinchTraslation();
            
            scrollChildren(delta);
        }
    }
    else if (stato == GestureStatus::RECOGNIZED)
    {
        if (not twoFingersPanEnabled)
            recognizer->setSwallowTouches(false);
        
        // Fix to hide scroll bar after a pinch
        Touch touch;
        auto point = recognizer->getGestureLocation();
        touch.setTouchInfo(0, point.x, point.y);
        handleReleaseLogic(&touch);
    }
}

void ScrollViewCustom::onTap(TapGestureRecognizer* recognizer) 
{
    auto stato = recognizer->getStatus();
    if (stato == GestureStatus::RECOGNIZED)
    {
        if (baseNode and baseNode->getNumberOfRunningActions() == 0)
        {
            setTouchEnabled(false); // Scroll disabled during the zoom action
            auto enableTouch = CallFunc::create([this]{setScrollBarAutoHideEnabled(true);});
            
            if (getContentScale() == 1) // zoom to max
            {
                baseNode->runAction(ScaleTo::create(SCROLL_VIEW_CUSTOM_SCALE_TO_TIME, SCROLL_VIEW_CUSTOM_MAX_ZOOM));
                setContentScale(SCROLL_VIEW_CUSTOM_MAX_ZOOM);
                auto delta = (1 - SCROLL_VIEW_CUSTOM_MAX_ZOOM) * getInnerContainer()->convertToNodeSpace(recognizer->getGestureLocation());
                auto move = MoveTo::create(SCROLL_VIEW_CUSTOM_SCALE_TO_TIME, delta);
                getInnerContainer()->runAction(Sequence::createWithTwoActions(move, enableTouch));
            }
            else // zoom to 1
            {
                baseNode->runAction(ScaleTo::create(SCROLL_VIEW_CUSTOM_SCALE_TO_TIME, 1.0f));
                setContentScale(1);
                auto move = MoveTo::create(SCROLL_VIEW_CUSTOM_SCALE_TO_TIME, Vec2::ZERO);
                getInnerContainer()->runAction(Sequence::createWithTwoActions(move, enableTouch));
            }
        }
    }
}

#endif