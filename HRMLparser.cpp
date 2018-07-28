// HRMLparser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h" 

//////////////////////////////////////////

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <exception>
#include <cctype>

using namespace std;

class Attrib;
class Value;
class Tag;
class Element;
class TagClose;
class GreaterThan;
class EqualSign;

/**************************************************************/
class HRMLparser {

public:
	/* Nested class */
	/* Exception specific for a parser, exposed to a user of a library.*/
	class HRLMParsingException : public exception {
	private:
		const char *msg;
	public:
		HRLMParsingException(const char* str) { msg = str; }
		const char* what() const throw () override { return this->msg; }
	};

private:
	/* Possible elements */

	/* Nested enum */
	enum class ElemType {
		TAG_OPEN,			// <tag1..
		TAG_CLOSE,			// </tag1>
		ATTRIB,				// someAttr
		VALUE,				// "someVal"
		EQUAL_SGN,			// =
		GT					// > -> ending of "tag opening section"
	};

	/* Nested classes */
	class Element {
	public:
		ElemType elemType;
		virtual ~Element(){}
	};

	class Tag : public Element {
	public:
		string name;
		bool hasClosing;
		bool hasClosingOfOpenSection;
		map<string, string> attribs;
		vector<Tag*> childs;
		Tag() : hasClosing(false), hasClosingOfOpenSection(false) {}
		};

	class TagClose : public Element {
	public:
		string name;
	};

	class Attrib : public Element {
	public:
		string name;
		bool hasValue = false;
		bool hasEqSgn = false;
	};

	class Value : public Element { 
	public:
		Value() {};
		Value(string v) : value(v) {};
		string value;
	};

	class EqualSign : public Element {};
	class GreaterThan : public Element {};

	/**************************************************************/

	Tag *rootTag;
	vector<string> tokens;
	vector<Element*> listOfElems;

	void leaveOnlyAlNumChars(string& s)
	{
		string ret;
		for (auto c : s)
		{
			if (isalnum(c)) ret.push_back(c);
		}
		s = ret;
	}

	bool startsWith(string s, char c)
	{
		if (s.size() < 1) throw HRLMParsingException("Invalid Tag token.");
		if (s.front() == c) return true;
		else return false;
	}

	bool startsWithAndIsAlNumAfter(string s, char c)
	{
		if (s.size() < 1) throw HRLMParsingException("Tag-starting char but no tag name.");
		if (s.front() == c && isalnum(s.at(1))) return true;
		else return false;
	}

	bool startsWith(string s, string beg)
	{
		if (search(s.begin(), s.end(), beg.begin(), beg.end()) == s.begin()) return true;
		else return false;
	}

	bool endsWith(string s, string beg)
	{
		if (search(s.begin(), s.end(), beg.begin(), beg.end()) == s.end() - 2) return true;
		else return false;
	}

	bool endsWith(string s, char c)
	{
		if (s.back() == c) return true;
		else return false;
	}

	bool isTagOpenningToken(string tok, bool closing)
	{
		if (tok.back() == '>')
		{
			closing = true;
		}

		bool ret = false;
		if (tok.size() > 0 &&
			startsWithAndIsAlNumAfter(tok, '<')) ret = true;
		return ret;
	}

	bool isTagClosingToken(string tok)
	{
		return startsWith(tok, "</");
	}

	bool isAttrib(string tok)
	{
		bool ret = true;
		for (auto c : tok)
		{
			if (!isalnum(c)) {
				ret = false;
				break;
			}
		}
		return ret;
	}

	bool isValue(string tok, bool& closing)
	{
		if (tok.back() == '>')
		{
			closing = true;
		}

		if (startsWith(tok, "\"") && endsWith(tok, "\""))
			throw HRLMParsingException("Invalid attribute value. Missing quote character.");

		string val(tok.begin() + 2, tok.end() - 2);
		for (auto c : val)
		{
			if (!isalnum(c)) {
				return false;
			}
		}
		return true;
	}

	bool isEqualSign(string tok)
	{
		if (tok.front() == '=')
		{
			if (tok.size() == 1) return true;
			else throw HRLMParsingException("Unexpected character after equal sign");
		}
		else return false;
	}

