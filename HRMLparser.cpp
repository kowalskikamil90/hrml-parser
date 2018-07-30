#include "HRMLparser.h"

///////////////////////////////////////////////////////////
/* Public exception class */
/* Exception specific for a parser, exposed to a user of a library.*/
///////////////////////////////////////////////////////////

/* Pass pointer to parser to get the Error Description.
 * We want to keep exception class small so all error
 * descriptions are stored in the HRMLparser class. */
HRMLparser::ParsingError::ParsingError(HRMLparser *parser, string errCode):
	errorCode(errCode)
{
	errorDes = parser->errorDescription[errorCode];
}

const char* HRMLparser::ParsingError::what() const { return errorDes.c_str();}

string HRMLparser::ParsingError::getErrorCode() { return errorCode;}

string HRMLparser::ParsingError::getErrorDescrition() {	return errorDes;}

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

bool HRMLparser::isTagOpenningToken(string tok, bool &closing)
{

	if (tok.back() == '>')
	{
		closing = true;
		tok.erase(tok.size() - 1);
	}

	if (startsWith(tok, '<') && tok.at(1) != '/')
	{
		// At this point we know that we are dealing with a tag
		string tagName(tok.begin() + 1, tok.end());

		if (isAlNum(tagName)) return true;
		else throw ParsingError(this, "E001");
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
		!startsWith(tok, '>') &&
		!startsWith(tok, '=') &&
		!endsWith(tok, '"') &&
		!endsWith(tok, '>')) {
		for (auto c : tok)
		{
			if (!isalnum(c)) {
				throw ParsingError(this, "E002");
			}
		}
		return true;
	}
	return false;
}

bool HRMLparser::isValue(string tok, bool closing)
{
	if (tok.size() >= 2) {
		if (tok.back() == '>')
		{
			tok.pop_back();
			closing = true;
		}

		bool considerAsValue = false;

		// Value must be surrounded by quote characters
		if (startsWith(tok, "\"") && endsWith(tok, "\"")) {
			considerAsValue = true;
		}
		else if (startsWith(tok, "\"") && !endsWith(tok, "\"")) {
			considerAsValue = true;
			throw ParsingError(this, "E003");
		}
		else if (!startsWith(tok, "\"") && endsWith(tok, "\"")) {
			considerAsValue = true;
			throw ParsingError(this, "E004");
		}

		if (considerAsValue && tok.size() >= 2) {
			string val(tok.begin() + 1, tok.end() - 1);
			if (val.empty()) throw ParsingError(this, "E005");
			if (!isAlNum(val)) throw ParsingError(this, "E006");
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
		else throw ParsingError(this, "E007");
	}
	else return false;
}

bool HRMLparser::isGrThan(string tok)
{
	if (tok.size() < 1) return false;
	if (tok.front() == '>')
	{
		if (tok.size() == 1) return true;
		else throw ParsingError(this, "E008");
	}
	else return false;
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
		bool closing = false;

		// opening of a tag
		if (isTagOpenningToken(t, closing)) {
			Tag *tag = new Tag();
			tag->elemType = ElemType::TAG_OPEN;

			if (closing)
			{
				// Push a tag, firstly
				tag->name = t.substr(1, t.size() - 2);
				listOfElems.push_back(tag);

				// Push also 'ending of a tag'
				GreaterThan *e = new GreaterThan();
				e->elemType = ElemType::GT;

				listOfElems.push_back(e);
			}
			else {
				// Push only a tag
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
			if (closing) {
				v->value = t.substr(1, t.size() - 3);
			}
			else {
				v->value = t.substr(1, t.size() - 2);
			}
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
			throw ParsingError(this, "E009");
		}
	}
}

void HRMLparser::validateElementsList()
{
	Element *firstElem = listOfElems.at(0);
	if (firstElem->elemType != ElemType::TAG_OPEN)
		throw ParsingError(this, "E010");
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
			default: throw ParsingError(this, "E011");
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
					throw ParsingError(this, "E012");
				// No value parsed yet. For now assign NULL.
				mostRecentTags.back()->attribs[a->name] = "NULL";
				break;
			}
			default: throw ParsingError(this, "E013");
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
			default: throw ParsingError(this, "E014");
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
					throw ParsingError(this, "E015");
				mostRecentTags.back()->attribs[mostRecentAttrib->name] = v->value;
				mostRecentAttrib->hasValue = true;
				break;
			}
			default: throw ParsingError(this, "E016");
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
			default: throw ParsingError(this, "E017");
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
					throw ParsingError(this, "E018");
				mostRecentTags.back()->hasClosing = true;
				mostRecentTags.pop_back();
				break;
			}
			default: throw ParsingError(this, "E019");
			}
			break;
		}
		default:
		{
			throw ParsingError(this, "E020");
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
			if (!tag->hasClosing) throw ParsingError(this, "E021");
			else if (!tag->hasClosingOfOpenSection)
				throw ParsingError(this, "E022");
		}
		case ElemType::ATTRIB:
		{
			Attrib *a = static_cast<Attrib*>(e);
			if (!a->hasEqSgn) throw ParsingError(this, "E023");
			if (!a->hasValue) throw ParsingError(this, "E024");
		}
		}
	}
}

