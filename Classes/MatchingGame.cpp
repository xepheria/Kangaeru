#include "MatchingGame.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <string>

USING_NS_CC;
using namespace std;

MatchingGame::MatchingGame(void){

}

MatchingGame::~MatchingGame(void){
    CC_SAFE_RELEASE(blinkAction);
}

Scene* MatchingGame::createScene(void){
   // 'scene' is an autorelease object
   auto scene = Scene::create();

   // 'layer' is an autorelease object
   auto layer = MatchingGame::create();

   // add layer as a child to scene
   scene->addChild(layer);

   // return the scene
   return scene;
}

bool MatchingGame::init(){
   if(!Layer::init()){
      return false;
   }
   
   //create background
   auto winSize = Director::getInstance()->getVisibleSize();
   auto background = Sprite::create("gameBackground.jpg");
   background->setScale(winSize.width/background->getContentSize().width);
   background->setPosition(winSize.width/2, winSize.height/2);
   this->addChild(background);     // add a background sprite to watch more obviously

   //back to main menu button
   auto back_menu = MenuItemLabel::create(Label::create("Back to Main Menu", "Arial", 48), this, menu_selector(MatchingGame::backToMainScene));
   auto backMenu = Menu::create(back_menu, nullptr);
   backMenu->setPosition(Point(winSize.width, winSize.height));
   back_menu->setAnchorPoint(Point(1, 1));
   this->addChild(backMenu, 1);
   
   //create menu of existing lists
   menu = Menu::create();
   for(int i = 0; i < UserDefault::getInstance()->getIntegerForKey("numOfLists"); i++){
      string listName = "list" + to_string(i);
      auto addToDaMenu = MenuItemLabel::create(Label::create(UserDefault::getInstance()->getStringForKey(listName.c_str()), "fonts/falcon.ttf", 40), this, menu_selector(MatchingGame::startWithListCallback));
      dynamic_cast<Label*>(addToDaMenu->getLabel())->enableOutline(Color4B::BLACK, 3);
      addToDaMenu->setTag(1); //tag indicates this is a user list
      menu->addChild(addToDaMenu);
   }
   menu->setPosition(winSize.width*.75, winSize.height/2);
   menu->alignItemsVerticallyWithPadding(15);
   this->addChild(menu, 1);
   title = Label::create("User Lists", "fonts/falcon.ttf", 36);
   title->enableOutline(Color4B::BLACK, 3);
   title->setPosition(winSize.width*.75, winSize.height*.8);
   this->addChild(title);
   
   //create menu of dictionary lists
   menu2 = Menu::create();
   auto N5menu = MenuItemLabel::create(Label::create("N5", "fonts/falcon.ttf", 48), this, menu_selector(MatchingGame::startWithListCallback));
   dynamic_cast<Label*>(N5menu->getLabel())->enableOutline(Color4B::BLACK, 3);
   N5menu->setTag(0);
   menu2->addChild(N5menu);
   //*********
   //add more lists here as they are made
   //*********
   menu2->setPosition(winSize.width/4, winSize.height/2);
   menu2->alignItemsVerticallyWithPadding(15);
   this->addChild(menu2, 1);
   title2 = Label::create("Default Lists", "fonts/falcon.ttf", 48);
   title2->enableOutline(Color4B::BLACK, 3);
   title2->setPosition(winSize.width/4, winSize.height*.8);
   this->addChild(title2);
   
   //initialize blinking action
   blinkAction = Sequence::create(Blink::create(1.0, 3), Hide::create(), NULL);
   blinkAction->retain();
   //create Sprites
   maru = Sprite::create("maru.png");
   batsu = Sprite::create("batsu.png");
   maru->setPosition(winSize.width/2, winSize.height/2);
   batsu->setPosition(winSize.width/2, winSize.height/2);
   maru->setVisible(false);
   batsu->setVisible(false);
   this->addChild(maru);
   this->addChild(batsu);
   
   //init score to 0
   currentCorrect = 0;
   currentWrong = 0;
   correctScore = Label::create("0", "fonts/falcon.ttf", 60);
   correctScore->setColor(Color3B::ORANGE);
   correctScore->enableOutline(Color4B::BLACK, 1);
   correctScore->setPosition(winSize.width*.33, winSize.height*.05);
   wrongScore = Label::create("0", "fonts/falcon.ttf", 60);
   wrongScore->setColor(Color3B::RED);
   wrongScore->enableOutline(Color4B::BLACK, 1);
   wrongScore->setPosition(winSize.width*.66, winSize.height*.05);
   this->addChild(correctScore);
   this->addChild(wrongScore);
   
   return true;
}

//back to main menu
void MatchingGame::backToMainScene(cocos2d::Ref *pSender){
   //saveData();
   Director::getInstance()->popScene();
}

