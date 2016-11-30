#include "rapidxml_utils.hpp"

int main(){

	rapidxml::file<> xmlFile("test.xml");
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

}
