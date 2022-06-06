# LsmL

Example file:

    <#
        [$] "field1" ::>
            (attribute1) -> "attribute 1 content"
            (attribute2) -> "attribute 2 content"
        [$] "field 2" ::>
            (attribute 3) -> "true"
            (attribute 4) -> "false"
    #>

Syntax:

- <#
  - SOF tag (Start Of File)
- \#>
  - EOF tag (End Of File)
- [$]
  - field opening tag
- ::>
  - field name closing tag and attributes opening tag
- ->
  - attribute membership tag
- field name must be wrappend around woth double quotes ""
- attribute name must be wrapped around with parentheses ()
- attribute content must be wrapped around with double quotes ""

Methods:

    LsmL lsml = LsmL("database.lsml"); // LsmL object

    lsml.read(); // returns std::vector<std::map<std::string, std::map<std::strig, std::string>>>
    lsml.write(newContent); // newContent must be of type std::vector<std::map<std::string, std::map<std::strig, std::string>>>

    lsml.isEmpty(); // returns bool

    lsml.getField("fieldName"); // returns std::map<std::string, std::string>
    lsml.getAttr("fieldName", "attrName"); // returns std::string
    
    lsml.addField("fieldName"); // void
    lsml.addAttr("fieldName", "attrName", "attrContent"); // void
    
    lsml.editField("fieldName", "newFieldName"); // void
    lsml.editAttr("fieldName", "attrName", "newAttrName", "newAttrContent"); // void

    lsml.removeField("fieldName"); // void
    lsml.removeAttr("fieldName", "attrName"); // void
