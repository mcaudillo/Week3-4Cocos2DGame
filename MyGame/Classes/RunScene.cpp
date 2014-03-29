#include "RunScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

float accpastx;
float accpasty;
float accpastz;
int steps=0;
char text[256];
int labelPointX;
int labelPointY;
float beginTime;
bool win=false;

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
    steps=1310;
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
    
    
    return true;
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
    if (changex>.6 && changey>1 && changez>.6 ) {
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
        
        
    }
    accpastx=accx;
    accpasty=accy;
    accpastz=accz;
    
    //second method for winning if the gps information is weak
    if (steps==1313 && win==false) {
        win=true;
        Director::getInstance()->pushScene(WinScene::createScene());
    }
    
    //play warning to the user
    
    //if quarter half and three quarters of time have passed and the steps are not the 1/4, 1/2 and 3/4 of total steps
    if (steps<325 && acc->timestamp -beginTime>180) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("forward.wav");
    }else if (steps<650 && acc->timestamp -beginTime>360){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("forward.wav");
    }else if (steps<975 && acc->timestamp -beginTime>540){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("forward.wav");
    }
    
    
    //second method for losing (12 minutes) which is signal of not running at all
    if (acc->timestamp -beginTime > 720 || (steps<325 && acc->timestamp -beginTime>360) || (steps<650 && acc->timestamp -beginTime>540)) {
        
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
