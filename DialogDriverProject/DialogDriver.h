/*
	Program by Emmanuel Sanchez (emanchez on github) (sanchez.emmanuelm@gmail.com)
	This will read an xml file and output it as a text-adventure style interactive program
*/
#pragma once
#include "pugixml.hpp"
#include <vector>
#include <string>


class DialogDriver{
private:
	struct DialogTreeNode{
		std::string text;
		std::vector<std::string> options; // array of options (possible user responses to a query presented)
	};
	pugi::xml_document xml_file;
	pugi::xml_node head_node;
	pugi::xml_node event_node;
	pugi::xml_node dialog_node;
	DialogTreeNode* tree_node = nullptr; // current dialog that is being handled

public:
	DialogDriver();
	~DialogDriver();
	void load_xml(std::string);
	void load_head(std::string, std::string, std::string);
	void load_event(std::string, std::string, std::string);
	int load_node(std::string, std::string, std::string);
	void show_options();
	int prompt_selection();
	int load_next(int);

	std::vector<std::string> get_options();
	std::string get_text();

};

