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
   
   //Create kanjibase main menu
   backToMainMenu();
   
   return true;

}

//called when 'back' button is hit on a dictionary menu
void KanjiBase::backToMainMenu(){
   this->kanjiBaseMenu = createKBMenu();
   this->addChild(kanjiBaseMenu);
}

Menu *KanjiBase::createKBMenu(){
   auto size = Director::getInstance()->getWinSize();
   
   auto back_menu = MenuItemLabel::create(LabelTTF::create("Back", "Arial", 48), [](Ref* sender){Director::getInstance()->popScene();});
   auto N5_dictionary = MenuItemLabel::create(LabelTTF::create("N5 Dictionary", "Arial", 48), this, menu_selector(KanjiBase::N5Callback));
   auto menu = Menu::create(back_menu,N5_dictionary,nullptr);
   menu->setPosition(Point(size.width/2, size.height/2));
   
   return menu;
}

//Open dictionary file
void KanjiBase::N5Callback(cocos2d::Ref *pSender){
   //close mainmenu
   this->removeChild(this->kanjiBaseMenu);
   
   //now display the dictionary
   //tbd
}
