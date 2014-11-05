#ifndef __KANJIBASE_H__
#define __KANJIBASE_H__

#include "cocos2d.h"

class KanjiBase : public cocos2d::Layer
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
   
private:
   cocos2d::Menu *kanjiBaseMenu;
};



#endif // __KANJIBASE_H__
