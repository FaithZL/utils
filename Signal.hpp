//
//  Signal.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/23.
//
//

#ifndef Signal_hpp
#define Signal_hpp

#include "cocos2d.h"

typedef bool (cocos2d::Ref::*Sig_SEL)(va_list args);

#define TO_SIG_SEL(_SELECTOR) static_cast<Sig_SEL>(&_SELECTOR)

typedef cocos2d::Ref * Sig_Target;

typedef struct{
    
    Sig_Target pTarget;
    
    Sig_SEL pSelector;
    //the smaller the number is, the higher the priority level is.
    int priority;
    
} Sig_struct;

class Signal :public cocos2d::Ref{
    
public:
    Signal();
    
    ~Signal();
    
    virtual bool init();
    
    void registerEvent(std::string eventName , Sig_Target pTarget , Sig_SEL pSelector ,int priority);
    
    void dispatchEvent(std::string eventName , ...);
    
    void removeEvent(std::string eventName , Sig_Target pTarget , Sig_SEL pSelector);
    
    void clearEvent(std::string eventName);
    
    void clear();
    
    CREATE_FUNC(Signal);
    
protected:
    
    std::map<std::string , std::vector<Sig_struct>> _structMap;
    
};

#endif /* Signal_hpp */