//start game with chosen list
void MatchingGame::startWithListCallback(cocos2d::Ref *pSender){
   auto ref = dynamic_cast<MenuItemLabel*>(pSender);
   
   Label *listLabel = dynamic_cast<Label*>(ref->getLabel());
   string path = listLabel->getString() + ".plist";
   //list is default
   if(ref->getTag() == 0){
      path = "dictionaries/" + path;
      path = FileUtils::getInstance()->fullPathForFilename(path);
      kanjiDict = FileUtils::getInstance()->getValueMapFromFile(path);
   }
   //list is user made
   else {
      path = FileUtils::getInstance()->getWritablePath() + path;
      kanjiDict = FileUtils::getInstance()->getValueMapFromFile(path);
   }
   
   menu->setVisible(false);
   menu2->setVisible(false);
   title->setVisible(false);
   title2->setVisible(false);
   
   auto winSize = Director::getInstance()->getVisibleSize();
   question = Label::create("This is an empty question that tests word wrapping if the question is too long.", "fonts/falcon.ttf", 64);
   question->setAlignment(TextHAlignment::CENTER);
   question->setDimensions(winSize.width, winSize.height*.6);
   question->enableOutline(Color4B::BLACK, 4);
   question->setPosition(winSize.width/2, winSize.height*.6);
   this->addChild(question);
   
   ans1 = MenuItemLabel::create(Label::create("answer 1", "fonts/falcon.ttf", 60), this, menu_selector(MatchingGame::evaluateAnswer));
   dynamic_cast<Label*>(ans1->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans1->setAnchorPoint(Vec2(1, .5));
   
   ans2 = MenuItemLabel::create(Label::create("answer 2", "fonts/falcon.ttf", 60), this, menu_selector(MatchingGame::evaluateAnswer));
   dynamic_cast<Label*>(ans2->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans2->setAnchorPoint(Vec2(0, .5));
   
   ans3 = MenuItemLabel::create(Label::create("answer 3", "fonts/falcon.ttf", 60), this, menu_selector(MatchingGame::evaluateAnswer));
   dynamic_cast<Label*>(ans3->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans3->setAnchorPoint(Vec2(1, 2.5));
   
   ans4 = MenuItemLabel::create(Label::create("answer 4", "fonts/falcon.ttf", 60), this, menu_selector(MatchingGame::evaluateAnswer));
   dynamic_cast<Label*>(ans4->getLabel())->enableOutline(Color4B::BLACK, 3);
   ans4->setAnchorPoint(Vec2(0, 2.5));
   
   answers = Menu::create(ans1, ans2, ans3, ans4, nullptr);
   answers->setPosition(winSize.width/2, winSize.height/2);
   answers->alignItemsInColumns(2, 2);
   this->addChild(answers);
   
   askQuestion(0);
}

void MatchingGame::askQuestion(float dt){
   //select a kanji from the list for correct answer
   srand(time(NULL));
   int correctIndex = rand() % kanjiDict.size();
   ValueMap correctKanji = kanjiDict.at(to_string(correctIndex).c_str()).asValueMap();
   //get the wrong indexes, make sure they don't match correct index
   int wrongIndex1, wrongIndex2, wrongIndex3;
   do{
      wrongIndex1 = rand() % kanjiDict.size();
      wrongIndex2 = rand() % kanjiDict.size();
      wrongIndex3 = rand() % kanjiDict.size();
   } while (wrongIndex1 == correctIndex || wrongIndex2 == correctIndex || wrongIndex3 == correctIndex || wrongIndex1 == wrongIndex2 || wrongIndex1 == wrongIndex3 || wrongIndex2 == wrongIndex3);
   
   //set question type
   //0: kunyomi
   //1: definition
   //2: onyomi
   int questionType = rand() % 3;
   
   //set question to kanji clue
   if(questionType == 0){
      if(correctKanji.find("Kunyomi") != correctKanji.end())
         question->setString(correctKanji.at("Kunyomi").asString());
      else
         question->setString(correctKanji.at("Onyomi").asString());
   }
   else if(questionType == 1){
      question->setString(correctKanji.at("Definition").asString());
   }
   else if(questionType == 2){
      if(correctKanji.find("Onyomi") != correctKanji.end())
         question->setString(correctKanji.at("Onyomi").asString());
      else
         question->setString(correctKanji.at("Kunyomi").asString());
   }
   
   //set the anwers, make sure to set tag on right answer to 1, wrong answers to 0
   int questionOrder = rand() % 4;
   switch(questionOrder){
   case 0:
      //correct answer is ans1
      ans1->setString(correctKanji.at("Kanji").asString());
      ans1->setTag(1);
      //wrong answers
      ans2->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans2->setTag(0);
      ans3->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans3->setTag(0);
      ans4->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans4->setTag(0);
      break;
   case 1:
      //correct answer is ans2
      ans2->setString(correctKanji.at("Kanji").asString());
      ans2->setTag(1);
      //wrong answers
      ans1->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans1->setTag(0);
      ans3->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans3->setTag(0);
      ans4->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans4->setTag(0);
      break;
   case 2:
      //correct answer is ans3
      ans3->setString(correctKanji.at("Kanji").asString());
      ans3->setTag(1);
      //wrong answers
      ans1->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans1->setTag(0);
      ans2->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans2->setTag(0);
      ans4->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans4->setTag(0);
      break;
   case 3:
      //correct answer is ans4
      ans4->setString(correctKanji.at("Kanji").asString());
      ans4->setTag(1);
      //wrong answers
      ans1->setString(kanjiDict.at(to_string(wrongIndex1).c_str()).asValueMap().at("Kanji").asString());
      ans1->setTag(0);
      ans2->setString(kanjiDict.at(to_string(wrongIndex2).c_str()).asValueMap().at("Kanji").asString());
      ans2->setTag(0);
      ans3->setString(kanjiDict.at(to_string(wrongIndex3).c_str()).asValueMap().at("Kanji").asString());
      ans3->setTag(0);
      break;
   }
}

void MatchingGame::evaluateAnswer(Ref *pSender){
   MenuItemLabel *ref = dynamic_cast<MenuItemLabel*>(pSender);
   if(ref->getTag() == 0){
      currentWrong++;
      wrongScore->setString(to_string(currentWrong));
      batsu->runAction(blinkAction);
   }
   else if(ref->getTag() == 1){
      currentCorrect++;
      correctScore->setString(to_string(currentCorrect));
      maru->runAction(blinkAction);
   }
   else
      cout << "wat" << endl;
   
   //wait until animation done
   this->scheduleOnce(schedule_selector(MatchingGame::askQuestion), 1.5f);
}
