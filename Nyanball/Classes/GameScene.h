#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

class GamePhysicsContactListener : public b2ContactListener
{
protected:
    cocos2d::Ref* m_target;
    cocos2d::SEL_CallFunc m_selector;
    
public:
    GamePhysicsContactListener(cocos2d::Ref* target, cocos2d::SEL_CallFunc selector);
    void BeginContact(b2Contact* contact);
};

class GameScene : public cocos2d::Layer
{
protected:
    enum kTag
    {
        kTagBackground = 1,
    };
    
    enum kZOrder
    {
        kZOrder_Background = 1,
        kZOrder_Score,
        kZOrder_Flipper,
        kZOrder_Ball,
        kZOrder_Button,
    };
    
    void createBackground();
    void createButton();
    void createFlipper();

    b2World* world;
    void initPhysics();
    
    b2Body* bgBody;
    
    void createBall();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);

    b2Body* leftFlipperBody;
    b2Body* rightFlipperBody;
    
    cocos2d::LabelTTF* score;
    GamePhysicsContactListener* gamePhysicsContactListener;
    void createScore();
    void updateScore();
    
    int ballCount;
    void createReset();
    void tapReset(Ref* target);
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
    
    void update(float dt);
};

#endif // __GAME_SCENE_H__