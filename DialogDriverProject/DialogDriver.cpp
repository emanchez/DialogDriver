/*
	Program by Emmanuel Sanchez (emanchez on github) (sanchez.emmanuelm@gmail.com)
	This will read an xml file and output it as a text-adventure style interactive program
*/
#include "DialogDriver.h"
#include <iostream>

DialogDriver::DialogDriver() {

}

DialogDriver::~DialogDriver(){
}

void DialogDriver::load_xml(std::string filename) { // loads xml document
	pugi::xml_parse_result result = xml_file.load_file(filename.c_str());
	if (!result) {
		std::cout << "Fatal error: could not load xml file! (" << filename << ")" << std::endl;
	}
}

void DialogDriver::load_head(std::string node, std::string attr_name, std::string attr_value) { // loads main xml node by element name (head node)
	head_node = xml_file.find_child_by_attribute(node.c_str(), attr_name.c_str(), attr_value.c_str());
	if (!head_node) {
		std::cout << "Error in loading head node" << std::endl;
	}
	
}

void DialogDriver::load_event(std::string node_name, std::string node_attr_name, std::string node_attr_val) { // YOU MUST HAVE HEAD NODE LOADED
	if (!head_node) {
		std::cout << "Error in loading event node: Head node not loaded" << std::endl;
	}
	else { // load dialog event (EXAMPLE: `<event name="value">` => `head_node.find_child_by_attribute("event", "name", "value)` )
		event_node = head_node.find_child_by_attribute(node_name.c_str(), node_attr_name.c_str(), node_attr_val.c_str());
		if (!event_node) {
			std::cout << "Error in loading event node" << std::endl;
		}
		else {
			load_node("dialog", "id", "1.1"); // standard leading dialog node for every dialog tree; must initialize all event nodes with this node template <dialog id="1.1">
		}
	}

}

int DialogDriver::load_node(std::string node_child, std::string node_attr_name, std::string node_attr_val) { // YOU MUST HAVE BOTH HEAD AND EVENT NODES LOADED
	if (!head_node) {
		std::cout << "Error! Head not loaded!" << std::endl;
	}
	if (!event_node) {
		std::cout << "Error! Event not loaded!" << std::endl;
	}
	tree_node = new DialogTreeNode; // wipes previous node data (or creates new node if none exists)
	dialog_node = event_node.find_child_by_attribute(node_child.c_str(), node_attr_name.c_str(), node_attr_val.c_str());
	// load text into tree_node
	tree_node->text = dialog_node.child("text").text().get();
	//std::cout << tree_node->text << std::endl; // debug

	// process node
	if ((std::string)dialog_node.attribute("type").value() == "tree") {
		//std::cout << "This is a tree node." << std::endl; //debug

		// load options from xml file (dialog_node) into tree_node as a vector of xml_nodes
		for (pugi::xml_node option : dialog_node.children("option")) {
			tree_node->options.push_back(option.text().get());
		}
		return 1; // loaded node success; still within a tree code
	}
	else if ((std::string)dialog_node.attribute("type").value() == "end") {
		return 0; // loaded node success; exit from tree success code
	}
	else {
		// std::cout << dialog.attribute("type").value() << std::endl; //debug
		std::cout << "Error in loading options" << std::endl; //debug
		return -1; // error code (probably something is wrong with the xml file if the correct head_node is loaded)
	}
}

void DialogDriver::show_options() {
	// std::cout << tree_node->options.size() << std::endl; //debug
	if (!tree_node) {
		std::cout << "Error displaying options (tree node not loaded)" << std::endl;
	}
	else { // print node options with counter (starting at 1)
		int counter = 0;
		for (std::string option : tree_node->options) {
			std::cout << "[" << ++counter << "] " << option << "\n";
		}

		std::cout << std::endl;
	}
}
std::vector<std::string> DialogDriver::get_options() {
	// std::cout << tree_node->options.size() << std::endl; //debug
	if (!tree_node) {
		std::cout << "Error getting options (tree node not loaded)" << std::endl;
	}
	return tree_node->options;
}

int DialogDriver::load_next(int sel) {
	std::string next_node_id = dialog_node.find_child_by_attribute("option", "id", std::to_string(sel).c_str()).attribute("goto").value();
	return load_node("dialog", "id", next_node_id);

}

int DialogDriver::prompt_selection() { // shows options and waits for user input
	int sel;
	
	do {
		show_options();
		std::cin >> sel;
		if (sel <= 0 || sel > tree_node->options.size())
			std::cout << "Not a valid option" << std::endl;

	} while (sel <= 0 || sel > tree_node->options.size());
	return sel;
}




std::string DialogDriver::get_text() {
	if (!tree_node) {
		std::cout << "Fatal error: no node exists in dialog driver" << std::endl;
		return "";
	}
	else {
		return tree_node->text;
	}
}
