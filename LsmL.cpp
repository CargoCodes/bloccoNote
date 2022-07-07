#include "LsmL.h"

void LsmL::startingContent() {
    if (subString(filePath, int(filePath.length()) - 5, int(filePath.length())) !=
        ".lsml") // checks the extension of the file
        throw runtime_error("File extension must be \".lsml\"");
    else {
        file.open(filePath, ios::in); // tries to open file to read the content
        if (file.is_open()) {
            string fileContent;
            while (getline(file, fileContent)) {
                content += fileContent + "\n"; // reads the content and stores it in "content"
            }
            file.close();
        } else { // if it is impossible to read
            content = "<#\n#>"; // sets content to the empty standard
            writeFile(content);
        }
    }
}

map<string, map<string, string>> LsmL::getField_() {
    map<string, map<string, string>> tmpDict; // content of the field variable
    pos += 3;

    while (text[pos] == ' ') // skips blank spaces
        pos += 1;

    if (text[pos] == '"') { // finds the opening double quotes for field name
        pos += 1;
        string fieldName;

        while (text[pos] != '"') { // scans until the following double quotes to read field name
            fieldName += text[pos];
            pos += 1;
        }
        pos += 1;

        while(text[pos] == ' ') // skips blank spaces
            pos += 1;

        map<string, string> insideDict; // map for attributes
        if(text.substr(pos, 3) == "::>"){ // looks for the attribute list opening tag
            pos += 3;

            while (subString(text, pos, int(text.length()) - 1) != "#>"
                   and text.substr(pos, 3) != "[$]") { // scans until it finds EOF or new field
                nullAdvancement(); // skips blank spaces, blank lines and tabs

                if (text[pos] == '(') { // looks for attribute opening parentheses
                    vector<string> returnVector = getAttr_(); // starts attribute reading, one at the time
                    insideDict.insert(
                            pair<string, string>(returnVector[0], returnVector[1])); // stores the attribute in the map
                    pos += 1;
                }

                tmpDict.insert(
                        pair<string, map<string, string>>(fieldName, insideDict)); // pushes the field in the return map
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

    pos += 1;
    nullAdvancement(); // skips blank spaces, blank lines and tabs

    while (text[pos] != ')') { // looks for the ending attribute name tag
        attrName += text[pos];
        pos += 1;
    }

    pos += 1;
    nullAdvancement(); // skips blank lines, blank spaces and tabs

    if (text.substr(pos, 2) == "->") { // looks for the appartenence tag
        pos += 2;

        while (text[pos] == ' ') // skips blank spaces
            pos += 1;

        if (text[pos] == '"') { // looks for the attribute content opening double quote
            string attr;
            pos += 1;

            while (text[pos] != '"') { // looks for the attribute content closing double quote
                attr += text[pos];
                pos += 1;
            }

            res.push_back(attrName);
            res.push_back(attr);

            return res; // returns attribute name and content
        } else
            throw runtime_error("Attribute must be wrapped with \"\"");
    } else
        throw runtime_error("\"->\" must between attribute name and attribute");
}

vector<map<string, map<string, string>>> LsmL::read() {
    pos = 0;
    text.clear();
    file.open(filePath, ios::in);
    if (file.is_open()) { // reads the content of the file
        string fileContent;
        while (getline(file, fileContent)) {
            text += fileContent + "\n";
        }
        file.close();

        vector<map<string, map<string, string>>> res; // return variable
        if (text.substr(pos, 2) == "<#") { // looks for SOF
            pos += 2;
            while (pos < text.length()
                   and subString(text, pos, int(text.length()) - 1) !=
                       "#>") { // scans until the end of the file
                nullAdvancement(); // skips blank spaces, blank lines and tabs

                if (text.substr(pos, 3) == "[$]") { // looks for the field tag
                    map<string, map<string, string>> point = getField_(); // starts the field reading process
                    res.push_back(point); // stores the field
                }
                if (subString(text, pos, int(text.length()) - 1) ==
                    "#>") // if it finds the EOF, stops scan
                    break;
            }
            return res;
        } else {
            throw runtime_error("File not starting with <#");
        }
    } else
        throw runtime_error("Can't open file \"" + filePath + "\"");
}

map<string, string> LsmL::getField(const string &fieldName) {
    map<string, string> res;
    string fileContent = readFile(); // reads the file
    int fieldIndex = int(fileContent.find("[$] \"" + fieldName + "\" ::>"));
    if (fieldIndex > 0) { // checks if the field is in the db
        // isolates the field from the rest of the file

        int endFieldIndex = fieldIndex + ("[$] \"" + fieldName + "\" ::>").length();

        while (subString(fileContent, endFieldIndex, endFieldIndex + 2) != "#>"
               and subString(fileContent, endFieldIndex, endFieldIndex + 3) != "[$]") {

            endFieldIndex++;
        }

        string isolatedClass = subString(fileContent, fieldIndex, endFieldIndex);

        // reads the field and puts the attributes in a map
        int parenthesesIndex = int(isolatedClass.find("("));
        if (parenthesesIndex > 0) {
            int index = parenthesesIndex;

            while (index < isolatedClass.length() and isolatedClass[index] == '(') {
                string attrName, attrContent;
                index++;
                while (isolatedClass[index] != ')') {
                    attrName += isolatedClass[index];
                    index++;
                }
                index++;
                while (isolatedClass[index] == ' ' or isolatedClass[index] == '\n' or isolatedClass[index] == '\t')
                    index++;
                if (subString(isolatedClass, index, index + 2) != "->") {
                    throw runtime_error("-> not found");
                }
                index += 2;
                while (isolatedClass[index] == ' ' or isolatedClass[index] == '\n' or isolatedClass[index] == '\t')
                    index++;
                if (isolatedClass[index] != '"')
                    throw runtime_error("\" not found");
                index++;
                while (isolatedClass[index] != '"') {
                    attrContent += isolatedClass[index];
                    index++;
                }
                index++;
                while (isolatedClass[index] == ' ' or isolatedClass[index] == '\n' or isolatedClass[index] == '\t')
                    index++;
                res.insert(pair<string, string>(attrName, attrContent));
            }
        } else
            throw runtime_error("( not found");
        return res;
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

string LsmL::getAttr(const string &fieldName, const string &attrName) {
    string res;
    string fileContent = readFile(); // reads the file
    int fieldIndex = int(fileContent.find("[$] \"" + fieldName + "\" ::>"));
    if (fieldIndex > 0) {
        int endFieldIndex = fieldIndex + ("[$] \"" + fieldName + "\" ::>").length();

        while (subString(fileContent, endFieldIndex, endFieldIndex + 2) != "#>"
               and subString(fileContent, endFieldIndex, endFieldIndex + 3) != "[$]") {

            endFieldIndex++;
        }

        string isolatedClass = subString(fileContent, fieldIndex, endFieldIndex);

        int attributeIndex = isolatedClass.find("(" + attrName + ") -> \"");
        if (attributeIndex > 0) {
            int contentStartIndex = attributeIndex + ("(" + attrName + ") -> \"").length();
            int contentEndIndex = contentStartIndex;
            while (isolatedClass[contentEndIndex] != '"') {
                res += isolatedClass[contentEndIndex];
                contentEndIndex++;
            }
        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" -- - not found");
        return res;
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::addField(const string &fieldName) {
    content = readFile();
    int fieldIndex = content.find("    [$] \"" + fieldName + "\" ::>");
    if (fieldIndex < 0) { // checks if the field already exists
        string oldContent = subString(content, 0,
                                      content.length() - 3); // takes teh content but removes the EOF
        string eof = "#>";

        content = oldContent + "    [$] \"" + fieldName + "\" ::>\n" + eof; // adds the new field and then the EOF

        return writeFile(content);
    }
    return false;
}

bool LsmL::addAttr(const string &fieldName, const string &attrName, const string &attrContent) {
    content = readFile();
    int index = content.find("[$] \"" + fieldName + "\" ::>");
    if (index > 0) { // checks if the field exists
        int endIndex = index + ("[$] \"" + fieldName + "\" ::>").length() + 1; // takes teh index of the field

        int endFieldIndex = endIndex + 1;
        try { // scans until EOF or new field
            while (content.substr(endFieldIndex, 2) != "#>"
                   and content.substr(endFieldIndex, 3) != "[$]")
                endFieldIndex += 1;
        } catch (...) {
            endFieldIndex = content.length() - 2;
        }

        string isolatedField = subString(content, index, endFieldIndex); // isolates the wanted field
        int attrIndex = isolatedField.find("        (" + attrName + ") -> \"" + attrContent + "\"");
        if (attrIndex < 0) { // checks if attribute already exists
            content = subString(content, 0, endIndex) + "        (" + attrName + ") -> \""
                            + attrContent + "\"\n"
                            + subString(content, endIndex, content.length()); // adds the attribute

            return writeFile(content);
        }
        return false;
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::editField(const string &fieldName, const string &newFieldName) {
    int startIndex = content.find("[$] \"" + fieldName + "\" ::>");
    if(startIndex > 0) { // checks if the field exists
        int endIndex = startIndex + ("[$] \"" + fieldName + "\" ::>").length(); // takes the ending index of teh field declaration

        content = content.substr(0, startIndex) + "[$] \"" + newFieldName + "\" ::>"
                        + subString(content, endIndex, content.length()); // edits the field name

        return writeFile(content);
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::editAttr(const string &fieldName, const string &attrName, const string &newAttrName, const string &attrContent) {
    content = readFile();
    int fieldIndex = content.find("[$] \"" + fieldName + "\" ::>");
    if (fieldIndex > 0) { // checks if the field exists
        string preField = subString(content, 0, fieldIndex); // isolates what's before the field
        string tmp = subString(content, fieldIndex + 5, content.length());

        int eofFieldIndex = tmp.find("[$]");
        int endFieldIndex = tmp.find("#>");

        int endIndex;
        if (eofFieldIndex > 0)
            endIndex = eofFieldIndex;
        else
            endIndex = endFieldIndex;

        string isolatedField = subString(content, fieldIndex, endIndex + fieldIndex + 5); // isolates the field
        string afterField = subString(tmp, endIndex, tmp.length()); // isolates what's after the field

        int oldAttrIndex = isolatedField.find("(" + attrName + ")");
        if (oldAttrIndex > 0) { // checks if the attribute exists
            isolatedField = subString(isolatedField, 0, oldAttrIndex+1)+ newAttrName + // updates the attribute name
                            subString(isolatedField, oldAttrIndex + attrName.length()+1, isolatedField.length());

            if (not attrContent.empty()) { // if attribute name is not empty
                int virgStart = oldAttrIndex;

                while (isolatedField[virgStart] != '"')
                    virgStart += 1;


                int virgEnd = virgStart+1;
                while(isolatedField[virgEnd] != '"')
                    virgEnd += 1;

                isolatedField = subString(isolatedField, 0, virgStart+1) + attrContent // updates the attribute content
                                + subString(isolatedField, virgEnd, isolatedField.length());
            }

            content = preField + isolatedField + afterField;

            return writeFile(content);
        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" of field \""
                                         + fieldName + "\" not found");
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::removeField(const string &fieldName) {
    int fieldIndex = content.find("    [$] \"" + fieldName + "\" ::>");
    if (fieldIndex > 0) { // checks if the field exists
        string preField = subString(content, 0, fieldIndex); // isolates what's before the field
        string tmp = subString(content, fieldIndex + 5, content.length());

        int endFieldIndex = tmp.find("[$]");
        int eofFieldIndex = tmp.find("#>");

        string afterField;

        if (endFieldIndex > 0 and endFieldIndex < eofFieldIndex) // isolates what's after the field
            afterField = subString(tmp, endFieldIndex - 4, tmp.length());
        else if (eofFieldIndex > 0)
            afterField = "#>";

        content = preField + afterField; // updates the content

        return writeFile(content);
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::removeAttr(const string &fieldName, const string &attrName) {
    content = readFile();
    int fieldIndex = content.find("[$] \"" + fieldName + "\" ::>");
    if (fieldIndex > 0) { // checks if the field exists
        string preField = subString(content, 0, fieldIndex); // isolates what's after the field
        string tmp = subString(content, fieldIndex+5, content.length());

        int eofFieldIndex = tmp.find("#>");
        int endFieldIndex = tmp.find("[$]");

        int endIndex;

        if (endFieldIndex > 0 and endFieldIndex < eofFieldIndex)
            endIndex = endFieldIndex;
        else
            endIndex = eofFieldIndex;

        string isolatedField = subString(content, fieldIndex, endIndex + fieldIndex + 5); // isolates the field
        string afterField = subString(tmp, endIndex, tmp.length()); // isolates what's after the field

        int oldAttrIndex = isolatedField.find("(" + attrName + ")");

        if (oldAttrIndex >= 0) { // checks if the attribute exists
            int virgStart = oldAttrIndex;
            while (isolatedField[virgStart] != '"')
                virgStart += 1;

            int virgEnd = virgStart + 1;
            while (isolatedField[virgEnd] != '"')
                virgEnd += 1;

            isolatedField = subString(isolatedField, 0, oldAttrIndex) // updates the field
                            + subString(isolatedField, virgEnd+1, isolatedField.length());

            content = preField + isolatedField + afterField;

            return writeFile(content);
        } else
            throw AttributeNotFoundError("Attribute \"" + attrName + "\" of field \""
                                         + fieldName + "\" not found");
    } else
        throw FieldNotFoundError("Field \"" + fieldName + "\" not found");
}

bool LsmL::isEmpty() {
    string fileContent = readFile();
    auto fieldIndex = fileContent.find("[$]");
    auto endFieldIndex = fileContent.find("::>");
    auto attrIndex = fileContent.find("->");
    // checks for the presence of fields and/or attributes
    if ((fieldIndex > fileContent.length()) and (endFieldIndex > fileContent.length()) and
        (attrIndex > fileContent.length()))
        // if not found, returns true
        return true;
    // otherways returns false
    return false;
}

/*\..{[|<->_<'>]|}../*/
