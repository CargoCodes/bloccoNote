//
// Created by viato on 12/05/2022.
//

#include "KvK.h"

void KvK::startingContent() {
    if (this->filePath.substr(this->filePath.length() - 4, this->filePath.length()) != ".kvk")
        throw runtime_error("File extension must be \".kvk\"");
    else {
        file.open(this->filePath, ios::in);
        if(file.is_open()){
            string fileContent;
            while(getline(file, fileContent)){
                this->content += fileContent + "\n";
            }
            file.close();
        } else {
            this->content = "<#\n#>";
            file.open(this->filePath, ios::out);
            if(file.is_open()){
                file << this->content;
                file.close();
            }
        }
    }
}

map<string, map<string, string>> KvK::getClass_() {
    map<string, map<string, string>> tmpDict;

    this->pos += 5;

    while(this->text[this->pos] == ' ')
        this->pos += 1;

    if(this->text[this->pos] == '"'){
        this->pos += 1;
        string className;

        while(this->text[this->pos] != '"'){
            className += this->text[this->pos];
            this->pos += 1;
        }

        while(this->text[this->pos] == ' ')
            this->pos += 1;

        map<string, string> insideDict;
        if(this->text.substr(this->pos, this->pos+3) == "::>"){
            this->pos += 3;

            while(this->text.substr(this->pos, this->text.length()) != "#>" and this->text.substr(this->pos, this->pos+5) != "class"){
                this->nullAdvancement();

                if(this->text[this->pos] == '('){
                    vector<string> returnVector = this->getAttr_();
                    insideDict.insert(pair<string, string>(returnVector[0], returnVector[1]));
                    this->pos += 1;
                }

                tmpDict.insert(pair<string, map<string, string>>(className, insideDict));
            }
            return tmpDict;
        } else
            throw runtime_error("\"::>\" must follow class name");
    } else
        throw runtime_error("Class name bust be wrapped with \"\"");
}

vector<string> KvK::getAttr_() {
    vector<string> res;
    string attrName;

    this->pos += 1;
    this->nullAdvancement();

    while(this->text[this->pos] != ')'){
        attrName += this->text[this->pos];
        this->pos += 1;
    }

    this->pos += 1;
    this->nullAdvancement();

    if(this->text.substr(this->pos, this->pos+2) == "->"){
        this->pos += 2;

        while(this->text[this->pos] == ' ')
            this->pos += 1;

        if(this->text[this->pos] == '"'){
            string attr;
            this->pos += 1;

            while(this->text[this->pos] != '"'){
                attr += this->text[this->pos];
                this->pos += 1;
            }

            res.push_back(attrName);
            res.push_back(attr);

            return res;
        } else
            throw runtime_error("Attribute must be wrapped with \"\"");
    } else
        throw runtime_error("\"->\" must between attribute name and attribute");
}

vector<map<string, map<string, string>>> KvK::read() {
    this->pos = 0;
    file.open(this->filePath, ios::in);
    if(file.is_open()) {
        string fileContent;
        while (getline(file, fileContent)) {
            this->text += fileContent + "\n";
        }
        file.close();
        vector<map<string, map<string, string>>> res;
        if (this->text.substr(this->pos, this->pos+2) == "<#"){
            this->pos += 2;
            while(this->pos < this->text.length()){
                this->nullAdvancement();
                if(this->text.substr(this->pos, this->pos+5) == "class"){
                    map<string, map<string, string>> point = getClass_();
                    res.push_back(point);
                }
                if(this->text.substr(this->pos, this->text.length()) == "#>")
                    break;
            }
            return res;
        } else {
            throw runtime_error("File not starting with <#");
        }
    } else
        throw runtime_error("Can't open file \"" + this->filePath + "\"");
}

map<string, string> KvK::getClass(const string &className) {
    this->pos = 0;
    auto fileContent = this->read();

    try {
        for(const auto& classCont:fileContent){
            for(const auto& classname:classCont){
                if(classname.first == className){
                    return classname.second;
                }
            }
        }
    } catch (...){
        map<string, string> empty;
        return empty;
    }
    map<string, string> empty;
    return empty;
}

string KvK::getAttr(const string &className, const string &attrName) {
    this->pos = 0;
    auto fileContent = this->read();

    try {
        for(const auto& classCont:fileContent){
            for(const auto& classname:classCont){
                if(classname.first == className){
                    auto attrs = classname.second;
                    for(const auto& attr:attrs){
                        if(attr.first == attrName)
                            return attr.second;
                    }
                }
            }
        }
    } catch (...){
        return "";
    }
    return "";
}

bool KvK::addClass(const string &className) {
    string oldContent = this->content.substr(0, this->content.length()-2);
    string eof = "#>";

    this->content = oldContent + "    class \"" + className + "\" ::>\n" + eof;

    file.open(this->filePath, ios::out);
    if(file.is_open()){
        file << this->content;
        file.close();

        return true;
    }
    return false;
}

bool KvK::addAttr(const string &className, const string &attrName, const string &attrContent) {
    try {
        int index = this->content.find("class \"" + className + "\" ::>");

        int endIndex = index+ ("class \"" + className + "\" ::>").length();

        this->content = this->content.substr(0, endIndex) + "        (" + attrName + ") -> \"" + attrContent + "\""
                + this->content.substr(endIndex, this->content.length());

        file.open(this->filePath, ios::out);
        if(file.is_open()){
            file << this->content;
            file.close();

            return true;
        }
        return false;

    } catch (...) {
        throw ClassNotFoundError("Class not found");
    }
}

