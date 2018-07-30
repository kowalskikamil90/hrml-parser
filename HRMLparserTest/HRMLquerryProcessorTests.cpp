#include "gtest/gtest.h"
#include "../HRMLparser.h"
#include <vector>
#include <string>

using namespace std;

class HRMLquerryProcessorTests : public ::testing::Test {
protected:
	void SetUp() override {
		parser = new HRMLparser();
	}

	void TearDown() override {
		delete parser;
	}

	HRMLparser *parser;
};

TEST_F(HRMLquerryProcessorTests, processSimpleQuerryOnelineTest)
{
	vector<string> lines;

	lines.push_back(
		"<tag1 a1 = \"1VALa1\"> "
		"	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"	</tag2> "
		"</tag1>");

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	ASSERT_NO_THROW(result = parser->processQuerry("tag1~a1"));
	ASSERT_STREQ(result.c_str(), "1VALa1");
}

TEST_F(HRMLquerryProcessorTests, processSimpleQuerryMultilineTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("	</tag2>");
	lines.push_back("</tag1>");

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	ASSERT_NO_THROW(result = parser->processQuerry("tag1~a1"));
	ASSERT_STREQ(result.c_str(), "1VALa1");
}

TEST_F(HRMLquerryProcessorTests, processQuerryOnelineTest)
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

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2.tag3~a2"));
	ASSERT_STREQ(result.c_str(), "3VALa2");
}

TEST_F(HRMLquerryProcessorTests, processQuerryMultilineTest)
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

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2.tag3.tag4~a2"));
	ASSERT_STREQ(result.c_str(), "4VALa2");
}

TEST_F(HRMLquerryProcessorTests, processMultiQuerryOnelineTest)
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

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2.tag3.tag4~a2"));
	ASSERT_STREQ(result.c_str(), "4VALa2");
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2~a2"));
	ASSERT_STREQ(result.c_str(), "2VALa2");
	ASSERT_NO_THROW(result = parser->processQuerry("tag1~a1"));
	ASSERT_STREQ(result.c_str(), "1VALa1");
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag6~a1"));
	ASSERT_STREQ(result.c_str(), "6VALa1");
}

TEST_F(HRMLquerryProcessorTests, processMultiQuerryMultilineTest)
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

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2.tag3.tag4~a2"));
	ASSERT_STREQ(result.c_str(), "4VALa2");
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2~a2"));
	ASSERT_STREQ(result.c_str(), "2VALa2");
	ASSERT_NO_THROW(result = parser->processQuerry("tag1~a1"));
	ASSERT_STREQ(result.c_str(), "1VALa1");
	ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag6~a1"));
	ASSERT_STREQ(result.c_str(), "6VALa1");
}