HRMLparser::Tag* HRMLparser::getChildTag(Tag *parent, string childsName)
{
	for (auto tag : parent->childs)
	{
		if (tag->name == childsName) return tag;
	}
	return nullptr;	
}

string HRMLparser::getAttributeValue(Tag *mostRecentTag, string attribute)
{
	string value;
	try {
		value = mostRecentTag->attribs.at(attribute);
	}
	catch (out_of_range e) {
		return "NULL";
	}
	return value;
}

///////////////////////////////////////////////////////////
/* Public methods */
///////////////////////////////////////////////////////////

HRMLparser::HRMLparser()
{
	errorDescription["E001"] = "Tag name may contain only alfanumeric characters.";
	errorDescription["E002"] = "Invalid attribute name. Only alfanumeric characters allowed.";
	errorDescription["E003"] = "Invalid attribute value. Missing ending quote character.";
	errorDescription["E004"] = "Invalid attribute value. Missing starting quote character.";
	errorDescription["E005"] = "No attribute value specified between the quotes.";
	errorDescription["E006"] = "Attribute value may consist of only alfanumeric characters.";
	errorDescription["E007"] = "Unexpected character after equal sign. Equal sign must be space seperated from attribute name and attribute value.";
	errorDescription["E008"] = "Unexpected character after tag closing.";
	errorDescription["E009"] = "Invalid token. No such element.";
	errorDescription["E010"] = "First element must be a tag-opening element.";
	errorDescription["E011"] = "New tag may appear only after closing of a tag or within a tag as a subtag.";
	errorDescription["E012"] = "Attribute with such name already exists for this tag.";
	errorDescription["E013"] = "Attribute may appear only inside of a tag opening section, either directly after tag name or after previous attribute value.";
	errorDescription["E014"] = "Equal sign may appear only inside of a 'tag opening section', after attribute name. Between atribute name and value, only one equal sign is allowed.";
	errorDescription["E015"] = "Attribute already has a value.";
	errorDescription["E016"] = "Attribute value may appear only after the equal sign.";
	errorDescription["E017"] = "Closing of 'tag opening'section may appear only after an attribute's value or after a 'tag opening' - in case there is no attributes.";
	errorDescription["E018"] = "Closing tag name doesn't match the opening tag name.";
	errorDescription["E019"] = "Closing tag may appear only after another closing tag or after closing of 'tag opening section'.";
	errorDescription["E020"] = "Validation internal fatal ERROR. No such element.";
	errorDescription["E021"] = "Closing of tag missing.";
	errorDescription["E022"] = "Closing of 'tag opening section' missing.";
	errorDescription["E023"] = "Missing equal sign for attribute.";
	errorDescription["E024"] = "Missing value for attribute.";
	errorDescription["Q001"] = "Couldn't find ~ character in querry, to denote an attribute name.";
	errorDescription["Q002"] = "Such root tag does not exist.";
	errorDescription["Q003"] = "Such child tag does not exist.";
	errorDescription["Q004"] = "Such attribute does not exist for specified tag.";
}

HRMLparser::~HRMLparser()
{
	for (auto e : this->listOfElems)
		delete e;
}

void HRMLparser::parseHRMLdocument(vector<string>& lines)
{
	extractTagsAndAttribs(lines);
	validateElementsList();
}

string HRMLparser::processQuerry(string querry)
{
	stringstream ss(querry);
	vector<string> tagsChain;
	string attribute;
	string tok;

	while (!ss.eof())
	{
		getline(ss, tok, '.');
		tagsChain.push_back(tok);
	}

	string lastTagAndAttr(tagsChain.back());
	auto found = lastTagAndAttr.find('~');
	tagsChain.erase(tagsChain.end()-1);
	if ( found == string::npos)	{
		throw ParsingError(this, "Q001");
	}
	else {
		tagsChain.push_back(string(lastTagAndAttr.begin(), lastTagAndAttr.begin() + found));
		attribute = string(lastTagAndAttr.begin() + found +1, lastTagAndAttr.end());
	}

	if (tagsChain.front() != rootTag->name)
		throw ParsingError(this, "Q002");

	Tag *mostRecentTag = rootTag;
	for (unsigned int i = 1; i < tagsChain.size(); i++)
	{
		Tag *childTag = getChildTag(mostRecentTag, tagsChain.at(i));
		if (childTag == nullptr) throw ParsingError(this, "Q003");
		mostRecentTag = childTag;
	}

	string value = getAttributeValue(mostRecentTag, attribute);
	if (value == "NULL") throw ParsingError(this, "Q004");

	return value;
}