bool KvK::editClass(const string &className, const string &newClassName) {
    int startIndex = this->content.find("class \"" + className + "\" ::>");
    if(startIndex) {
        int endIndex = startIndex + ("class \"" + className + "\" ::>").length();

        this->content = this->content.substr(0, startIndex) + "class \"" + newClassName + "\" ::>"
                + this->content.substr(endIndex, this->content.length());

        if(file.is_open()){
            file << this->content;
            file.close();

            return true;
        }
        return false;
    } else
        throw ClassNotFoundError("Class \"" + className + "\" not found");
}

bool KvK::editAttr(const string &className, const string &attrName, const string &newAttrName,
                   const string &attrContent) {
    int classIndex = this->content.find("class \"" + className + "\" ::>");
    if (classIndex) {
        string preClass = this->content.substr(0, classIndex);
        string tmp = this->content.substr(classIndex+5, this->content.length());

        int eofClassIndex = tmp.find("class");
        int endClassIndex = tmp.find("#>");

        int endIndex;

        if(eofClassIndex)
            endIndex = eofClassIndex;
        else if(endClassIndex)
            endIndex = endClassIndex;

        string isolatedClass = this->content.substr(classIndex, endClassIndex + classIndex + 5);

        string afterClass = tmp.substr(endClassIndex, tmp.length());

        int oldAttrIndex = isolatedClass.find(attrName);

        if(oldAttrIndex) {
            isolatedClass = isolatedClass.substr(0, oldAttrIndex) + newAttrName +
                            isolatedClass.substr(oldAttrIndex + attrName.length(),
                            isolatedClass.length());

            if(not attrContent.empty()){
                int virgStart = oldAttrIndex;

                while(isolatedClass[virgStart] != '"')
                    virgStart += 1;

                int virgEnd = virgStart+1;
                while(isolatedClass[virgEnd] != '"')
                    virgEnd += 1;

                isolatedClass = isolatedClass.substr(0, virgStart+1) + attrContent
                                    + isolatedClass.substr(virgEnd, isolatedClass.length());
            }
            this->content = preClass + isolatedClass + afterClass;

            if(file.is_open()){
                file << this->content;
                file.close();

                return true;
            }
            return false;

        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" of class \""
                                                                + className + "\" not found");
    } else
        throw ClassNotFoundError("Class \"" + className + "\" not found");
}

bool KvK::removeClass(const string &className) {
    int classIndex = this->content.find("    class \"" + className + "\" ::>");
    if (classIndex) {
        string preClass = this->content.substr(0, classIndex);
        string tmp = this->content.substr(classIndex+5, this->content.length());

        int endClassIndex = tmp.find("class");
        int eofClassIndex = tmp.find("#>");

        int endIndex;
        string afterClass;

        if(endClassIndex) {
            endIndex = endClassIndex;
            afterClass = tmp.substr(endClassIndex, tmp.length());
        }
        else if(eofClassIndex) {
            endIndex = eofClassIndex;
            afterClass = "#>";
        }

        this->content = preClass + afterClass;

        if(file.is_open()){
            file << this->content;
            file.close();

            return true;
        }
        return false;
    } else
        throw ClassNotFoundError("Class \"" + className + "\" not found");
}

bool KvK::removeAttr(const string &className, const string &attrName) {
    int classIndex = this->content.find("class \"" + className + "\" ::>");
    if (classIndex) {
        string preClass = this->content.substr(0, classIndex);
        string tmp = this->content.substr(classIndex+5, this->content.length());

        int eofClassIndex = tmp.find("class");
        int endClassIndex = tmp.find("#>");

        int endIndex;

        if(eofClassIndex)
            endIndex = eofClassIndex;
        else if(endClassIndex)
            endIndex = endClassIndex;

        string isolatedClass = this->content.substr(classIndex, endClassIndex + classIndex + 5);

        string afterClass = tmp.substr(endClassIndex, tmp.length());

        int oldAttrIndex = isolatedClass.find(attrName);

        if(oldAttrIndex) {
            tmp = isolatedClass.substr(0, oldAttrIndex-1)
                + isolatedClass.substr(oldAttrIndex + attrName.length(),
                                       isolatedClass.length());


            int virgStart = oldAttrIndex;

            while(isolatedClass[virgStart] != '"')
                virgStart += 1;

            int virgEnd = virgStart+1;
            while(isolatedClass[virgEnd] != '"')
                virgEnd += 1;

            isolatedClass = isolatedClass.substr(0, oldAttrIndex-10)
                            + isolatedClass.substr(virgEnd+1, isolatedClass.length());

            this->content = preClass + isolatedClass + afterClass;

            if(file.is_open()){
                file << this->content;
                file.close();

                return true;
            }
            return false;

        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" of class \""
                                         + className + "\" not found");
    } else
        throw ClassNotFoundError("Class \"" + className + "\" not found");
}

bool KvK::isEmpty() {
    string actualContent = this->content;
    auto contentList = split(actualContent, ' ');

    int i = 0;
    for(const auto& element:contentList){
        if(element.empty() or element == " "){
            contentList = pop(contentList, i);
        }
        i += 1;
    }
    try{
        if(contentList[0] == "<#" and contentList[1] == "#>")
            return true;
        return false;
    } catch (...) {
        if(contentList.empty())
            return true;
        return false;
    }
}