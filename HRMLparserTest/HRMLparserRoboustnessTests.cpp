#include "gtest/gtest.h"
#include "../HRMLparser.h"
#include <vector>
#include <string>

using namespace std;

class HRMLparserRoboustnessTests : public ::testing::Test {
protected:
	void SetUp() override {

		parser = new HRMLparser();

		bigHRMLmultilineDoc = new vector<string>();

		bigHRMLmultilineDoc->push_back("<tag1 a1 = \"1VALa1\">");
		bigHRMLmultilineDoc->push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("			</tag4>");
		bigHRMLmultilineDoc->push_back("		</tag3>");
		bigHRMLmultilineDoc->push_back("	</tag2>");
		bigHRMLmultilineDoc->push_back("	<tag5>");
		bigHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("													</tag4>");
		bigHRMLmultilineDoc->push_back("												</tag3>");
		bigHRMLmultilineDoc->push_back("											</tag2>");
		bigHRMLmultilineDoc->push_back("										</tag4>");
		bigHRMLmultilineDoc->push_back("									</tag3>");
		bigHRMLmultilineDoc->push_back("								</tag2>");
		bigHRMLmultilineDoc->push_back("							</tag4>");
		bigHRMLmultilineDoc->push_back("						</tag3>");
		bigHRMLmultilineDoc->push_back("					</tag2>");
		bigHRMLmultilineDoc->push_back("				</tag4>");
		bigHRMLmultilineDoc->push_back("			</tag3>");
		bigHRMLmultilineDoc->push_back("		</tag2>");
		bigHRMLmultilineDoc->push_back("	</tag5>");
		bigHRMLmultilineDoc->push_back("	<tag6 a1 = \"6VALa1\" >");
		bigHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		bigHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		bigHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		bigHRMLmultilineDoc->push_back("													</tag4>");
		bigHRMLmultilineDoc->push_back("												</tag3>");
		bigHRMLmultilineDoc->push_back("											</tag2>");
		bigHRMLmultilineDoc->push_back("										</tag4>");
		bigHRMLmultilineDoc->push_back("									</tag3>");
		bigHRMLmultilineDoc->push_back("								</tag2>");
		bigHRMLmultilineDoc->push_back("							</tag4>");
		bigHRMLmultilineDoc->push_back("						</tag3>");
		bigHRMLmultilineDoc->push_back("					</tag2>");
		bigHRMLmultilineDoc->push_back("				</tag4>");
		bigHRMLmultilineDoc->push_back("			</tag3>");
		bigHRMLmultilineDoc->push_back("		</tag2>");
		bigHRMLmultilineDoc->push_back("	</tag6>");
		bigHRMLmultilineDoc->push_back("</tag1>");

		bigHRMLonelineDoc = new vector<string>();

		bigHRMLonelineDoc->push_back(
		"<tag1 a1 = \"1VALa1\"> "
		"	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"			</tag4> "
		"		</tag3> "
		"	</tag2> "
		"	<tag5> "
		"		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"													</tag4> "
		"												</tag3> "
		"											</tag2> "
		"										</tag4> "
		"									</tag3> "
		"								</tag2> "
		"							</tag4> "
		"						</tag3> "
		"					</tag2> "
		"				</tag4> "
		"			</tag3> "
		"		</tag2> "
		"	</tag5> "
		"	<tag6 a1 = \"6VALa1\" > "
		"		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\"> "
		"													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\"> "
		"													</tag4> "
		"												</tag3> "
		"											</tag2> "
		"										</tag4> "
		"									</tag3> "
		"								</tag2> "
		"							</tag4> "
		"						</tag3> "
		"					</tag2> "
		"				</tag4> "
		"			</tag3> "
		"		</tag2> "
		"	</tag6> "
		"</tag1>");

		hugeHRMLmultilineDoc = new vector<string>();

		hugeHRMLmultilineDoc->push_back("<tag1 a1 = \"1VALa1\">");
		hugeHRMLmultilineDoc->push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("		<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("			</tag4>");
		hugeHRMLmultilineDoc->push_back("		</tag3>");
		hugeHRMLmultilineDoc->push_back("	</tag2>");
		hugeHRMLmultilineDoc->push_back("	<tag5>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag5>");
		hugeHRMLmultilineDoc->push_back("	<tag55>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag55>");
		hugeHRMLmultilineDoc->push_back("	<tag66>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag66>");
		hugeHRMLmultilineDoc->push_back("	<tag77>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag77>");
		hugeHRMLmultilineDoc->push_back("	<tag88>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag88>");
		hugeHRMLmultilineDoc->push_back("	<tag99>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag99>");
		hugeHRMLmultilineDoc->push_back("	<tag100>");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag100>");
		hugeHRMLmultilineDoc->push_back("	<tag6 a1 = \"6VALa1\" >");
		hugeHRMLmultilineDoc->push_back("		<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("			<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("				<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("					<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("						<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("							<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("								<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("									<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("										<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("											<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
		hugeHRMLmultilineDoc->push_back("												<tag3 a1 = \"3VALa1\" a2 = \"3VALa2\">");
		hugeHRMLmultilineDoc->push_back("													<tag4 a1 = \"4VALa1\" a2 = \"4VALa2\">");
		hugeHRMLmultilineDoc->push_back("													</tag4>");
		hugeHRMLmultilineDoc->push_back("												</tag3>");
		hugeHRMLmultilineDoc->push_back("											</tag2>");
		hugeHRMLmultilineDoc->push_back("										</tag4>");
		hugeHRMLmultilineDoc->push_back("									</tag3>");
		hugeHRMLmultilineDoc->push_back("								</tag2>");
		hugeHRMLmultilineDoc->push_back("							</tag4>");
		hugeHRMLmultilineDoc->push_back("						</tag3>");
		hugeHRMLmultilineDoc->push_back("					</tag2>");
		hugeHRMLmultilineDoc->push_back("				</tag4>");
		hugeHRMLmultilineDoc->push_back("			</tag3>");
		hugeHRMLmultilineDoc->push_back("		</tag2>");
		hugeHRMLmultilineDoc->push_back("	</tag6>");
		hugeHRMLmultilineDoc->push_back("</tag1>");
	}

	void TearDown() override {
		delete parser;
		delete bigHRMLmultilineDoc;
		delete bigHRMLonelineDoc;
		delete hugeHRMLmultilineDoc;
	}

	HRMLparser *parser;
	vector<string> *bigHRMLmultilineDoc;
	vector<string> *bigHRMLonelineDoc;
	vector<string> *hugeHRMLmultilineDoc;
};

TEST_F(HRMLparserRoboustnessTests, process100QuerriesSimpleOnelineTest)
{
	vector<string> lines;

	lines.push_back(
		"<tag1 a1 = \"1VALa1\"> "
		"	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\"> "
		"	</tag2> "
		"</tag1>");

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry("tag1~a1"));
		ASSERT_STREQ(result.c_str(), "1VALa1");
	}
}

TEST_F(HRMLparserRoboustnessTests, process100QuerriesSimpleMultilineTest)
{
	vector<string> lines;

	lines.push_back("<tag1 a1 = \"1VALa1\">");
	lines.push_back("	<tag2 a1 = \"2VALa1\" a2 = \"2VALa2\">");
	lines.push_back("	</tag2>");
	lines.push_back("</tag1>");

	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(lines));
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry("tag1~a1"));
		ASSERT_STREQ(result.c_str(), "1VALa1");
	}
}

TEST_F(HRMLparserRoboustnessTests, process100QuerriesOnelineTest)
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
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2.tag3~a2"));
		ASSERT_STREQ(result.c_str(), "3VALa2");
	}
}

