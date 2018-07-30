#include "HRMLparser.h"

/* Main function for testing */
int main() {

	vector<string> lines;

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
		parser.parseHRMLdocument(lines);
		string val = parser.processQuerry("tag1.tag2.tag3~a2");
		cout << "VALUE of tag1.tag2.tag3~a2 is : " << val << endl;
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