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

class PlaySE: public cocos2d::ActionInstant
{
public:
    PlaySE(std::string sound);
    virtual ~PlaySE(){}
    
    virtual void update(float time);
    virtual FiniteTimeAction* reverse(void);
    
public:
    static PlaySE* create(std::string sound);
    
protected:
    std::string m_sound;
};


#endif
