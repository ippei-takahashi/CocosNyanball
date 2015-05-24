#ifndef __APPMACROS_H__
#define __APPMACROS_H__

#include "cocos2d.h"

typedef struct tagResource
{
    cocos2d::Size size;
    char directory[100];
} Resource;

static Resource smallResource = { cocos2d::Size( 384, 512), "S"};
static Resource mediumResource = { cocos2d::Size( 768, 1024), "M"};
static Resource largeResource = { cocos2d::Size(1536, 2048), "L"};

static cocos2d::Size designResolutionSize = cocos2d::Size(768, 1024);

#define SCORE_FONT_SIZE (Director::getInstance()->getOpenGLView()->getDesignResolutionSize().width / mediumResource.size.width * 48)

#endif // __APPMACROS_H__