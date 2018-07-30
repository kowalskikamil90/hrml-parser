#include "gtest/gtest.h"
#include "../HRMLparser.h"
#include <vector>
#include <string>

using namespace std;

class HRMLgeneralParserTests : public ::testing::Test {
protected:
	void SetUp() override {
		parser = new HRMLparser();
	}

	void TearDown() override {
		delete parser;
	}

	HRMLparser *parser;
};

TEST_F(HRMLgeneralParserTests, parseSimpleDocOnelineTest)
{
	vector<string> lines;

	lines.push_back(
		"<tag1 a1 = \"1VALa1\"> "
		"	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"	</tag2> "
		"</tag1>");

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
}

TEST_F(HRMLgeneralParserTests, parseSimpleDocMultilinesTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("	</tag2>");
	lines.push_back("</tag1>");

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
}

TEST_F(HRMLgeneralParserTests, parseBigDocOnelineTest)
{
	vector<string> lines;

	lines.push_back(
		"<tag1 a1 = \"1VALa1\"> "
		"	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"			</tag4> "
		"		</tag3> "
		"	</tag2> "
		"	<tag5> "
		"	</tag5> "
		"	<tag6 a1 = \"6VALa1\" > "
		"	</tag6> "
		"</tag1>");

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
}

TEST_F(HRMLgeneralParserTests, parseBigDocMultilinesTest)
{
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

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
}