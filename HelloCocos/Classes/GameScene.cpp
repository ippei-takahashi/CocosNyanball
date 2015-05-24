
//
//  GameScene.cpp
//  HelloCocos
//
//  Created by 高橋一平 on 2015/05/17.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSprite.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    initForVariables();
    
    showBackground();
    
    showBlock();
    
    return true;
}

void GameScene::initForVariables()
{
    srand((unsigned)time(NULL));
    
    BlockSprite* pBlock = BlockSprite::createWithBlockType(kBlockRed);
    m_blockSize = pBlock->getContentSize().height;
}

Point GameScene::getPosition(int posIndexX, int posIndexY)
{
    float offsetX = m_background->getContentSize().width * 0.168;
    float offsetY = m_background->getContentSize().height * 0.029;
    return Point((posIndexX + 0.5) * m_blockSize + offsetX, (posIndexY + 0.5) * m_blockSize + offsetY);
}

int GameScene::getTag(int posIndexX, int posIndexY)
{
    return kTagBaseBlock + posIndexX * 100 + posIndexY;
}

void GameScene::showBlock()
{
    for (int x = 0; x < MAX_BLOCK_X; x++) {
        for (int y = 0; y < MAX_BLOCK_Y; y++) {
            kBlock blockType = (kBlock)(rand() % kBlockCount);
            
            int tag = getTag(x, y);
            m_BlockTags[blockType].push_back(tag);
            
            BlockSprite* pBlock = BlockSprite::createWithBlockType(blockType);
            pBlock->setPosition(getPosition(x, y));
            m_background->addChild(pBlock, kZOrderBlock, tag);
        }
    }
}

void GameScene::showBackground()
{
    Size winSize = Director::getInstance()->getWinSize();
    
    m_background = Sprite::create(PNG_BACKGROUND);
    m_background->setPosition(winSize.width / 2, winSize.height / 2);
    addChild(m_background, kZOrderBackground, kTagTabBackground);
}

Scene* GameScene::scene()
{
    Scene* scene = Scene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{
}

