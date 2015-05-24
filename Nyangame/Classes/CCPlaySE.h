//
//  CCPlaySE.h
//  HelloCocos
//
//  Created by 高橋一平 on 2015/05/17.
//
//

#ifndef HelloCocos_CCPlaySE_h
#define HelloCocos_CCPlaySE_h

#include "cocos2d.h"

class CCPlaySE: public cocos2d::CCActionInstant
{
public:
    CCPlaySE(std::string sound);
    virtual ~CCPlaySE(){}
    
    virtual void update(float time);
    virtual cocos2d::CCFiniteTimeAction* reverse(void);
    virtual cocos2d::CCObject* copyWithZone(cocos2d::CCZone* pZone);
    
public:
    static CCPlaySE* create(std::string sound);
    
protected:
    std::string m_sound;
};


#endif
