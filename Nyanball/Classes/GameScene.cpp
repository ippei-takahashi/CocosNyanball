#include "GameScene.h"
#include "GB2ShapeCache-x.h"
#include "AppMacros.h"

#define PTM_RATIO 1024

USING_NS_CC;

static int scorePoint;

GamePhysicsContactListener::GamePhysicsContactListener(Ref* target, SEL_CallFunc selector)
{
    m_target = target;
    m_selector = selector;
}

void GamePhysicsContactListener::BeginContact(b2Contact* contact)
{
    Ref* userDataA = (Ref*)contact->GetFixtureA()->GetUserData();
    Ref* userDataB = (Ref*)contact->GetFixtureB()->GetUserData();
    
    String* stringA = dynamic_cast<String*>(userDataA);
    String* stringB = dynamic_cast<String*>(userDataB);
    
    if (stringA->intValue() > 0 || stringB->intValue() > 0)
    {
        scorePoint += stringA->intValue();
        scorePoint += stringB->intValue();
        
        (m_target->*m_selector)();
    }
}

Scene* GameScene::scene()
{
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
        return false;
    
    ballCount = 5;
    
    // シェイプデータの読込み
    gbox2d::GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("nyanball.plist");
    
    // タップを有効にする
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    // 物理空間の生成
    initPhysics();
    
    // 背景を追加
    //createBackground();
    
    // ボタンを追加
    createButton();
    
    // フリッパーを追加
    //createFlipper();
    
    // 得点の表示
    createScore();
    
    // リセットボタンの表示
    createReset();
    
    // 毎フレーム処理の開始
    scheduleUpdate();
    
    return true;
}

void GameScene::createBackground()
{
    Size winSize = CCDirector::getInstance()->getWinSize();
    
    // 背景
    Sprite* bg = CCSprite::create("background.png");
    bg->setScale(2);
    bg->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(bg, kZOrder_Background, kTagBackground);

    // 背景の物理構造
    b2BodyDef bgBodyDef;
    bgBodyDef.type = b2_staticBody;
    bgBodyDef.position.Set(bg->getPositionX() / PTM_RATIO, bg->getPositionY() / PTM_RATIO);
    bgBodyDef.userData = bg;
    bgBody = world->CreateBody(&bgBodyDef);
    
    gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(bgBody, "background");
    bg->setAnchorPoint(sc->anchorPointForShape("background"));
}

void GameScene::createButton()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    // 左ボタン
    Sprite* leftButton = Sprite::create("button_left.png");
    leftButton->setPosition(Vec2(winSize.width * 0.2, winSize.height * 0.1));
    this->addChild(leftButton, kZOrder_Button);
    
    // 右ボタン
    Sprite* rightButton = Sprite::create("button_right.png");
    rightButton->setPosition(Vec2(winSize.width * 0.8, winSize.height * 0.1));
    this->addChild(rightButton, kZOrder_Button);
}

void GameScene::createFlipper()
{
    Size winSize = CCDirector::getInstance()->getWinSize();
    
    gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    
    // 左フリッパー
    Point leftFlipperPos = Vec2(winSize.width * 0.3, winSize.height * 0.04);
    Sprite* leftFlipper = Sprite::create("flipper_left.png");
    leftFlipper->setScale(2);
    leftFlipper->setPosition(leftFlipperPos);
    this->addChild(leftFlipper, kZOrder_Flipper);
    
    // 左フリッパーの物理構造
    b2BodyDef leftFlipperBodyDef;
    leftFlipperBodyDef.type = b2_dynamicBody;
    leftFlipperBodyDef.position.Set(leftFlipperPos.x / PTM_RATIO, leftFlipperPos.y / PTM_RATIO);
    leftFlipperBodyDef.userData = leftFlipper;
    
    leftFlipperBody = world->CreateBody(&leftFlipperBodyDef);
    sc->addFixturesToBody(leftFlipperBody, "flipper_left");
    leftFlipper->setAnchorPoint(sc->anchorPointForShape("flipper_left"));
    leftFlipperBody->SetTransform(leftFlipperBody->GetPosition(), CC_DEGREES_TO_RADIANS(0));

    // 左フリッパーのジョイント
    b2RevoluteJointDef leftJointDef;
    leftJointDef.Initialize(leftFlipperBody, bgBody, leftFlipperBody->GetPosition());
    leftJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(-45);
    leftJointDef.upperAngle = CC_DEGREES_TO_RADIANS(0);
    leftJointDef.enableLimit = true;
    world->CreateJoint(&leftJointDef);

    // 右フリッパー
    Point rightFlipperPos = Vec2(winSize.width * 0.7, winSize.height * 0.04);
    Sprite* rightFlipper = Sprite::create("flipper_right.png");
    rightFlipper->setPosition(rightFlipperPos);
    this->addChild(rightFlipper, kZOrder_Flipper);
    
    // 右フリッパーの物理構造
    b2BodyDef rightFlipperBodyDef;
    rightFlipperBodyDef.type = b2_dynamicBody;
    rightFlipperBodyDef.position.Set(rightFlipperPos.x / PTM_RATIO, rightFlipperPos.y / PTM_RATIO);
    rightFlipperBodyDef.userData = rightFlipper;
    
    rightFlipperBody = world->CreateBody(&rightFlipperBodyDef);
    sc->addFixturesToBody(rightFlipperBody, "flipper_right");
    rightFlipper->setAnchorPoint(sc->anchorPointForShape("flipper_right"));
    rightFlipperBody->SetTransform(rightFlipperBody->GetPosition(), CC_DEGREES_TO_RADIANS(0));

    // 右フリッパーのジョイント
    b2RevoluteJointDef rightJointDef;
    rightJointDef.Initialize(rightFlipperBody, bgBody, rightFlipperBody->GetPosition());
    rightJointDef.lowerAngle = CC_DEGREES_TO_RADIANS(0);
    rightJointDef.upperAngle = CC_DEGREES_TO_RADIANS(45);
    rightJointDef.enableLimit = true;
    world->CreateJoint(&rightJointDef);
}

