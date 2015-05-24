//
//  BlockSprite.h
//  HelloCocos
//
//  Created by 高橋一平 on 2015/05/17.
//
//

#ifndef __HelloCocos__BlockSprite__
#define __HelloCocos__BlockSprite__

#include "cocos2d.h"
#include "Config.h"

class BlockSprite: public cocos2d::Sprite
{
protected:
    const char* getBlockImageFileName(kBlock blockType);
    
public:
    CC_SYNTHESIZE(kBlock, m_BlockType, BlockType);
    
    BlockSprite();
    virtual ~BlockSprite();
    
    virtual bool initWithBlockType(kBlock blockType);
    static BlockSprite* createWithBlockType(kBlock blockType);
    
};

#endif /* defined(__HelloCocos__BlockSprite__) */
