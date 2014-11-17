#include "MainMenu.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //cocos vector to hold menu items
    cocos2d::Vector<cocos2d::MenuItem*> pMenuItems;
    
    //game 1
    cocos2d::MenuItem *pGame1Item = cocos2d::MenuItemImage::create("Game1Normal.png", "Game1Selected.png", this, menu_selector(MainMenu::menuGame1Callback));
    pMenuItems.pushBack(pGame1Item); //add to list
    
    //game 2
    cocos2d::MenuItem *pGame2Item = cocos2d::MenuItemImage::create("Game2Normal.png", "Game2Selected.png", this, menu_selector(MainMenu::menuGame2Callback));
    pMenuItems.pushBack(pGame2Item);
    
    //close menu
    cocos2d::MenuItem *pCloseItem = cocos2d::MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(MainMenu::menuCloseCallback));
    pMenuItems.pushBack(pCloseItem); //add to list
    
    cocos2d::Menu *pMenu = cocos2d::Menu::createWithArray(pMenuItems); //create menu

    pMenu->alignItemsVertically();

    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCString *labelString = CCString::createWithFormat("漢ガエル");
    auto label = LabelTTF::create(labelString->getCString(), "fonts/falcon.ttf", 40);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "MainMenu" splash screen"
    auto sprite = Sprite::create("MainMenubackground.jpg");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //scale sprite
    sprite->setScale(visibleSize.width/sprite->getContentSize().width);

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

//Game 1
void MainMenu::menuGame1Callback(cocos2d::Ref *pSender){
   transitionToKanjiBaseScene();
    //tbd
}

//Game 2
void MainMenu::menuGame2Callback(cocos2d::Ref *pSender){
    //tbd
}

//Close game
void MainMenu::menuCloseCallback(cocos2d::Ref *pSender){
    Director::getInstance()->end();
    exit(0);
}

void MainMenu::toGameScene()
{
    //get the game scene and run it.
    auto scene = KanjiBase::createScene();
    Director::getInstance()->pushScene(scene);
    //what is diff between replaceScene and pushScene?
}

//transition to kanji base
void MainMenu::transitionToKanjiBaseScene(){
   toGameScene();
}
