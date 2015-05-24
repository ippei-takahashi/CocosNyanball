//
//  BlockSprite.cpp
//  HelloCocos
//
//  Created by 高橋一平 on 2015/05/17.
//
//

#include "BlockSprite.h"

BlockSprite::BlockSprite()
{
}

BlockSprite::~BlockSprite()
{
}

BlockSprite* BlockSprite::createWithBlockType(kBlock blockType)
{
    BlockSprite* pRet = new BlockSprite();
    if (pRet && pRet->initWithBlockType(blockType))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool BlockSprite::initWithBlockType(kBlock blockType)
{
    if (!Sprite::initWithFile(getBlockImageFileName(blockType)))
    {
        return false;
    }
    
    m_BlockType = blockType;
    
    return true;
}

const char* BlockSprite::getBlockImageFileName(kBlock blockType)
{
    switch (blockType) {
        case kBlockRed:
            return "red.png";
            break;
            
        case kBlockBlue:
            return "blue.png";
            break;
        
        case kBlockYellow:
            return "yellow.png";
            break;
        
        case kBlockGreen:
            return "green.png";
            break;
        
        case kBlockGray:
            return "gray.png";
            break;
            
        default:
            return "";
    }
}