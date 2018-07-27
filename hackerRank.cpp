// hackerRankTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//////////////////////////////////////////

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
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
	/* Nested classes */
	/* Exception specific for a parser */
	class HRLMParsingException : public exception {
	private:
		const char* msg;
	public:
		HRLMParsingException(const char* str) { msg = str; }
		const char* what() const throw () override { return this->msg; }
	};

	/* Possible elements */
	enum class ElemType {
		TAG_OPEN,
		TAG_CLOSE,
		ATTRIB,
		VALUE,
		EQUAL_SGN,
		GT
	};

	class Element {
	public:
		ElemType elemType;
		virtual ~Element(){};
	};

	class Tag : public Element {
	public:
		string name;
		bool hasEnding = false;
		map<Attrib*, Value*> attrs;
		vector<Tag*> childs;
		//~Tag() {};
	};

	class TagClose : public Element {
	public:
		string name;
		//~TagClose() {};
	};

	class Attrib : public Element {
	public:
		string name;
	};

	class Value : public Element {
	public:
		string value;
	};

	class EqualSign : public Element {};
	class GreaterThan : public Element {};

	/**************************************************************/

private:
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

		string val(tok.begin(), tok.end());

		if (val.front() != '"' || val.back() != '"')
			throw HRLMParsingException("Invalid value. Missing quote character.");

		string val1(val.begin() + 1, val.end() - 1);
		for (auto c : val1)
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
				tc->name = t.substr(2);
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
				v->value = t;
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
			throw HRLMParsingException("First element must be a tag-opening element");
		else {
			/* We can also use dynamic cast here, but we are sure at this point that
			 * we point to Tag so we can use static_cast */
			Tag *t = static_cast<Tag*>(firstElem);
		}

		Element *prevElem = firstElem;

		for (auto it = listOfElems.begin()+1; it < listOfElems.end(); it++)
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
						
						break;
					}
					default: throw HRLMParsingException("New tag may appear only"
						     " after closing of a tag or within a tag.");
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

						break;
					}
					default: throw HRLMParsingException("New atrib may appear only"
						" inside of a tag, after previous attribute value or after"
						" tag opening.");
				}
				break;
			}
			case ElemType::EQUAL_SGN:
			{
				switch (prevElem->elemType)
				{
					// These are valid cases
					case ElemType::ATTRIB:
					{

						break;
					}
					default: throw HRLMParsingException("Equal sign may appear only"
						" after inside of a tag, after previous attribute value .");
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

						break;
					}
					default: throw HRLMParsingException("Attribute value may appear only"
						" after the equal sign.");
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

						break;
					}
					default: throw HRLMParsingException("Closing tag may appear only"
						" after another closing tag or after closing of 'tag opening'.");
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
						//TODO: may appear also after tag open (in case of no attribs)
					{

						break;
					}
					default: throw HRLMParsingException("Closing of 'tag opening'section"
						" may appear only after a value or after a 'tag opening' in case"
					    " there is no attributes.");
				}
				break;
			}
			default:
			{
				throw HRLMParsingException("Validation failure. No such element.");
			}
			}

			prevElem = e;
		}
	}
};

/* Main function for testing */
int main() {
	int nOfLines, nOfQueries;

	cin >> nOfLines >> nOfQueries;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<string> lines;
	string line;

	for (int i = 0; i < nOfLines; i++)
	{
		getline(cin, line);
		lines.push_back(line);
	}

	HRMLparser parser;
	try {
		parser.extractTagsAndAttribs(lines);
		parser.validateElementsList();
	}
	catch (HRMLparser::HRLMParsingException e) {
		cerr << e.what();
	}
	catch (...) {
		cerr << "Unknown exception";
	}

	return 0;
}