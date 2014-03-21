#include "HelpScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelpScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelpScene::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Ayuda", "Arial", 40);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("ayuda.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    
    auto homeButton = MenuItemImage::create("menu.png","menu.png",CC_CALLBACK_1(HelpScene::homeButtonCallback,this));
    
    homeButton->setPosition(Point((visibleSize.width/10)*0.8,
                                  (visibleSize.height/10)*9));
    
    auto homeButtonMenu = Menu::create(homeButton,NULL);
    homeButtonMenu->setPosition(Point::ZERO);
    this->addChild(homeButtonMenu, 1);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Chuen.wav");
    
    return true;
}

void HelpScene::homeButtonCallback(Ref* pSender)
{
    Director::getInstance()->popScene();
}


void HelpScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
