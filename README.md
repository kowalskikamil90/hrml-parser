# hrml-parser
This is tool for parsing HRML documents, which are quite similar to XML documents.
In HRML (hacker rank markup language), each element consists of a starting and ending tag, and there are attributes associated with each tag. Only starting tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde and the name of the attribute. The tags may also be nested.  The opening tags follow the format:  <tag-name attribute1-name = "value1" attribute2-name = "value2" ...>  The closing tags follow the format:  </tag-name>  For example:  <tag1 value = "HelloWorld"> <tag2 name = "Name1"> </tag2> </tag1> The attributes are referenced as:  tag1[tilde]value   tag1.tag2[tilde]name

The tool parses HRML document and internally generates a DOM (document object model) that later on may be accessed by a querry interpreter (which is also a part of this tool).