void GameScene::initPhysics()
{
    b2Vec2 gravity;
    gravity.Set(0.0f, -0.8f);
    world = new b2World(gravity);
    
    // 衝突判定処理を追加
    gamePhysicsContactListener = new GamePhysicsContactListener(this, callfunc_selector(GameScene::updateScore));
    world->SetContactListener(gamePhysicsContactListener);
}

void GameScene::update(float dt)
{
    int velocityIterations = 8;
    int positionIterations = 1;
    
    world->Step(dt, velocityIterations, positionIterations);

    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL)
        {
            Sprite* myActor = (Sprite*)b->GetUserData();
            
            if (b->GetPosition().y < 0)
            {
                world->DestroyBody(b);
                this->removeChild(myActor);
                continue;
            }
            
            myActor->setPosition(Point(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
            myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
        }
    }
}

void GameScene::createBall()
{
    if (ballCount <= 0)
        return;
    
    ballCount--;
    
    Size winSize = Director::getInstance()->getWinSize();
    
    // ボールの作成
    Point ballPoint = Vec2(winSize.width * 0.55, winSize.height * 0.85);
    Sprite* ball = Sprite::create("ball.png");
    ball->setPosition(ballPoint);
    this->addChild(ball, kZOrder_Ball);
    
    // ボールの物理構造
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(ballPoint.x / PTM_RATIO, ballPoint.y / PTM_RATIO);
    ballBodyDef.userData = ball;
    b2Body* body = world->CreateBody(&ballBodyDef);
    
    gbox2d::GB2ShapeCache* sc = gbox2d::GB2ShapeCache::sharedGB2ShapeCache();
    sc->addFixturesToBody(body, "ball");
    ball->setAnchorPoint(sc->anchorPointForShape("ball"));
}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    Director* pDirector = Director::getInstance();
    Point location = pDirector->convertToGL(touch->getLocationInView());
    
    if (location.y > winSize.height / 2)
        // 画面上部をタップ
        createBall();
    
    else if (location.x > winSize.width / 2)
        // 画面下部の左をタップ
        rightFlipperBody->ApplyTorque(-1, true);
    
    else
        // 画面下部の右をタップ
        leftFlipperBody->ApplyTorque(1, true);
    
    return true;
}

void GameScene::createScore()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    // 得点の表示
    score = LabelTTF::create("0", "", SCORE_FONT_SIZE);
    score->setPosition(Vec2(winSize.width * 0.5, winSize.height * 0.18));
    this->addChild(score, kZOrder_Score);
}

void GameScene::updateScore()
{
    String* string = String::createWithFormat("%d", scorePoint);
    score->setString(string->getCString());
}

void GameScene::createReset()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    // スコアの表示
    MenuItemImage* reset = MenuItemImage::create("button_reset1.png", "button_reset2.png", this, menu_selector(GameScene::tapReset));
    reset->setPosition(Vec2(winSize.width * 0.8, winSize.height * 0.94));
    
    Menu* menu = Menu::create(reset, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, kZOrder_Button);
}

void GameScene::tapReset(Ref* target)
{
    Scene* scene = GameScene::scene();
    Director::getInstance()->replaceScene(scene);
}
