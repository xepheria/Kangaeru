#include "KanjiBase.h"

USING_NS_CC;

KanjiBase::KanjiBase(void){

}

KanjiBase::~KanjiBase(void){

}

Scene* KanjiBase::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = KanjiBase::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool KanjiBase::init(){
   if(!Layer::init()){
      return false;
   }
   
   auto size = Director::getInstance()->getWinSize();
   auto background = Sprite::create("background.png"); //here the background.png is a "red screen" png.
   background->setScale(size.width/background->getContentSize().width);
   background->setPosition(size.width/2, size.height/2);
   this->addChild(background);     // add a background sprite to watch more obviously
   
   auto back_label = LabelTTF::create("Back", "Arial", 48);
   auto back_menu = MenuItemLabel::create(back_label, [](Ref* sender){Director::getInstance()->popScene(); });
   auto menu = Menu::create(back_menu,nullptr);
   menu->setPosition(Point(size.width/2, size.height/2));
   this->addChild(menu);
   return true;
   
   return true;
}
