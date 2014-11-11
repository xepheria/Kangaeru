#include "KanjiBase.h"
#include "CustomTableViewCell.h"
#include <iostream>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

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
   
   auto size = Director::getInstance()->getVisibleSize();
   auto background = Sprite::create("background.png"); //here the background.png is a "red screen" png.
   background->setScale(size.height/background->getContentSize().height);
   background->setPosition(size.width/2, size.height/2);
   this->addChild(background);     // add a background sprite to watch more obviously
   
   //Create kanjibase main menu
   backToMainMenu(nullptr);
   
   return true;

}

//called when 'back' button is hit on a dictionary menu
void KanjiBase::backToMainMenu(cocos2d::Ref *pSender){
   this->kanjiBaseMenu = createKBMenu();
   this->addChild(kanjiBaseMenu);
   
   if(pSender != nullptr){
      this->removeChild(pTable);
      this->removeChild(kanjiInfoMenu);
      this->removeChildByTag(50);
   }
}

Menu *KanjiBase::createKBMenu(){
   auto size = Director::getInstance()->getWinSize();
   
   auto back_menu = MenuItemLabel::create(LabelTTF::create("Back", "Arial", 48), [](Ref* sender){Director::getInstance()->popScene();});
   auto N5_dictionary = MenuItemLabel::create(LabelTTF::create("N5 Dictionary", "Arial", 48), this, menu_selector(KanjiBase::N5Callback));
   auto menu = Menu::create(back_menu,N5_dictionary,nullptr);
   menu->alignItemsVertically();
   menu->setPosition(Point(size.width/2, size.height/2));
   
   return menu;
}

//Open dictionary file
void KanjiBase::N5Callback(cocos2d::Ref *pSender){
   //close mainmenu
   this->removeChild(this->kanjiBaseMenu);
   
   Size winSize = Director::getInstance()->getVisibleSize();
   
   //create back button
   auto N5back_menu = MenuItemLabel::create(LabelTTF::create("Back", "Arial", 48), this, menu_selector(KanjiBase::backToMainMenu));
   auto N5menu = Menu::create(N5back_menu,nullptr);
   N5menu->setTag(50);
   N5menu->setPosition(Point(winSize.width, winSize.height));
   N5back_menu->setAnchorPoint(Point(1, 1));
   this->addChild(N5menu);
   
   //init kanjiInfoMenu
   cout << "Create menu" << endl;
   kanjiLabel = LabelTTF::create("some info about the kanji", "fonts/falcon.ttf", 34);
   kanjiLabel->setColor(Color3B(246, 103, 51));
   kanjiInfoButton = MenuItemLabel::create(kanjiLabel);
   
   //create actual background image*****************
   auto kanjiMenuBackground = MenuItemImage::create("kanjiInfoBG.png", "kanjiInfoBG.png", "kanjiInfoBG.png");
   
   kanjiInfoMenu = Menu::create(kanjiMenuBackground, kanjiInfoButton, nullptr);
   kanjiInfoMenu->setPosition(Vec2(winSize.width*.8, winSize.height*.5));
   
   kanjiMenuBackground->setPosition(Vec2(-400, 0));
   
   kanjiInfoMenu->setVisible(false);
   this->addChild(kanjiInfoMenu);
   
   cout << "background location: " << kanjiMenuBackground->getPositionX() << " " << kanjiMenuBackground->getPositionY() << endl;
   cout << "menu location: " << kanjiInfoMenu->getPositionX() << " " << kanjiInfoMenu->getPositionY() << endl;
   
   //now display the dictionary
   //open dictionary plist file
   std::string path = FileUtils::getInstance()->fullPathForFilename("dictionaries/N5.plist");
   N5Dict = FileUtils::getInstance()->getValueMapFromFile(path);
   //cout << N5Dict.size() << endl;
   numOfCells = N5Dict.size();
   
   //create a tableview
   pTable = TableView::create(this, winSize);
   pTable->setDirection(ScrollView::Direction::VERTICAL);
   pTable->setPosition(Vec2(winSize.width/2-50,0));
   pTable->setDelegate(this);
   pTable->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
   this->addChild(pTable);
   pTable->reloadData();

   //traverse dictionary
   for(unsigned int i = 0; i < N5Dict.size(); i++){
      string str = std::to_string(i);
      const char *str1 = str.c_str();
      ValueMap kanjiEntry = N5Dict.at(str1).asValueMap();
      auto kanjiName = kanjiEntry.at("Kanji").asString();
      //cout << kanjiName << endl;
   }
   
   //tbd
   
}

//tableview functions
void KanjiBase::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLOG("cell touched at index: %ld", cell->getIdx());
    //display more information about the kanji
    //String kanjiToLabel = 
    kanjiLabel->setString("clicked a cell");
    cout << "clicked it" << endl;
    if(!kanjiInfoMenu->isVisible()){
      cout << "no good?" << endl;
      kanjiInfoMenu->setVisible(true); 
    }
}

Size KanjiBase::tableCellSizeForIndex(TableView *table, ssize_t idx)
{

    return Size(100, 60);
}

TableViewCell* KanjiBase::tableCellAtIndex(TableView *table, ssize_t idx)
{
   //creates the numbers for the string, with idx being the index
   //cout << std::to_string(idx) << endl;
   auto kanjiEntry = N5Dict.at(std::to_string(idx)).asValueMap();
   std::string kanjiString = kanjiEntry.at("Kanji").asString();
   //cout << kanjiString << endl;
   TableViewCell *cell = table->dequeueCell();
   //creates default icon with index if table doesn't contain cell
   if (!cell) {
      cell = new CustomTableViewCell();
      cell->autorelease();
      //create default icon sprite
      auto sprite = Sprite::create("Icon.png");
      sprite->setAnchorPoint(Vec2::ZERO);
      sprite->setPosition(cell->getContentSize().width/2, cell->getContentSize().height/2);
      cell->addChild(sprite);
      
      //generates the numbered label for each icon
      auto label = Label::createWithSystemFont(kanjiString, "fonts/falcon.ttf", 30.0);
      label->setPosition(Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
      label->setAnchorPoint(Vec2(0.5, 0.5));
      label->setTag(123);
      cell->addChild(label);
   }
   //generates cell's label
   else
   {
      auto label = (Label*)cell->getChildByTag(123);
      label->setString(kanjiString);
   }


   return cell;
}

ssize_t KanjiBase::numberOfCellsInTableView(TableView *table)
{
    return numOfCells;
}
