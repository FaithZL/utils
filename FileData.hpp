//
//  Data.hpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#ifndef Data_hpp
#define Data_hpp

#include "cocos2d.h"
#include "json/json.h"

class FileData {
    
public:
    FileData();
    ~FileData();
    
    virtual bool init();
    
    Json::Value getData();
    
    // fileName is absolute path
    CC_SYNTHESIZE(std::string, _fileName, FileName);
    
    CC_SYNTHESIZE_READONLY(Json::Value , _value , Value);
    
    void saveData();
    
    bool parseFile();
    
};

#endif /* Data_hpp */
