#ifndef __KANJIBASE_H__
#define __KANJIBASE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class KanjiBase : public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
   KanjiBase(void);
   ~KanjiBase(void);

   //create default functions
   CREATE_FUNC(KanjiBase);

   static cocos2d::Scene* createScene();

   virtual bool init() override;
   
   void backToMainMenu();
   void N5Callback(cocos2d::Ref *pSender);
   cocos2d::Menu *createKBMenu();
   
   //table view functions
   virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) {};
   virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) {}
   virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
   virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
   virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
   virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
   
private:
   cocos2d::Menu *kanjiBaseMenu;
   cocos2d::ValueMap N5Dict;
   ssize_t numOfCells;
};



#endif // __KANJIBASE_H__
