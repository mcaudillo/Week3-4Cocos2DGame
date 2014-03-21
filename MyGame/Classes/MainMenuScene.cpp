#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
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
                                           CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
    
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
    
    auto label = LabelTTF::create("¡Corre de la Fiaca!", "Arial", 40);
    
    // position the label on the center of the screen
    
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    label->setColor(Color3B(0, 0, 0));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("mapa.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    auto helpButton = MenuItemImage::create("help.png","help.png",
                                            CC_CALLBACK_1(MainMenuScene::helpButtonCallback,this));
    
    auto gameButton = MenuItemImage::create("run.png","run.png",
                                            CC_CALLBACK_1(MainMenuScene::gameButtonCallback,this));
    
    helpButton->setPosition(Point((visibleSize.width/10)*2,
                                  visibleSize.height/2));
    gameButton->setPosition(Point((visibleSize.width/10)*8,
                                  visibleSize.height/2));
    
    auto helpButtonMenu = Menu::create(helpButton,NULL);
    helpButtonMenu->setPosition(Point::ZERO);
    this->addChild(helpButtonMenu,1);
    
    auto gameButtonMenu = Menu::create(gameButton,NULL);
    gameButtonMenu->setPosition(Point::ZERO);
    this->addChild(gameButtonMenu,1);
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Chuen.wav");
    
    return true;
}

void MainMenuScene::helpButtonCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(HelpScene::createScene());
}

void MainMenuScene::gameButtonCallback(Ref* pSender)
{
    Director::getInstance()->pushScene(RunScene::createScene());
}

void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
