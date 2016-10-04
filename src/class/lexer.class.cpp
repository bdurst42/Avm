#include "class/lexer.class.hpp"

lexer::lexer(void)
{
	return ;
}

lexer::lexer(lexer const &src)
{
	*this = src;

	return;
}

lexer::~lexer(void)
{
	return ;
}

bool	lexer::_isDigit(const char c) const
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

bool	lexer::_isLowerAlpha(const char c) const
{
	if (c >= 'a' && c <= 'z')
		return 1;
	else
		return 0;
}

token								lexer::_getToken(const std::string command, unsigned int *pos) const
{
	token	token;

	while (*pos > 0 && command[*pos] && command[*pos] == ' ')
		++(*pos);
	if (command[*pos] == '(') {
		token.type = leftBracket;
		token.str = "(";
		++(*pos);
	}
	else if (command[*pos] == ')') {
		token.type = rightBracket;
		token.str = ")";
		++(*pos);
	}
	else if (command[*pos] == ';') {
		token.type = Comment;
		token.str = ";";
		*pos = command.length();
	}
	else if (command[*pos] == '.') {
		token.type = Dot;
		token.str = ".";
		++(*pos);
	}
	else if (command[*pos] == '-') {
		token.type = Sign;
		token.str = "-";
		++(*pos);
	}
	else if (_isDigit(command[*pos])) {
		int	i;
		for (i = *pos; command[i] && _isDigit(command[i]); ++i)
			;
		token.type = Nb;
		token.str = command.substr(*pos, i - *pos);
		*pos = i;
	}
	else if (_isLowerAlpha(command[*pos])) {
		int	i;
		for (i = *pos; command[i] && (_isLowerAlpha(command[i]) || _isDigit(command[i])); ++i)
			;
		token.type = String;
		token.str = command.substr(*pos, i - *pos);
		*pos = i;
	}
	else {
		token.type = Unknow;
		token.str = command[*pos];
		*pos = command.length();
	}
	return (token);
}

std::vector<std::vector<token> >	lexer::checkCommands(std::vector<std::string> commands) const
{
	std::vector<std::vector<token> >	commandsTokens;

	for(unsigned int i = 0; i < commands.size(); i++)
	{
		std::vector<token> tokens;
		unsigned int pos = 0;
		while (pos < commands[i].length())
			tokens.push_back(_getToken(commands[i], &pos));
		if (pos > 1)
			commandsTokens.push_back(tokens);
	}
	return (commandsTokens);
}

lexer &	lexer::operator=(lexer const &rhs)
{
		  static_cast<void>(rhs);
		  return (*this);
}
