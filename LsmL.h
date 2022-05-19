#ifndef LSMLLIB_LSML_H
#define LSMLLIB_LSML_H


#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class LsmL {
public:
    explicit LsmL(const string& filePath) : filePath(filePath) {
        this->startingContent();
    }

    LsmL(const LsmL& other) {
        this->filePath = other.filePath;
        this->content = other.content;
    }

    LsmL& operator=(const LsmL& other) {
        this->filePath = other.filePath;
        this->content = other.content;
        return *this;
    }

    vector<map<string, map<string, string>>> read();

    void write(const vector<map<string, map<string, string>>>& content);

    map<string, string> getField(const string &fieldName);

    string getAttr(const string &fieldName, const string &attrName);

    bool addField(const string& fieldName);

    bool addAttr(const string& fieldName, const string& attrName, const string&attrContent);

    bool editAttr(const string& fieldName, const string& attrName, const string& newAttrName, const string& attrContent="");

    bool editField(const string& fieldName, const string& newFieldName);

    bool removeField(const string& fieldName);

    bool removeAttr(const string& fieldName, const string& attrName);

    bool isEmpty();

private:
    string filePath;
    int pos = 0;

    string content;
    fstream file;
    string text;

    void startingContent();

    map<string, map<string, string>> getField_();

    vector<string> getAttr_();

    void nullAdvancement() {
        while(this->text[this->pos] == ' ' or this->text[this->pos] == '\t' or this->text[this->pos] == '\n')
            this->pos += 1;
    }

    static vector<string> split(string str, char separator){
        vector<string> list;

        while(str.find(separator)){
            list.push_back(str.substr(0, str.find(separator)));
            str = str.substr(str.find(separator)+1, str.length());
        }

        return list;
    }

    static vector<string> pop(const vector<string> &list, int index) {
        vector<string> returnList;
        for(int i = 0; i < list.size(); i++){
            if(i != index){
                returnList.push_back(list[i]);
            }
        }
        return returnList;
    }

    class FieldNotFoundError : runtime_error {
    public:
        explicit FieldNotFoundError(const string& message) : runtime_error(message.c_str()) {
            cerr << message << endl;
        }
    };

    class AttributeNotFoundError : runtime_error {
    public:
        explicit AttributeNotFoundError(const string& message) : runtime_error(message) {
            cerr << message << endl;
        }
    };

    static string subString(const string& string, int startIndex, int endIndex) {
        if(startIndex >= 0 and startIndex <= string.length() and endIndex >= 0 and endIndex <= string.length()){
            std::string returnstring;

            for(int i = startIndex; i < endIndex; i++){
                returnstring += string[i];
            }
            return returnstring;
        } else
            throw std::out_of_range("Index out of range");
    }
};

#endif // LSMLLIB_LSML_H
