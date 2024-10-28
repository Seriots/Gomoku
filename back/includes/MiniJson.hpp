#pragma once

#include <string>
#include <map>
#include <vector>

#include "structs.hpp"

class MiniJson {

    private:
        std::map<std::string, std::string> _stringElem;
        std::map<std::string, int> _intElem;
        std::map<std::string, std::vector<int> > _intListElem;
        std::map<std::string, std::vector<t_stone> > _stoneListElem;

    public:
        MiniJson();
        ~MiniJson();
        void parse(std::string json);

        int getInt(std::string key);
        std::string getStr(std::string key);
        std::vector<int> getIntList(std::string key);
        std::vector<t_stone> getStoneList(std::string key);
};