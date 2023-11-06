#ifndef COMMAND_HPP
#define COMMAND_HPP

# include <vector>
# include <iostream>
# include <exception>
class CommandHandler;
class Client;

class Command
{
private:
	std::string 				_input;
	std::string 				_command;
	std::vector<std::string>	_parameters;
	std::string					_content;
	// mettre le client la !

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
	const std::string&			 	getInput(void) const;
	const std::string& 				getCommand(void) const;
	const std::vector<std::string>& 	getParameters(void) const;
	const std::string&				getContent(void) const;


	/* exceptions */
	class invalidException : public std::exception {
		public:
			virtual const char * what() const throw() { return ("Invalid command syntax !"); };
	};
};
#endif