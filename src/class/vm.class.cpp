#include "class/vm.class.hpp"

t_options vm::options = {false, false};

vm::vm(void): _commands(0)
{
	_lexer = std::make_shared<lexer>();
	_parser = std::make_shared<parser>();
}

vm::vm(vm const &src)
{
	*this = src;

	return;
}

vm::~vm(void)
{
	return ;
}

std::shared_ptr<lexer>	vm::getLexer(void) const
{
	return this->_lexer;
}

std::shared_ptr<parser>	vm::getParser(void) const
{
	return this->_parser;
}

std::vector<std::string>	vm::getCommands(void) const
{
	return (this->_commands);
}

void	vm::setCommands(std::vector<std::string> const commands)
{
	this->_commands = commands;
}

vm &	vm::operator=(vm const &rhs)
{
	if (this != &rhs)
	{
		this->_lexer = rhs.getLexer();
		this->_parser = rhs.getParser();
	}
	
	return (*this);
}
