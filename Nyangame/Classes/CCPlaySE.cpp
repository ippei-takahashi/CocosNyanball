//
//  CCPlaySE.cpp
//  HelloCocos
//
//  Created by 高橋一平 on 2015/05/17.
//
//

#include "CCPlaySE.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCPlaySE::CCPlaySE(std::string sound)
{
    m_sound = sound;
}

CCPlaySE* CCPlaySE::create(std::string sound)
{
    CCPlaySE* pRet = new CCPlaySE(sound);
    
    if (pRet) {
        pRet->autorelease();
    }
    
    return pRet;
}

void CCPlaySE::update(float time)
{
    CC_UNUSED_PARAM(time);
    SimpleAudioEngine::sharedEngine()->playEffect(m_sound.c_str());
}

CCFiniteTimeAction* CCPlaySE::reverse()
{
    return (CCFiniteTimeAction *)(CCPlaySE::create(m_sound));
}

CCObject* CCPlaySE::copyWithZone(CCZone* pZone)
{
    CCZone* pNewZone = NULL;
    CCPlaySE* pRet = NULL;
    if (pZone && pZone->m_pCopyObject)
    {
        pRet = (CCPlaySE*)(pZone->m_CopyObject)
    }
    else
    {
        pRet = new CCPlaySE(m_sound);
        pZone = pNewZone = new CCZone(pRet);
    }
    
    CCActionInstant::copyWithZone(pZone);
    CC_SAFE_DELETE(pNewZone);
    return pRet;
}