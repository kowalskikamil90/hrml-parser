#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <map>
#include <exception>
#include <cctype>

using namespace std;

class HRMLparser {

public:
	/////////////////////////////////////////////////////////////////////
	/* Exception specific for a parser, exposed to a user of a library.*/
	/////////////////////////////////////////////////////////////////////

	class ParsingError : public exception {
	private:
		string errorDes;
		string errorCode;
	public:
		ParsingError(HRMLparser *parser, string errCode);
		const char* what() const override;
		string getErrorCode();
		string getErrorDescrition();
	};

	/////////////////////////////////////////////////////////////////////
	/* Public interface */
	/////////////////////////////////////////////////////////////////////

	void parseHRMLdocument(vector<string>& lines);
	string processQuerry(string querry);
	HRMLparser();
	~HRMLparser();

private:
	/////////////////////////////////////////////////////////////////////
	/* Nested enum type */
	/////////////////////////////////////////////////////////////////////

	enum class ElemType;

	/////////////////////////////////////////////////////////////////////
	/* Nested classes */
	/////////////////////////////////////////////////////////////////////

	class Element;
	class Tag;
	class TagClose;
	class Attrib;
	class Value;
	class EqualSign;
	class GreaterThan;

	/////////////////////////////////////////////////////////////////////
	/* Private members */
	/////////////////////////////////////////////////////////////////////

	Tag *rootTag;
	vector<string> tokens;
	vector<Element*> listOfElems;
	map<string, string> errorDescription;

	/////////////////////////////////////////////////////////////////////
	/* Private member functions */
	/////////////////////////////////////////////////////////////////////

	void leaveOnlyAlNumChars(string& s);
	bool startsWith(string &s, char c);
	bool isAlNum(string &s);
	bool startsWith(string &s, string beg);
	bool endsWith(string &s, string beg);
	bool endsWith(string &s, char c);
	bool isTagOpenningToken(string tok, bool &closing);
	bool isTagClosingToken(string tok);
	bool isAttrib(string tok);
	bool isValue(string tok, bool &closing);
	bool isEqualSign(string tok);
	bool isGrThan(string tok);

	void validateElementsList();
	void extractTagsAndAttribs(vector<string>& lines);

	Tag* getChildTag(Tag *parent, string childsName);
	string getAttributeValue(Tag *mostRecentTag, string attribute);
};
