#include "stdafx.h" 
#include "HRMLparser.h"

/* Main function for testing */
int main() {

	vector<string> lines;

	/*
	int nOfLines, nOfQueries;
	cin >> nOfLines >> nOfQueries;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string line;

	for (int i = 0; i < nOfLines; i++)
	{
	getline(cin, line);
	lines.push_back(line);
	}
	*/

	lines.push_back("<tag1 a1 = \"v1\">");
	lines.push_back("<tag2 a2 = \"v2\">");
	lines.push_back("<tag3 a3 = \"v3\" a4 = \"v4\">");
	lines.push_back("<tag4 a1 = \"v33\" a2 = \"v44\">");
	lines.push_back("</tag4>");
	lines.push_back("</tag3>");
	lines.push_back("</tag2>");
	lines.push_back("</tag1>");

	HRMLparser parser;
	try {
		parser.extractTagsAndAttribs(lines);
		parser.validateElementsList();
	}
	catch (HRMLparser::ParsingError e) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown exception" << endl;
	}

	return 0;
}