//
//  WinScene.h
//  MyGame
//
//  Created by Mario A Caudillo Melgoza on 3/28/14.
//
//

#ifndef __WIN_SCENE_H__
#define __WIN_SCENE_H__

#include "cocos2d.h"
#include "MainMenuScene.h"

class WinScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // selector callbacks
    void menuCloseCallback(cocos2d::Ref* pSender);
    void homeButtonCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(WinScene);
};

#endif // __WIN_SCENE_H__