#include "RunScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;
//accelerator variables to check for the steps
float accpastx;
float accpasty;
float accpastz;
//steps variable
int steps=0;
//text to change the label number of steps with sprintf
char text[256];
//variables of position of the center of the screen
int labelPointX;
int labelPointY;
//variable to help measure the time passed from the begining of the run
float beginTime;
//flag for win scene
bool win=false;
//distance atribute changed with the buttons 1k 5k and 10k,
int distance=1;
//position of the device when the user run.
int position=1;


Scene* RunScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = RunScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool RunScene::init()
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
                                           CC_CALLBACK_1(RunScene::menuCloseCallback, this));
    
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
    
    //initialize steps and accelerometer values
    accpastx=0;
    accpasty=0;
    accpastz=0;
    steps=0;
    labelPointX=origin.x + visibleSize.width/2;
    labelPointY=origin.y + visibleSize.height/2;
    beginTime=0;
    
    
    auto label = LabelTTF::create("¡CORRE!", "Arial", 40);
    
    // position the label on the center of the screen
    label->setPosition(Point(labelPointX,
                             labelPointY));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    
    //CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
    

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("fondo.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Point(labelPointX, labelPointY));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    Device::setAccelerometerEnabled(true);
    
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(RunScene::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    //1k
    auto run1kItem = MenuItemImage::create(
                                           "run1k.png",
                                           "run1k.png",
                                           CC_CALLBACK_1(RunScene::run1kCallback, this));
    
	run1kItem->setPosition(Point(labelPointX/2 ,
                                 labelPointY/2));
    
    // create menu, it's an autorelease object
    auto run1kmenu = Menu::create(run1kItem, NULL);
    run1kmenu->setPosition(Point::ZERO);
    this->addChild(run1kmenu, 1);
    
    
    //5k
    auto run5kItem = MenuItemImage::create(
                                           "run5k.png",
                                           "run5k.png",
                                           CC_CALLBACK_1(RunScene::run5kCallback, this));
    
	run5kItem->setPosition(Point(labelPointX ,
                                 labelPointY/2));
    
    // create menu, it's an autorelease object
    auto run5kmenu = Menu::create(run5kItem, NULL);
    run5kmenu->setPosition(Point::ZERO);
    this->addChild(run5kmenu, 1);
    
    //10k
    auto run10kItem = MenuItemImage::create(
                                           "run10k.png",
                                           "run10k.png",
                                           CC_CALLBACK_1(RunScene::run10kCallback, this));
    
	run10kItem->setPosition(Point(labelPointX*1.5 ,
                                 labelPointY/2));
    
    // create menu, it's an autorelease object
    auto run10kmenu = Menu::create(run10kItem, NULL);
    run10kmenu->setPosition(Point::ZERO);
    this->addChild(run10kmenu, 1);
    
    //hand
    auto handItem = MenuItemImage::create(
                                            "mano.png",
                                            "mano.png",
                                            CC_CALLBACK_1(RunScene::handCallback, this));
    
	handItem->setPosition(Point(labelPointX*.7 ,
                                  labelPointY*1.5));
    
    // create menu, it's an autorelease object
    auto handmenu = Menu::create(handItem, NULL);
    handmenu->setPosition(Point::ZERO);
    this->addChild(handmenu, 1);
    
    //pocket
    auto pocketItem = MenuItemImage::create(
                                            "bolsillo.png",
                                            "bolsillo.png",
                                            CC_CALLBACK_1(RunScene::pocketCallback, this));
    
	pocketItem->setPosition(Point(labelPointX*1.3 ,
                                  labelPointY*1.5));
    
    // create menu, it's an autorelease object
    auto pocketmenu = Menu::create(pocketItem, NULL);
    pocketmenu->setPosition(Point::ZERO);
    this->addChild(pocketmenu, 1);
    
    
    return true;
}

void RunScene::run1kCallback(cocos2d::Ref* pSender){
    
    distance=1;

}

void RunScene::run5kCallback(cocos2d::Ref* pSender){
    
    distance=5;
    
}

void RunScene::run10kCallback(cocos2d::Ref* pSender){
    
    distance=10;
    
}

void RunScene::handCallback(cocos2d::Ref* pSender){
    
    position=1;
    
}

void RunScene::pocketCallback(cocos2d::Ref* pSender){
    
    position=3;
    
}
                                          

void RunScene::onAcceleration(Acceleration* acc, Event* event)
{
    if (beginTime==0) {
        beginTime=acc->timestamp;
    }
    
    
    //acceleration x and give a variable change between the accelerometer values
    float accx;
    float changex;
    if (acc->x<0) {
        accx=-acc->x;
    }else{
        accx=acc->x;
    }
    
    if (accx>accpastx) {
        changex=accx-accpastx;
    }else{
        changex=accpastx-accx;
    }
    
    //acceleration y and give a variable change between the accelerometer values
    float accy;
    float changey;
    if (acc->y<0) {
        accy=-acc->y;
    }else{
        accy=acc->y;
    }
    
    if (accy>accpastx) {
        changey=accy-accpasty;
    }else{
        changey=accpasty-accy;
    }
    
    //acceleration z and give a variable change between the accelerometer values
    float accz;
    float changez;
    if (acc->z<0) {
        accz=-acc->z;
    }else{
        accz=acc->z;
    }
    
    if (accz>accpastz) {
        changez=accz-accpastz;
    }else{
        changez=accpastz-accz;
    }
    
    //if the change is a shake of the device add a step to the count
    if (changex>.6/position && changey>1/position && changez>.6/position ) {
        steps++;
        this->removeAllChildrenWithCleanup(true);
        
        // add "HelloWorld" splash screen"
        auto sprite = Sprite::create("fondo.png");
        
        // position the sprite on the center of the screen
        sprite->setPosition(Point(labelPointX, labelPointY));
        
        // add the sprite as a child to this layer
        this->addChild(sprite, 1);
        
        sprintf(text, "Kilómetros: %2f",steps*0.00076161462);
        
        auto stepLabel = LabelTTF::create(text, "Arial", 80);
        
        // position the label on the center of the screen
        stepLabel->setPosition(Point(labelPointX,
                                     labelPointY));
        
        // add the label as a child to this layer
        this->addChild(stepLabel, 1);
        
        // add a "close" icon to exit the progress. it's an autorelease object
        auto closeItem = MenuItemImage::create(
                                               "CloseNormal.png",
                                               "CloseSelected.png",
                                               CC_CALLBACK_1(RunScene::menuCloseCallback, this));
        
        closeItem->setPosition(Point(labelPointX*1.9 ,
                                     labelPointY*.1));
        
        // create menu, it's an autorelease object
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Point::ZERO);
        this->addChild(menu, 1);
        
        //method for winning
        if (steps==1313*distance && win==false) {
            win=true;
            Director::getInstance()->pushScene(WinScene::createScene());
        }
        
        
    }
    accpastx=accx;
    accpasty=accy;
    accpastz=accz;
    
    
    
    //play warning to the user
    
    //if quarter half and three quarters of time have passed and the steps are not the 1/4, 1/2 and 3/4 of total steps
    if (steps<325*distance && acc->timestamp -beginTime>180*distance) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("forward.wav");
    }else if (steps<650*distance && acc->timestamp -beginTime>360*distance){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("forward.wav");
    }else if (steps<975*distance && acc->timestamp -beginTime>540*distance){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("forward.wav");
    }
    
    
    //second method for losing (12 minutes/km) which is signal of not running at all
    if (acc->timestamp -beginTime > 720*distance || (steps<325*distance && acc->timestamp -beginTime>360*distance) || (steps<650*distance && acc->timestamp -beginTime>540*distance)) {
        
        Director::getInstance()->pushScene(LostScene::createScene());
    }
    
}





void RunScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
