# HRML-PARSER
This is tool for parsing HRML documents, which are quite similar to XML documents.
In HRML (hacker rank markup language), each element consists of a starting and ending tag, and there are attributes associated with each tag. Only starting tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde and the name of the attribute. The tags may also be nested.

The opening tags follow the format: <tag-name attribute1-name = "value1" attribute2-name = "value2" ...>

The closing tags follow the format: < / tag-name>

# QUERRY INTERPRETER (QI)
In the QUERRY INTERPRETER the attributes are referenced as (e.g.):

tag1 ~ value

tag1.tag2 ~ name

The tool parses HRML document and internally generates a DOM (document object model) that later on may be accessed by a querry interpreter (which is also a part of this tool).

# BLACKBOX TESTS (gtest)
![](https://github.com/kowalskikamil90/hrml-parser/blob/master/demo/testOutput.png)

# EXCEPTION ERROR CODES:

CURRENTLY, FOLLOWING EXCEPTION CODE ERRORS ARE AVAILABLE FOR THE CLIENT:

["E001"] = "Tag name may contain only alfanumeric characters."

["E002"] = "Invalid attribute name. Only alfanumeric characters allowed."

["E003"] = "Invalid attribute value. Missing ending quote character."

["E004"] = "Invalid attribute value. Missing starting quote character."

["E005"] = "No attribute value specified between the quotes."

["E006"] = "Attribute value may consist of only alfanumeric characters."

["E007"] = "Unexpected character after equal sign. Equal sign must be space seperated from attribute name and attribute value."

["E008"] = "Unexpected character after tag closing."

["E010"] = "First element must be a tag-opening element."

["E011"] = "New tag may appear only after closing of a tag or within a tag as a subtag."

["E012"] = "Attribute with such name already exists for this tag."

["E013"] = "Attribute may appear only inside of a tag opening section, either directly after tag name or after previous attribute value."

["E014"] = "Equal sign may appear only inside of a 'tag opening section', after attribute name. Between atribute name and value, only one equal sign is allowed."

["E015"] = "Attribute already has a value."

["E016"] = "Attribute value may appear only after the equal sign."

["E017"] = "Closing of 'tag opening'section may appear only after an attribute's value or after a 'tag opening' - in case there is no attributes."

["E018"] = "Closing tag name doesn't match the opening tag name."

["E019"] = "Closing tag may appear only after another closing tag or after closing of 'tag opening section'."

["E021"] = "Closing of tag missing."

["E022"] = "Closing of 'tag opening section' missing."

["E023"] = "Missing equal sign for attribute."

["E024"] = "Missing value for attribute."

["Q001"] = "Couldn't find ~ character in querry, to denote an attribute name."

["Q002"] = "Such root tag does not exist."

["Q003"] = "Such child tag does not exist."

["Q004"] = "Such attribute does not exist for specified tag."

# EXEMPLARY HRML document

![](https://github.com/kowalskikamil90/hrml-parser/blob/master/demo/HRMLexample.png)

