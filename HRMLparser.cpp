#include "stdafx.h" 
#include "HRMLparser.h"

///////////////////////////////////////////////////////////
/* Public exception class */
/* Exception specific for a parser, exposed to a user of a library.*/
///////////////////////////////////////////////////////////

HRMLparser::ParsingError::ParsingError(const char* str) { msg = str; }
const char* HRMLparser::ParsingError::what() const { return this->msg; }

///////////////////////////////////////////////////////////
/* Private enum type */
///////////////////////////////////////////////////////////

enum class HRMLparser::ElemType {
	TAG_OPEN,			// <tag1..
	TAG_CLOSE,			// </tag1>
	ATTRIB,				// someAttr
	VALUE,				// "someVal"
	EQUAL_SGN,			// =
	GT					// > -> ending of "tag opening section"
};

///////////////////////////////////////////////////////////
/* Private classes */
///////////////////////////////////////////////////////////

class HRMLparser::Element {
public:
	ElemType elemType;
	virtual ~Element() {}
};

class HRMLparser::Tag : public HRMLparser::Element {
public:
	string name;
	bool hasClosing;
	bool hasClosingOfOpenSection;
	map<string, string> attribs;
	vector<Tag*> childs;
	Tag() : hasClosing(false), hasClosingOfOpenSection(false) {}
};

class HRMLparser::TagClose : public HRMLparser::Element {
public:
	string name;
};

class HRMLparser::Attrib : public HRMLparser::Element {
public:
	string name;
	bool hasValue;
	bool hasEqSgn;
	Attrib() :hasValue(false), hasEqSgn(false) {}
};

class HRMLparser::Value : public HRMLparser::Element {
public:
	Value() {};
	Value(string v) : value(v) {};
	string value;
};

class HRMLparser::EqualSign : public HRMLparser::Element {};
class HRMLparser::GreaterThan : public HRMLparser::Element {};

///////////////////////////////////////////////////////////
/* Private methods */
///////////////////////////////////////////////////////////

void HRMLparser::leaveOnlyAlNumChars(string& s)
{
	string ret;
	for (auto c : s)
	{
		if (isalnum(c)) ret.push_back(c);
	}
	s = ret;
}

bool HRMLparser::startsWith(string &s, char c)
{
	if (s.size() < 1) return false;
	if (s.front() == c) return true;
	else return false;
}

bool HRMLparser::isAlNum(string &s)
{
	for (auto c : s)
	{
		if (!isalnum(c))
			return false;
	}
	return true;
}

bool HRMLparser::startsWith(string &s, string beg)
{
	if (search(s.begin(), s.end(), beg.begin(), beg.end()) == s.begin()) return true;
	else return false;
}

bool HRMLparser::endsWith(string &s, string beg)
{
	if ((search(s.begin()+1, s.end(), beg.begin(), beg.end())) == s.end() - 1) return true;
	else return false;
}

bool HRMLparser::endsWith(string &s, char c)
{
	if (s.size() < 1) return false;
	if (s.back() == c) return true;
	else return false;
}

bool HRMLparser::isTagOpenningToken(string tok, bool closing)
{
	if (tok.back() == '>')
	{
		closing = true;
		tok.erase(tok.size() - 1);
	}

	if (startsWith(tok, '<'))
	{
		// At this point we know that we are dealing with a tag
		if (closing) {
			string tagName(tok.begin() + 1, tok.end() - 1);
			if (isAlNum(tagName)) return true;
			else ParsingError("Tag name may contain only alfanumeric characters.");
		}
		else {
			string tagName(tok.begin() + 1, tok.end());
			if (isAlNum(tagName)) return true;
			else ParsingError("Tag name may contain only alfanumeric characters.");
		}
	}
	return false;
}

bool HRMLparser::isTagClosingToken(string tok)
{
	return startsWith(tok, string("</"));
}

bool HRMLparser::isAttrib(string tok)
{
	if (!startsWith(tok, '<') &&
		!startsWith(tok, '"') &&
		!startsWith(tok, '=') &&
		!endsWith(tok, '"') &&
		!endsWith(tok, '>')) {
		for (auto c : tok)
		{
			if (!isalnum(c)) {
				throw ParsingError("Invalid attribute name. Only alfanumeric characters allowed.");
			}
		}
		return true;
	}
	return false;
}

