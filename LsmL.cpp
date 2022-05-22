#include "LsmL.h"

void LsmL::startingContent() {
    if (subString(this->filePath, static_cast<int>(this->filePath.length()) -5, static_cast<int>(this->filePath.length())) != ".lsml") // checks the extension of the file
        throw runtime_error("File extension must be \".lsml\"");
    else {
        file.open(this->filePath, ios::in); // tries to open file to read the content_

        if(file.is_open()){
            this->empty = false;
            string fileContent;
            while(getline(file, fileContent)){
                this->content += fileContent + "\n"; // reads the content_ and stores it in "content_"
            }
            file.close();
        } else { // if it is impossible to read
            this->empty = true;
            this->content = "<#\n#>"; // sets content_ to the empty standard
            file.open(this->filePath, ios::out);

            if(file.is_open()){
                file << this->content; // writes the standard empty content_ in the file
                file.close();
            }
        }
    }
}

map<string, map<string, string>> LsmL::getField_() {
    map<string, map<string, string>> tmpDict; // content_ of the field variable

    this->pos += 3;

    while(this->text[this->pos] == ' ') // skips blank spaces
        this->pos += 1;

    if(this->text[this->pos] == '"'){ // finds the opening double quotes for field name
        this->pos += 1;
        string fieldName;

        while(this->text[this->pos] != '"'){ // scans until the following double quotes to read field name
            fieldName += this->text[this->pos];
            this->pos += 1;
        }
        this->pos += 1;

        while(this->text[this->pos] == ' ') // skips blank spaces
            this->pos += 1;

        map<string, string> insideDict; // map for attributes
        if(this->text.substr(this->pos, 3) == "::>"){ // looks for the attribute list opening tag
            this->pos += 3;

            while(subString(this->text, this->pos, this->text.length()-1) != "#>"
                  and this->text.substr(this->pos, 3) != "[$]"){ // scans until it finds EOF or new field
                this->nullAdvancement(); // skips blank spaces, blank lines and tabs

                if(this->text[this->pos] == '('){ // looks for attribute opening parentheses
                    vector<string> returnVector = this->getAttr_(); // starts attribute reading, one at the time
                    insideDict.insert(pair<string, string>(returnVector[0], returnVector[1])); // stores the attribute in the map
                    this->pos += 1;
                }

                tmpDict.insert(pair<string, map<string, string>>(fieldName, insideDict)); // pushes the field in the return map
            }
            return tmpDict;
        } else
            throw runtime_error("\"::>\" must follow field name");
    } else
        throw runtime_error("Field name bust be wrapped with \"\"");
}

vector<string> LsmL::getAttr_() {
    vector<string> res; // return variable
    string attrName;

    this->pos += 1;
    this->nullAdvancement(); // skips blank spaces, blank lines and tabs

    while(this->text[this->pos] != ')'){ // looks for the ending attribute name tag
        attrName += this->text[this->pos];
        this->pos += 1;
    }

    this->pos += 1;
    this->nullAdvancement(); // skips lbank lines, blank spaces and tabs

    if(this->text.substr(this->pos, 2) == "->"){ // looks for the appartenence tag
        this->pos += 2;

        while(this->text[this->pos] == ' ') // skips blank spaces
            this->pos += 1;

        if(this->text[this->pos] == '"'){ // looks for the attribute content_ opening double quote
            string attr;
            this->pos += 1;

            while(this->text[this->pos] != '"'){ // looks for the attribute content_ closing double quote
                attr += this->text[this->pos];
                this->pos += 1;
            }

            res.push_back(attrName);
            res.push_back(attr);

            return res; // returns attribute name and content_
        } else
            throw runtime_error("Attribute must be wrapped with \"\"");
    } else
        throw runtime_error("\"->\" must between attribute name and attribute");
}

