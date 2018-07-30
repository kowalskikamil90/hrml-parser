#include "gtest/gtest.h"
#include "../HRMLparser.h"
#include <vector>
#include <string>

using namespace std;

class HRMLvalidationExceptionsTests : public ::testing::Test {
protected:
	void SetUp() override {
		parser = new HRMLparser();
	}

	void TearDown() override {
		delete parser;
	}

	HRMLparser *parser;
};

class DISABLED_HRMLvalidationExceptionsTests : public ::testing::Test {
protected:
	HRMLparser *parser;
};

TEST_F(HRMLvalidationExceptionsTests, tagNonalfanumericCharactersTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	// NOTE: tag name contains non-alfanumeric character
	lines.push_back("	<ta%%g2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
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

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E001");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, attributeNonalfanumericCharactersTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	// NOTE: attribute name contains non-alfanumeric character
	lines.push_back("	<tag2 a.1 = \"2VALa1\" a2 = \"2VALa2\">");
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

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E002");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, attributeValueMissingEndingQuoteTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Invalid attribute value. Missing ending quote character.
	lines.push_back("			<tag4 a1 = \"4VALa1 a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E003");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, attributeValueMissingStartingQuoteTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Invalid attribute value. Missing starting quote character.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = 4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E004");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(DISABLED_HRMLvalidationExceptionsTests, attributeNoValueBetweenQuotesTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: No attribute value specified between the quotes.
	lines.push_back("			<tag4 a1 = \"\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E005");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, attributeValueNonalfanumericCharactersTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute value may consist of only alfanumeric characters.
	lines.push_back("			<tag4 a1 = \"4VALa1$#\" a2 = 4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E006");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, unexpectedCharacterAfterEqualSignTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Unexpected character after equal sign.
	lines.push_back("			<tag4 a1 =# \"4VALa1\" a2 = 4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E007");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, equalSignNotSeperatedFromAttributeOrValueTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Equal sign must be seperated from attribute name and attribute value.
	lines.push_back("			<tag4 a1 =\"4VALa1\" a2 = 4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E007");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(DISABLED_HRMLvalidationExceptionsTests, unexpectedCharacterAfterTagClosingTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Unexpected character after tag closing.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = 4VALa2\">");
	lines.push_back("			</tag4> a");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E008");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, firstElementNotTagOpeningTest)
{
	vector<string> lines;

	// NOTE: First element must be a tag-opening element.
	lines.push_back("tag1 a1 = \"1VALa1\">");	
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

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E010");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagOpening1Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: New tag may appear only after closing of a tag or within a tag as a subtag.
	lines.push_back("			<tag4 a1 <badtag> = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E011");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagOpening2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: New tag may appear only after closing of a tag or within a tag as a subtag.
	lines.push_back("			<tag4 a1 = <badtag \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E011");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagOpening3Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: New tag may appear only after closing of a tag or within a tag as a subtag.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\" <badtag> >");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E011");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, doubledAttributeNameForATagTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute with such name already exists for this tag.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\" a1 = \"doubledAttrib\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E012");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttribute1Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute may appear only inside of a tag opening section, 
	//       either directly after tag name or after previous attribute value.
	lines.push_back("			<tag4 a1 = attrib \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E013");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttribute2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute may appear only inside of a tag opening section, 
	//       either directly after tag name or after previous attribute value.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> attrib");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E013");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttribute3Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute may appear only inside of a tag opening section, 
	//       either directly after tag name or after previous attribute value.
	lines.push_back("			<tag4 a1 attrib = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E013");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfEqualSign1Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Equal sign may appear only inside of a 'tag opening section', after
	//       attribute name. Between atribute name and value, only one equal sign is allowed.
	lines.push_back("			<tag4 = a1 = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E014");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfEqualSign2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Equal sign may appear only inside of a 'tag opening section', after
	//       attribute name. Between atribute name and value, only one equal sign is allowed.
	lines.push_back("			<tag4 a1 = \"4VALa1\" = a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E014");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfEqualSign3Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Equal sign may appear only inside of a 'tag opening section', after
	//       attribute name. Between atribute name and value, only one equal sign is allowed.
	lines.push_back("			<tag4 a1 = = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E014");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfEqualSign4Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Equal sign may appear only inside of a 'tag opening section', after
	//       attribute name. Between atribute name and value, only one equal sign is allowed.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> =");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E014");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, AttributeDoubledValueTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute already has a value.
	lines.push_back("			<tag4 a1 = \"4VALa1\" \"anotherValue\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E016");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttributeValue1Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute value may appear only after the equal sign.
	lines.push_back("			<tag4 a1 = \"4VALa1\" \"anotherValue\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E016");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttributeValue2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute value may appear only after the equal sign.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 \"anotherValue\" = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E016");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttributeValue3Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Attribute value may appear only after the equal sign.
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> \"anotherValue\" ");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E016");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfAttributeValue4Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
	// NOTE: Attribute value may appear only after the equal sign.
	lines.push_back("			</tag4> \"anotherValue\" ");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E016");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementTagOpeningSectionClosing1Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Closing of 'tag opening'section may appear only after an 
	//       attribute's value or after a 'tag opening' - in case there is no attributes.
	lines.push_back("			<tag4 a1 = >");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E017");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementTagOpeningSectionClosing2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Closing of 'tag opening'section may appear only after an 
	//       attribute's value or after a 'tag opening' - in case there is no attributes.
	lines.push_back("			<tag4 a1 = \"val\" a2 >");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E017");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, closingTagNameDoesntMatchOpening1Test)
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
	// NOTE: Closing tag name doesn't match the opening tag name.
	lines.push_back("</tag11>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E018");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, closingTagNameDoesntMatchOpening2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	// NOTE: Closing tag name doesn't match the opening tag name.
	lines.push_back("	</tag22>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E018");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, closingTagNameDoesntMatchOpening3Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
	// NOTE: Closing tag name doesn't match the opening tag name.
	lines.push_back("			</tag44>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E018");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagClosing1Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Closing tag may appear only after another closing 
	//       tag or after closing of 'tag opening section'.
	lines.push_back("			<tag4 </tag4> a1 = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag44>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E019");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagClosing2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Closing tag may appear only after another closing 
	//       tag or after closing of 'tag opening section'.
	lines.push_back("			<tag4 a1 </tag4> = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag44>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E019");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagClosing3Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Closing tag may appear only after another closing 
	//       tag or after closing of 'tag opening section'.
	lines.push_back("			<tag4 a1 = </tag4> \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag44>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E019");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, incorrectPlacementOfTagClosing4Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
	// NOTE: Closing tag may appear only after another closing 
	//       tag or after closing of 'tag opening section'.
	lines.push_back("			<tag4 a1 = \"4VALa1\" </tag4> a2 = \"4VALa2\">");
	lines.push_back("			</tag44>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E019");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, closingOfTagMissingTest)
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
	// NOTE: Closing of tag missing.
	//		 lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E021");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(DISABLED_HRMLvalidationExceptionsTests, closingOfTagOpeningSectionMissing1Test)
{
	vector<string> lines;

	// NOTE: Closing of tag opening section missing.
	lines.push_back("<tag1 a1 = \"1VALa1\" ");
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

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E022");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(DISABLED_HRMLvalidationExceptionsTests, closingOfTagOpeningSectionMissing2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	// NOTE: Closing of tag opening section missing.
	lines.push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\" ");
	lines.push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
	lines.push_back("			</tag4>");
	lines.push_back("		</tag3>");
	lines.push_back("	</tag2>");
	lines.push_back("	<tag5>");
	lines.push_back("	</tag5>");
	lines.push_back("	<tag6 a1 = \"6VALa1\" >");
	lines.push_back("	</tag6>");
	lines.push_back("</tag1>");

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E022");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLvalidationExceptionsTests, closingOfTagOpeningSectionMissing2Test)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	// NOTE: Closing of tag opening section missing.
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

	try {
		parser->parseHRMLdocument(lines);
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "E022");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

/* Exception ERRORS code that are not reproducable:
 * errorDescription["E005"] = "No attribute value specified between the quotes."; - should be tested
 * errorDescription["E008"] = "Unexpected character after tag closing."; - should be tested
 * errorDescription["E015"] = "Attribute already has a value."; - may not be reachable
 * errorDescription["E022"] = "Closing of 'tag opening section' missing."; - should be tested, throws E011 or E016, may not be reachable
 * errorDescription["E023"] = "Missing equal sign for attribute."; - may not be reachable
 * errorDescription["E024"] = "Missing value for attribute."; - may not be reachable
 * 
 * Exceptions that should not be reproducable:
 * errorDescription["E009"] = "Parsing internal fatal ERROR. No such element.";
 * errorDescription["E020"] = "Validation internal fatal ERROR. No such element.";
 *
 * Exceptions that should not be reproducable but are:
 * errorDescription["E009"] = "Parsing internal fatal ERROR. No such element."; //e.g "... attrib>"
 */