TEST_F(HRMLparserRoboustnessTests, process100QuerriesMultilineTest)
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
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry("tag1.tag2.tag3~a2"));
		ASSERT_STREQ(result.c_str(), "3VALa2");
	}
}

TEST_F(HRMLparserRoboustnessTests, parseBigMultilineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*bigHRMLmultilineDoc));
}

TEST_F(HRMLparserRoboustnessTests, processQuerryBigMultilineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*bigHRMLmultilineDoc));
	ASSERT_NO_THROW(result = parser->processQuerry(
		"tag1.tag5.tag2.tag3.tag4.tag2.tag3.tag4.tag2.tag3.tag4~a2"));
	ASSERT_STREQ(result.c_str(), "4VALa2");
}

TEST_F(HRMLparserRoboustnessTests, process100QuerriesBigMultilineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*bigHRMLmultilineDoc));
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry(
			"tag1.tag5.tag2.tag3.tag4.tag2.tag3.tag4.tag2.tag3.tag4~a2"));
		ASSERT_STREQ(result.c_str(), "4VALa2");
	}
}

TEST_F(HRMLparserRoboustnessTests, processQuerryBigOnelineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*bigHRMLonelineDoc));
	ASSERT_NO_THROW(result = parser->processQuerry(
		"tag1.tag5.tag2.tag3.tag4.tag2.tag3.tag4.tag2.tag3.tag4~a2"));
	ASSERT_STREQ(result.c_str(), "4VALa2");
}

TEST_F(HRMLparserRoboustnessTests, process100QuerriesBigOnelineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*bigHRMLonelineDoc));
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry(
			"tag1.tag5.tag2.tag3.tag4.tag2.tag3.tag4.tag2.tag3.tag4~a2"));
		ASSERT_STREQ(result.c_str(), "4VALa2");
	}
}

TEST_F(HRMLparserRoboustnessTests, processQuerryHugeOnelineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*hugeHRMLmultilineDoc));
	ASSERT_NO_THROW(result = parser->processQuerry(
		"tag1.tag100.tag2.tag3.tag4.tag2.tag3.tag4.tag2.tag3.tag4~a2"));
	ASSERT_STREQ(result.c_str(), "4VALa2");
}

TEST_F(HRMLparserRoboustnessTests, process100QuerriesHugeOnelineTest)
{
	string result;

	ASSERT_NO_THROW(parser->parseHRMLdocument(*hugeHRMLmultilineDoc));
	for (int i = 0; i < 100; i++)
	{
		ASSERT_NO_THROW(result = parser->processQuerry(
			"tag1.tag99.tag2.tag3.tag4.tag2.tag3.tag4.tag2.tag3.tag4~a2"));
		ASSERT_STREQ(result.c_str(), "4VALa2");
	}
}