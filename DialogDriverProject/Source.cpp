/*
	Program by Emmanuel Sanchez (emanchez on github) (sanchez.emmanuelm@gmail.com)
	This will read an xml file and output it as a text-adventure style interactive program
*/

///SAMPLE PROGRAM///

#include <iostream>
#include <string>
#include "DialogDriver.h"

void sample_dialog_driver(std::string, std::string, std::string, std::string, std::string, std::string, std::string);

int main(int argc, char* argv[]) {
	sample_dialog_driver("first.xml", "npc", "name", "villager001", "event", "name", "test");

	system("PAUSE");
	return 0;
}

void sample_dialog_driver(std::string filename, std::string head_node, std::string head_node_attr, std::string attr_value, std::string event_node, std::string event_attr , std::string event_attr_val) {
	DialogDriver driver;
	driver.load_xml(filename);
	driver.load_head(head_node, head_node_attr, attr_value);
	driver.load_event(event_node, event_attr, event_attr_val);
	std::cout << driver.get_text() << std::endl;
	int code = 1;
	while (code > 0) {
		code = driver.load_next(driver.prompt_selection());
		std::cout << driver.get_text() << std::endl;
	}
	if (code < 0)
		std::cout << "There was an error you fuck" << std::endl;
	else
		std::cout << "exit success" << std::endl;
}