vector<map<string, map<string, string>>> LsmL::read() {
    this->pos = 0;
    file.open(this->filePath, ios::in);

    if(file.is_open()) { // reads the content_ of the file
        string fileContent;
        while (getline(file, fileContent)) {
            this->text += fileContent + "\n";
        }
        file.close();

        vector<map<string, map<string, string>>> res; // return variable
        if (this->text.substr(this->pos, 2) == "<#"){ // looks for SOF

            this->pos += 2;
            while(this->pos < this->text.length()
                  and subString(this->text, this->pos, this->text.length()-1) != "#>"){ // scans until the end of the file
                this->nullAdvancement(); // skips blank spaces, blank lines and tabs

                if(this->text.substr(this->pos, 3) == "[$]"){ // looks for the field tag

                    map<string, map<string, string>> point = getField_(); // starts the field reding process
                    res.push_back(point); // stores the field
                }
                if(subString(this->text, this->pos, this->text.length()-1) == "#>") // if it find the EOF, stops scan
                    break;
            }
            return res;
        } else {
            throw runtime_error("File not starting with <#");
        }
    } else
        throw runtime_error("Can't open file \"" + this->filePath + "\"");
}

bool LsmL::addField(const string &fieldName) {
    file.open(this->filePath_, ios::in);
    if (file.is_open()) {
        string currentContent;
        string fileContent;
        while (getline(file, fileContent)) {
            currentContent += fileContent + "\n";
        }
        file.close();
        int fieldIndex = static_cast<int>(currentContent.find("    [$] \"" + fieldName + "\" ::>"));
        if (fieldIndex < 0) { // cheks if the field already exists
            string oldContent = subString(currentContent, 0,
                                          static_cast<int>(currentContent.length()) - 3); // takes teh content_ but removes the EOF
            string eof = "#>";

            this->content =
                    oldContent + "    [$] \"" + fieldName + "\" ::>\n" + eof; // adds the new field and then the EOF
            return writeFile(this->content);
        }
        return false;
    }
    return false;
}

bool LsmL::addAttr(const string &fieldName, const string &attrName, const string &attrContent) {
    this->content = readFile();
    int index = this->content.find("[$] \"" + fieldName + "\" ::>");
    if (index > 0) { // checks if the field exists
        int endIndex = index + ("[$] \"" + fieldName + "\" ::>").length() + 1; // takes teh index of the field

        int endFieldIndex = endIndex + 1;
        try { // scans until EOF or new field
            while (this->content.substr(endFieldIndex, 2) != "#>"
                   and this->content.substr(endFieldIndex, 3) != "[$]")
                endFieldIndex += 1;
        } catch (...) {
            endFieldIndex = this->content.length() - 2;
        }

        string isolatedField = subString(this->content, index, endFieldIndex); // isolates the wanted field
        int attrIndex = isolatedField.find("        (" + attrName + ") ->");
        if (attrIndex < 0) { // checks if attribute already exists
            this->content = subString(this->content, 0, endIndex) + "        (" + attrName + ") -> \""
                            + attrContent + "\"\n"
                            + subString(this->content, endIndex, this->content.length()); // adds the attribute
            return writeFile(this->content);
        }
        return false;
    } else
        throw FieldNotFoundError("Field not found");
}

