#ifndef VM_CLASS_HPP
# define VM_CLASS_HPP

#include "class/lexer.class.hpp"
#include "class/parser.class.hpp"
#include "class/AvmException.class.hpp"
#include "struct.hpp"
#include <memory>

class parser;
class lexer;

class vm
{

	public:

		static t_options options;


											vm(void);
											vm(vm const &src);
		std::shared_ptr<lexer>							getLexer(void) const;
		std::shared_ptr<parser>							getParser(void) const;
		std::vector<std::string>	getCommands(void) const;
		void								setCommands(std::vector<std::string> const commands);
											~vm(void);

		vm &								operator=(vm const &rhs);

	private:

		std::shared_ptr<lexer>							_lexer;
		std::shared_ptr<parser>							_parser;
		std::vector<std::string>	_commands;
};

#endif