bool HRMLparser::isValue(string tok, bool& closing)
{
	if (tok.size() > 2) {
		if (tok.back() == '>')
		{
			tok.pop_back();
			closing = true;
		}

		bool consideAsValue = false;

		// Value must be surrounded by quote characters
		if (startsWith(tok, "\"") && endsWith(tok, "\"")) {
			consideAsValue = true;
		}
		else if (startsWith(tok, "\"") && !endsWith(tok, "\"")) {
			consideAsValue = true;
			throw ParsingError("Invalid attribute value. Missing ending quote character.");
		}
		else if (!startsWith(tok, "\"") && endsWith(tok, "\"")) {
			consideAsValue = true;
			throw ParsingError("Invalid attribute value. Missing starting quote character.");
		}

		if (consideAsValue && tok.size() >= 2) {
			string val(tok.begin() + 1, tok.end() - 1);
			if (val.empty()) throw ParsingError("No attribute value specified between the quotes.");
			if (!isAlNum(val)) throw ParsingError("Attribute value may consist of only alfanumeric characters.");
			return true;
		}
		return false;
	}
	else {
		return false;
	}
	
}

bool HRMLparser::isEqualSign(string tok)
{
	if (tok.size() < 1) return false;
	if (tok.front() == '=')
	{
		if (tok.size() == 1) return true;
		else throw ParsingError("Unexpected character after equal sign. "
		                        "Equal sign must be space seperated from "
		                        "attribute name and attribute value.");
	}
	else return false;
}

bool HRMLparser::isGrThan(string tok)
{
	if (tok.size() < 1) return false;
	if (tok.front() == '>')
	{
		if (tok.size() == 1) return true;
		else throw ParsingError("Unexpected character after tag closing");
	}
	else return false;
}

///////////////////////////////////////////////////////////
/* Public methods */
///////////////////////////////////////////////////////////

HRMLparser::~HRMLparser()
{
	for (auto e : this->listOfElems)
		delete e;
}

void HRMLparser::extractTagsAndAttribs(vector<string>& lines)
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

		if (t == "a3$43") {
			int x = 5;
		}

		bool closing = false;

		// opening of a tag
		if (isTagOpenningToken(t, closing)) {
			Tag *tag = new Tag();
			tag->elemType = ElemType::TAG_OPEN;

			if (closing)
			{
				tag->name = t.substr(1, t.size() - 1);
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
			Attrib *a = new Attrib();
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

		else {
			throw ParsingError("Parsing internal fatal ERROR. No such element.");
		}
	}
}

void HRMLparser::validateElementsList()
{
	Element *firstElem = listOfElems.at(0);
	if (firstElem->elemType != ElemType::TAG_OPEN)
		throw ParsingError("First element must be a tag-opening element.");
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

	for (auto it = listOfElems.begin() + 1; it != listOfElems.end(); it++)
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
			default: throw ParsingError("New tag may appear only"
				" after closing of a tag or within a tag as a subtag.");
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
					throw ParsingError("Attribute with such name"
						" already exists for this tag.");
				// No value parsed yet. For now assign NULL.
				mostRecentTags.back()->attribs[a->name] = "NULL";
				break;
			}
			default: throw ParsingError("Attribute may appear only"
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
			default: throw ParsingError("Equal sign may appear only inside"
				" of a 'tag opening section', after attribute name. Between"
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
					throw ParsingError("Attribute already has a value.");
				mostRecentTags.back()->attribs[mostRecentAttrib->name] = v->value;
				mostRecentAttrib->hasValue = true;
				break;
			}
			default: throw ParsingError("Attribute value may appear"
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
			default: throw ParsingError("Closing of 'tag opening'section"
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
					throw ParsingError("Closing tag name doesn't match the opening tag name.");
				mostRecentTags.back()->hasClosing = true;
				mostRecentTags.pop_back();
				break;
			}
			default: throw ParsingError("Closing tag may appear only"
				" after another closing tag or after"
				" closing of 'tag opening section'.");
			}
			break;
		}
		default:
		{
			throw ParsingError("Validation internal fatal ERROR. No such element.");
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
			if (!tag->hasClosing) throw ParsingError("Closing of tag missing.");
			else if (!tag->hasClosingOfOpenSection)
				throw ParsingError("Closing of 'tag opening section' missing.");
		}
		case ElemType::ATTRIB:
		{
			Attrib *a = static_cast<Attrib*>(e);
			if (!a->hasEqSgn) throw ParsingError("Missing equal sign for attribute.");
			if (!a->hasValue) throw ParsingError("Missing value for attribute.");
		}
		}
	}
}