#include <iostream>
#include <type_traits>
#include <algorithm> 

#include "MiniJson.hpp"
#include "structs.hpp"

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

bool isInt(std::string &s) {
    for (char &c: s) {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

bool isIntList(std::string &s) {
    if (s.size() < 2)
        return false;
    if (s[0] == '[' && s[1] != '{')
        return true;
    return false;
}

bool isStoneList(std::string &s) {
    if (s.size() < 2)
        return false;
    if (s[0] == '[' && s[1] == '{')
        return true;
    return false;
}

std::vector<int>    stringToIntList(std::string &s) {
    std::vector<int> split;
    size_t pos = 0;
    size_t end = 0;

    s = s.substr(1, s.size() - 2);

    while ((end = s.find(",", pos)) != std::string::npos) {
        split.push_back(std::stoi(s.substr(pos, end - pos)));
        pos = end + 1;
    }
    //std::string last = s.substr(pos, s.size() - pos);
    //if (isInt(last))
    //    split.push_back(std::stoi(last));
    return split;
}

std::vector<t_stone>    stringToStoneList(std::string &s) {
    std::vector<t_stone>    out;
    std::vector<std::string> split;
    size_t pos = 0;
    size_t end = 0;

    s = s.substr(1, s.size() - 2);

    while ((end = s.find("},", pos)) != std::string::npos) {
        split.push_back(s.substr(pos, end - pos + 2));
        pos = end + 3;
    }
    split.push_back(s.substr(pos, s.size() - pos));

    for (std::string &elem : split) {
        int pos = elem.find(",");
        std::string left = elem.substr(0, pos);
        std::string right = elem.substr(pos+9);

        t_stone stone;
        stone.pos = std::stoi(left.substr(left.find("\"pos\":") + 6));
        
        out.push_back(stone);
    }
    return out;
}

MiniJson::MiniJson() {
}

MiniJson::~MiniJson() {
}

void MiniJson::parse(std::string json) {
    if (json.size() < 2)
        return;
    json = json.substr(1, json.size() - 2);
    trim(json);

    std::vector<std::string> json_split;
    size_t pos = 0;
    size_t end = 0;

    while ((end = json.find(",\n", pos)) != std::string::npos) {
        json_split.push_back(json.substr(pos, end - pos));
        pos = end + 1;
    }
    json_split.push_back(json.substr(pos, json.size() - pos));

    for (std::string &elem: json_split) {
        trim(elem);
        int pos = elem.find(":", 0);
        std::string left = elem.substr(1, pos - 2);
        std::string right = elem.substr(pos + 1, elem.size() - pos);
        if (isInt(right))
            _intElem[left] = std::stoi(right);
        else if (isIntList(right))
            _intListElem[left] = stringToIntList(right);
        else if (isStoneList(right))
            _stoneListElem[left] = stringToStoneList(right);
        else
            _stringElem[left] = right; 
    }
}

int MiniJson::getInt(std::string key) {
    return _intElem[key];
};
std::string MiniJson::getStr(std::string key) {
    return _stringElem[key];
};
std::vector<int> MiniJson::getIntList(std::string key) {
    return _intListElem[key];
};
std::vector<t_stone> MiniJson::getStoneList(std::string key) {
    return _stoneListElem[key];
};