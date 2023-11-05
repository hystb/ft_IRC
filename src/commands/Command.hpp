#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <vector>
#include <exception>

class Command
{
private:
	std::string 				_input;
	std::string 				_command;
	std::vector<std::string>	_parameters;
	std::string					_content;

	void parse(void);

	Command(void);
public:
	/* canonical form */
	~Command(void);
	Command& operator=(const Command &parent);
	Command(const Command &parent);

	/* constructor */
	Command(std::string input);

	/* getters */
	std::string&			 	getInput(void);
	std::string& 				getCommand(void);
	std::vector<std::string>& 	getParameters(void);
	std::string&				getContent(void);


	/* exceptions */
	class invalidException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Invalid command syntax !"); };
	};
};
#endif