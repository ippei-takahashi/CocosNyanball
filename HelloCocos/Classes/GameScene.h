//
//  GameScene.h
//  HelloCocos
//
//  Created by 高橋一平 on 2015/05/17.
//
//

#ifndef HelloCocos_GameScene_h
#define HelloCocos_GameScene_h

#include "cocos2d.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 8

#define PNG_BACKGROUND "background.png"

class GameScene: public cocos2d::Layer
{
protected:
    enum kTag
    {
        kTagTabBackground = 1,
        kTagBaseBlock = 10000,
    };
    
    enum kZOrder
    {
        kZOrderBackground,
        kZOrderBlock,
    };
    
    cocos2d::Sprite* m_background;
    void showBackground();
    
    float m_blockSize;
    std::map<kBlock, std::list<int>> m_BlockTags;
    void initForVariables();
    void showBlock();
    cocos2d::Point getPosition(int posIndexX, int posIndexY);
    int getTag(int posIndexX, int posIndexY);
    
    void getTouchBlockTag(cocos2d::Point touchPoint, int &tag, kBlock &blockType);
    std::list<int> getSameColorBlockTags(int baseTag, kBlock blockType);
    void removeBlock(std::list<int> blockTags, kBlock blockType);
    bool hasSameColorBlock(std::list<int> blockTagList, int searchBlockTag);
    
public:
    virtual bool init();
    static cocos2d::Scene* scene();
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
    virtual void onTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
};

#endif
