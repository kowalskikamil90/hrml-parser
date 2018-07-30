#include "gtest/gtest.h"
#include "../HRMLparser.h"
#include <vector>
#include <string>

using namespace std;

class HRMLquerryProcessingExceptionsExceptionsTests : public ::testing::Test {
protected:
	void SetUp() override {
		parser = new HRMLparser();

		HRMLdoc = new vector<string>();

		HRMLdoc->push_back("<tag1 a1 = \"1VALa1\">");
		HRMLdoc->push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		HRMLdoc->push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		HRMLdoc->push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		HRMLdoc->push_back("			</tag4>");
		HRMLdoc->push_back("		</tag3>");
		HRMLdoc->push_back("	</tag2>");
		HRMLdoc->push_back("	<tag5>");
		HRMLdoc->push_back("	</tag5>");
		HRMLdoc->push_back("	<tag6 a1 = \"6VALa1\" >");
		HRMLdoc->push_back("	</tag6>");
		HRMLdoc->push_back("</tag1>");
	}

	void TearDown() override {
		delete parser;
		delete HRMLdoc;
	}

	HRMLparser *parser;
	vector<string> *HRMLdoc;
};

class DISABLED_HRMLquerryProcessingExceptionsExceptionsTests : public ::testing::Test {
protected:
	HRMLparser * parser;
	vector<string> *HRMLdoc;
};

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, noAttributeDenotingCharacter1Test)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: No ~ character to denote an attribute
		parser->processQuerry("tag1.tag2.tag3.tag4*a1");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q001");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, noAttributeDenotingCharacter2Test)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: No ~ character to denote an attribute
		parser->processQuerry("tag2.tag44*atrib");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q001");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, invalidRootTagNameTest)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: Such root tag does not exist.
		parser->processQuerry("tag11.tag2.tag3.tag4~a1");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q002");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, invalidChildTagName1Test)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: Such child tag does not exist.
		parser->processQuerry("tag1.tag22.tag3.tag4~a1");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q003");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, invalidChildTagName2Test)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: Such child tag does not exist.
		parser->processQuerry("tag1.tag2.tag3.tag44~a1");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q003");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, invalidAttributeName1Test)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: Such attribute does not exist for specified tag.
		parser->processQuerry("tag1.tag2.tag3.tag4~a3");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q004");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}

TEST_F(HRMLquerryProcessingExceptionsExceptionsTests, invalidAttributeName2Test)
{
	try {
		parser->parseHRMLdocument(*HRMLdoc);
		// NOTE: Such attribute does not exist for specified tag.
		parser->processQuerry("tag1.tag5~someAttrib");
	}
	catch (HRMLparser::ParsingError &pe) {
		ASSERT_STREQ(pe.getErrorCode().c_str(), "Q004");
	}
	catch (...) {
		FAIL() << "Unexpected exception cought...";
	}
}