	bool isGrThan(string tok)
	{
		if (tok.front() == '>')
		{
			if (tok.size() == 1) return true;
			else throw HRLMParsingException("Unexpected character after tag closing '>'");
		}
		else return false;
	}

public:

	~HRMLparser()
	{
		for (auto e : this->listOfElems)
			delete e;
	}

	void extractTagsAndAttribs(vector<string>& lines)
	{
		string token;
		for (auto l : lines)
		{
			stringstream ss(l);
			while (!ss.eof()) {
				ss >> token;
				tokens.push_back(token);
			}
		}

		for (auto t : tokens)
		{
			bool closing = false;

			// opening of a tag
			if (isTagOpenningToken(t, closing)) {
				Tag *tag = new Tag();
				tag->elemType = ElemType::TAG_OPEN;

				if (closing)
				{
					tag->name = t.substr(1, t.size()-1);
					listOfElems.push_back(tag);

					// Push also 'ending of a tag'
					GreaterThan *e = new GreaterThan();
					e->elemType = ElemType::GT;

					listOfElems.push_back(e);
				}
				else {
					tag->name = t.substr(1);
					listOfElems.push_back(tag);
				}
			}

			// ending of a tag
			else if (isTagClosingToken(t)) {
				TagClose *tc = new TagClose();
				tc->name = t.substr(2, t.size() - 3);
				tc->elemType = ElemType::TAG_CLOSE;

				listOfElems.push_back(tc);
			}

			// attribute name
			else if (isAttrib(t)) {
				Attrib *a =  new Attrib();
				a->name = t;
				a->elemType = ElemType::ATTRIB;

				listOfElems.push_back(a);
			}

			// equal sign
			else if (isEqualSign(t)) {
				EqualSign *e = new EqualSign();
				e->elemType = ElemType::EQUAL_SGN;

				listOfElems.push_back(e);
			}

			// attribute value
			else if (isValue(t, closing)) {
				Value *v = new Value();
				v->value = t.substr(1, t.size() - 3);
				v->elemType = ElemType::VALUE;

				listOfElems.push_back(v);

				if (closing)
				{
					GreaterThan *e = new GreaterThan();
					e->elemType = ElemType::GT;

					listOfElems.push_back(e);
				}
			}

			// standalone closing of 'tag opening section'
			else if (isGrThan(t)) {
				GreaterThan	*s = new GreaterThan();
				s->elemType = ElemType::GT;

				listOfElems.push_back(s);
			}
		}
	}

