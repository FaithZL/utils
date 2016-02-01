//
//  Data.cpp
//  DontCrash
//
//  Created by SATAN_Z on 16/1/31.
//
//

#include "FileData.hpp"
#include "../constant.h"
#include "iostream"
#include <fstream>


FileData::FileData():
_fileName(""){
}

FileData::~FileData(){
}


bool FileData::parseFile(){
    if (_fileName == "") {
        return false;
    }
    
    auto fileUtils = cocos2d::FileUtils::getInstance();
    auto str = fileUtils->getStringFromFile(_fileName);
    Json::Reader reader;
    reader.parse(str, _value, true);
    return true;
}

void FileData::saveData(){
    std::ofstream fout;
    fout.open(_fileName);
    Json::StyledWriter writer;
    fout << writer.write(_value) << std::endl;
    fout.close();
}

Json::Value FileData::getData(){
    return _value;
}

bool FileData::init()
{
    return true;
}