bool LsmL::editField(const string &fieldName, const string &newFieldName) {
    this->content = readFile();
    int startIndex = this->content.find("[$] \"" + fieldName + "\" ::>");
    if(startIndex > 0) { // checks if the field exists
        int endIndex = startIndex + ("[$] \"" + fieldName + "\" ::>").length(); // takes the ending index of teh field declaration

        this->content = this->content.substr(0, startIndex) + "[$] \"" + newFieldName + "\" ::>"
                        + subString(this->content, endIndex, this->content.length()); // edits the field name
        return writeFile(this->content);
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::editAttr(const string &fieldName, const string &attrName, const string &newAttrName, const string &attrContent) {
    this->content = readFile();
    int fieldIndex = this->content.find("[$] \"" + fieldName + "\" ::>");
    if (fieldIndex > 0) { // checks if the field exists
        string preField = this->content.substr(0, fieldIndex); // isolates what's before the field
        string tmp = subString(this->content, fieldIndex+5, this->content.length());

        int newFieldIndex = tmp.find("[$]");
        int eofFieldIndex = tmp.find("#>");

        int endIndex;
        if(newFieldIndex > 0)
            endIndex = newFieldIndex;
        else
            endIndex = eofFieldIndex;

        string isolatedField = subString(this->content, fieldIndex, endIndex+fieldIndex+5); // isolates the field
        string afterField = tmp.substr(endIndex, tmp.length()); // isolates what's after the field

        int oldAttrIndex = isolatedField.find(attrName);
        if(oldAttrIndex > 0) { // checks if the attribute exists
            isolatedField = isolatedField.substr(0, oldAttrIndex) + newAttrName + // updates the attribute name
                            subString(isolatedField, oldAttrIndex+attrName.length(), isolatedField.length());

            if(not attrContent.empty()){ // if attribute name is not empty
                int virgStart = oldAttrIndex;

                while(isolatedField[virgStart] != '"')
                    virgStart += 1;

                int virgEnd = virgStart+1;
                while(isolatedField[virgEnd] != '"')
                    virgEnd += 1;

                isolatedField = isolatedField.substr(0, virgStart+1) + attrContent // updates the attribute content_
                                + subString(isolatedField, virgEnd, isolatedField.length());
            }
            this->content = preField + isolatedField + afterField;
            return writeFile(this->content);
        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" of field \""
                                         + fieldName + "\" not found");
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::removeField(const string &fieldName) {
    this->content = readFile();
    int fieldIndex = this->content.find("    [$] \"" + fieldName + "\" ::>");
    if (fieldIndex > 0) { // checks if the field exists
        string preField = subString(this->content, 0, fieldIndex); // isolates what's before the field
        string tmp = subString(this->content, fieldIndex + 5, this->content.length());

        int endFieldIndex = tmp.find("[$]");
        int eofFieldIndex = tmp.find("#>");

        string afterField;

        if (endFieldIndex > 0 and endFieldIndex < eofFieldIndex) // isolates what's after the field
            afterField = subString(tmp, endFieldIndex - 4, tmp.length());
        else if (eofFieldIndex > 0)
            afterField = "#>";

        this->content = preField + afterField; // updates the content_
        return writeFile(this->content);
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::removeAttr(const string &fieldName, const string &attrName) {
    int fieldIndex = this->content.find("[$] \"" + fieldName + "\" ::>");
    if (fieldIndex > 0) { // checks if the field exists
        string preField = subString(this->content, 0, fieldIndex); // isolates what's after the field
        string tmp = subString(this->content, fieldIndex+5, this->content.length());

        int eofFieldIndex = tmp.find("#>");
        int endFieldIndex = tmp.find("[$]");

        int endIndex;

        if(endFieldIndex > 0 and endFieldIndex < eofFieldIndex)
            endIndex = endFieldIndex;
        else
            endIndex = eofFieldIndex;

        string isolatedField = subString(this->content, fieldIndex, endIndex+fieldIndex+5); // isolates the field
        string afterField = subString(tmp, endFieldIndex, tmp.length()); // isolates what's after the field

        int oldAttrIndex = isolatedField.find("(" + attrName + ")");

        if(oldAttrIndex >= 0) { // checks if the attribute exists
            int virgStart = oldAttrIndex;
            while(isolatedField[virgStart] != '"')
                virgStart += 1;

            int virgEnd = virgStart+1;
            while(isolatedField[virgEnd] != '"')
                virgEnd += 1;

            isolatedField = subString(isolatedField, 0, oldAttrIndex) // updates the field
                            + subString(isolatedField, virgEnd+1, isolatedField.length());

            this->content = preField + isolatedField + afterField;
            return writeFile(this->content);
        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" of field \""
                                         + fieldName + "\" not found");
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::isEmpty() {
    return this->empty;
}