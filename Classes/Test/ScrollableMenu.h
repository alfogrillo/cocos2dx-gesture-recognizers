#pragma once

#include <stdio.h>
#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <string>
#include <vector>
#include <functional>

using namespace cocos2d;

#define DEFAULT_LISTVIEW_HEIGHT 0.85f
#define DEFAULT_ITEM_MARGIN 30

class ScrollableMenu : public cocos2d::Node
{
public:
    virtual bool init();
    CREATE_FUNC(ScrollableMenu);
    void setTitle(std::string text, int fontSize = 80, Color3B color = Color3B::YELLOW);
    
    template <class ScenaType>
    void addMenuEntry(std::string desc, int fontSize = 65, Color3B color = Color3B::WHITE)
    {
        using namespace cocos2d::ui;
        
        auto text = Text::create(desc.c_str(), "fonts/Marker Felt.ttf", fontSize);
        text->setTextHorizontalAlignment(TextHAlignment::CENTER);
        text->setTouchEnabled(true);
        text->setColor(color);
        listView->pushBackCustomItem(text);
        
        auto loadScene = []{
            auto scene = ScenaType::createScene();
            Director::getInstance()->pushScene(scene);
        };
        
        lambdas.push_back(loadScene);
    }
    
private:
    void createListView();
    void selectedItem(cocos2d::Ref *s, ui::ListView::EventType type);
    
    ui::ListView* listView {nullptr};
    cocos2d::Size visibleSize;
    std::vector<std::function<void()>> lambdas;
};