	void validateElementsList()
	{
		Element *firstElem = listOfElems.at(0);
		if (firstElem->elemType != ElemType::TAG_OPEN)
			throw HRLMParsingException("First element must be a tag-opening element.");
		else {
			/* We can also use dynamic cast here, but we are sure at this point that
			 * we point to Tag so we can use static_cast as well.*/
			Tag *t = static_cast<Tag*>(firstElem);
			rootTag = t;
		}

		vector<Tag*> mostRecentTags;
		mostRecentTags.push_back(rootTag);
		Attrib *mostRecentAttrib = nullptr;
		Element *prevElem = firstElem;

		for (auto it = listOfElems.begin()+1; it != listOfElems.end(); it++)
		{
			Element *e = *it;
			switch (e->elemType)
			{
			case ElemType::TAG_OPEN:
			{
				switch (prevElem->elemType)
				{
					// These are valid cases
					case ElemType::TAG_CLOSE:
					case ElemType::GT:
					{
						Tag *nextTag = static_cast<Tag*>(e);
						mostRecentTags.back()->childs.push_back(nextTag);
						mostRecentTags.push_back(nextTag);
						break;
					}
					default: throw HRLMParsingException("New tag may appear only"
						     " after closing of a tag or within a tag as a subtag");
				}
				break;
			}
			case ElemType::ATTRIB:
			{
				switch (prevElem->elemType)
				{
					// These are valid cases
					case ElemType::TAG_OPEN:
					case ElemType::VALUE:
					{
						Attrib *a = static_cast<Attrib*>(e);
						mostRecentAttrib = a;
						if (mostRecentTags.back()->attribs.count(a->name) != 0)
							throw HRLMParsingException("Attribute with such name"
								                  " already exists for this tag.");
						// No value parsed yet. For now assign NULL.
						mostRecentTags.back()->attribs[a->name] = "NULL";
						break;
					}
					default: throw HRLMParsingException("Attribute may appear only"
						        " inside of a tag opening section, either directly"
						       " after tag name or after previous attribute value.");
				}
				break;
			}
			case ElemType::EQUAL_SGN:
			{
				switch (prevElem->elemType)
				{
					// This is valid case
					case ElemType::ATTRIB:
					{
						mostRecentAttrib->hasEqSgn = true;
						break;
					}
					default: throw HRLMParsingException("Equal sign may appear only inside"
					          " of a 'tag opening section', after attribute name. Between "
				                " atribute name and value, only one equal sign is allowed.");
				}
				break;
			}
			case ElemType::VALUE:
			{
				switch (prevElem->elemType)
				{
					// These are valid cases
					case ElemType::EQUAL_SGN:
					{
						Value *v = static_cast<Value*>(e);
						if (mostRecentTags.back()->attribs.at(mostRecentAttrib->name) != "NULL")
							throw HRLMParsingException("Attribute already has a value.");
						mostRecentTags.back()->attribs[mostRecentAttrib->name] = v->value;
						mostRecentAttrib->hasValue = true;
						break;
					}
					default: throw HRLMParsingException("Attribute value may appear"
						                               " only after the equal sign.");
				}
				break;
			}
			case ElemType::GT:
			{
				switch (prevElem->elemType)
					{
						// These are valid cases
					case ElemType::VALUE:
					case ElemType::TAG_OPEN:
					{
						mostRecentTags.back()->hasClosingOfOpenSection = true;
						break;
					}
					default: throw HRLMParsingException("Closing of 'tag opening'section"
						          " may appear only after an attribute's value or after "
					                 " a 'tag opening' - in case there is no attributes.");
					}
				break;
			}
			case ElemType::TAG_CLOSE:
			{
				switch (prevElem->elemType)
				{
					// These are valid cases
					case ElemType::TAG_CLOSE:
					case ElemType::GT:
					{
						TagClose *tc = static_cast<TagClose*>(e);
						if (mostRecentTags.back()->name != tc->name)
							throw HRLMParsingException("Closing tag name doesn't match the opening tag name.");
						mostRecentTags.back()->hasClosing = true;
						mostRecentTags.pop_back();
						break;
					}
					default: throw HRLMParsingException("Closing tag may appear only"
						                        " after another closing tag or after"
						                         " closing of 'tag opening section'.");
				}
				break;
			}
			default:
				{
					throw HRLMParsingException("Validation fatal ERROR. No such element.");
				}
			}

			prevElem = e;
		}

		/* Final validation. Check if all tags are closed. Check if all attributes have
		 * equal signs before the attribute value.*/
		for (auto &e : listOfElems)
		{
			switch (e->elemType)
			{
				case ElemType::TAG_OPEN:
				{
					Tag *tag = static_cast<Tag*>(e);
					if (!tag->hasClosing) throw HRLMParsingException("Closing of tag missing.");
					else if (!tag->hasClosingOfOpenSection)
						throw HRLMParsingException("Closing of 'tag opening section' missing.");
				}
				case ElemType::ATTRIB:
				{
					Attrib *a = static_cast<Attrib*>(e);
					if (!a->hasEqSgn) throw HRLMParsingException("Missing equal sign for attribute.");
					if (!a->hasValue) throw HRLMParsingException("Missing value for attribute.");
				}
			}
		}
	}
};

/* Main function for testing */
int main() {

	//int nOfLines, nOfQueries;
	//cin >> nOfLines >> nOfQueries;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');

	vector<string> lines;
	string line;

	/* for (int i = 0; i < nOfLines; i++)
	{
		getline(cin, line);
		lines.push_back(line);
	} */

	lines.push_back("<tag1 a1 = \"v1\">");
	lines.push_back("<tag2 a2 = \"v2\">");
	lines.push_back("<tag3 a3 = \"v3\" a4 = \"v4\">");
	lines.push_back("</tag3>");
	lines.push_back("</tag2>");
	lines.push_back("</tag1>");

	HRMLparser parser;
	try {
		parser.extractTagsAndAttribs(lines);
		parser.validateElementsList();
	}
	catch (HRMLparser::HRLMParsingException e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown exception" << endl;
	}

	return 0;
}
