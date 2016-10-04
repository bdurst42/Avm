#ifndef LEXER_CLASS_HPP
# define LEXER_CLASS_HPP

#include <regex>
#include <iostream>
#include "class/AvmException.class.hpp"
#include "class/vm.class.hpp"
#include "struct.hpp"

class lexer
{

	public:

												lexer(void);
												lexer(lexer const &src);
												~lexer(void);
		std::vector<std::vector<token> >	checkCommands(std::vector<std::string> commands) const;

		lexer &									operator=(lexer const &rhs);

	private:

		token									_getToken(const std::string command, unsigned int *pos) const;
		bool									_isLowerAlpha(const char c) const;
		bool									_isDigit(const char c) const;
};

#endif
