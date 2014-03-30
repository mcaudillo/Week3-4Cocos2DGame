#ifndef __RUN_SCENE_H__
#define __RUN_SCENE_H__

#include "cocos2d.h"
#include "WinScene.h"
#include "LostScene.h"

class RunScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // selector callbacks
    void menuCloseCallback(cocos2d::Ref* pSender);
    void run1kCallback(cocos2d::Ref* pSender);
    void run5kCallback(cocos2d::Ref* pSender);
    void run10kCallback(cocos2d::Ref* pSender);
    void handCallback(cocos2d::Ref* pSender);
    void pocketCallback(cocos2d::Ref* pSender);
    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* event);
    
    // implement the "static create()" method manually
    CREATE_FUNC(RunScene);
};

#endif // __RUN_SCENE_H__
