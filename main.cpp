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

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>"); 
	lines.push_back("</tag1>");

	HRMLparser parser;
	try {
		parser.extractTagsAndAttribs(lines);
		parser.validateElementsList();
	}
	catch (HRMLparser::ParsingError e) {
		cerr << "Error code: " << e.getErrorCode() << endl << endl;
		cerr << "Error desc: " << e.what() << endl;
	}
	catch (...) {
		cerr << "Unknown exception" << endl << endl;
	}

	return 0;
}