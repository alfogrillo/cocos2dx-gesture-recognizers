#include "ScrollableMenu.h"

bool ScrollableMenu::init()
{
    if (not Node::init()){
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    createListView();
    return true;
}

void ScrollableMenu::createListView()
{
    using namespace cocos2d::ui;
    
    listView = ListView::create();
    listView->setDirection(ScrollView::Direction::VERTICAL);
    listView->setInertiaScrollEnabled(true);
    listView->setClippingEnabled(true);
    listView->setClippingType(cocos2d::ui::Layout::ClippingType::SCISSOR);
    listView->setGravity(ListView::Gravity::CENTER_HORIZONTAL);
    listView->setColor(Color3B::BLACK);
    listView->setBounceEnabled(true);
    listView->setContentSize({visibleSize.width, visibleSize.height * DEFAULT_LISTVIEW_HEIGHT});
    listView->addEventListener(CC_CALLBACK_2(ScrollableMenu::selectedItem, this));
    listView->setItemsMargin(DEFAULT_ITEM_MARGIN);
    addChild(listView);

}

void ScrollableMenu::selectedItem(cocos2d::Ref *s, ui::ListView::EventType type)
{
    using namespace cocos2d::ui;
    
    switch (type)
    {
        case ListView::EventType::ON_SELECTED_ITEM_END:
            lambdas[listView->getCurSelectedIndex()]();
            break;
        default:
            break;
    }
 
}

void ScrollableMenu::setTitle(std::string text, int fontSize, Color3B color)
{
    auto l = Label::createWithTTF(text, "fonts/Marker Felt.ttf", fontSize, {visibleSize.width, (float)fontSize}, TextHAlignment::CENTER);
    float normHeight = DEFAULT_LISTVIEW_HEIGHT + (1.0f - DEFAULT_LISTVIEW_HEIGHT) / 2.0f;
    l->setPosition({visibleSize.width/2.0f, visibleSize.height * normHeight});
    l->setColor(color);
    l->enableShadow();
    addChild(l);

}