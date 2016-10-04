#include "class/parser.class.hpp"
#include "class/vm.class.hpp"
#include <cmath>
#include <sstream>

parser::parser(void)
{
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("push", &parser::_push));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("pop", &parser::_pop));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("assert", &parser::_assert));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("add", &parser::_add));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("sub", &parser::_sub));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("mul", &parser::_mul));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("div", &parser::_div));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("mod", &parser::_mod));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("pow", &parser::_pow));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("max", &parser::_max));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("min", &parser::_min));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("avg", &parser::_avg));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("print", &parser::_print));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("dump", &parser::_dump));
	this->_instructions.insert(std::pair<std::string, void (parser::*)(void)>("exit", &parser::_exit));
	this->_factory = std::make_shared<OperandFactory>();
}

parser::parser(parser const &src)
{
	*this = src;

	return;
}

parser::~parser(void)
{
	return ;
}

eOperandType	parser::_getType(std::string type)
{
 	if (!type.compare("int8"))
			return Int8;
 	else if (!type.compare("int16"))
 			return Int16;
 	else if (!type.compare("int32"))
 			return Int32;
 	else if (!type.compare("float"))
 			return Float;
 	return Double;	
}

char	parser::_checkType(token token)
{
	if (token.type != String || token.str.length() > 6)
		return -1;
	else if (!token.str.compare("float") || !token.str.compare("double"))
		return 1;
	else if (!token.str.compare("int8") || !token.str.compare("int16") || !token.str.compare("int32"))
		return 0;
	else
		return -1;
}

char	parser::_checkInstruction(token token)
{
	if (token.type == Comment)
		return 2;
	if (token.type != String || token.str.length() > 6)
		return -1;
	else if (!token.str.compare("push") || !token.str.compare("assert"))
		return 1;
	else if (!token.str.compare("pop") || !token.str.compare("add") || !token.str.compare("sub") || !token.str.compare("div") || !token.str.compare("mul") || !token.str.compare("mod") || !token.str.compare("pow") || !token.str.compare("avg") || !token.str.compare("min") || !token.str.compare("max") || !token.str.compare("print") || !token.str.compare("dump") || !token.str.compare("exit"))
		return 0;
	else
		return -1;
}

bool	parser::_checkNumberOfTokens(std::vector<token> tokens, char typeInstruction)
{
	if (!typeInstruction && tokens.size() > 2)
		return false;
	else if (typeInstruction && (tokens.size() < 5 || tokens.size() > 9))
		return false;
	return true;
}

std::string	parser::_checkOrderOfTokens(std::vector<token> tokens, char typeInstruction, int *type)
{
	std::stringstream nbStr;

	if (!typeInstruction) {
		if (tokens.size() > 1 && tokens[1].type != Comment)
			return "";
		nbStr << "ok";
	}
	else {
		*type = _checkType(tokens[1]);
		unsigned int i = 2;
		if (*type == -1 || tokens[i++].type != leftBracket)
			return "";
		else {
			if (tokens[i].type == Sign)
			{
				nbStr << tokens[i].str;
				if (tokens[++i].type != Nb) 
					return "";
				else
				{
					nbStr << tokens[i].str;
					if (!*type && (tokens[++i].type != rightBracket || (++i < tokens.size() && tokens[i].type != Comment)))
						return "";
					else if (*type) {
						if (tokens[++i].type == Dot) {
							nbStr << tokens[i].str << tokens[i + 1].str;
							if (tokens[++i].type != Nb || (tokens[++i].type != rightBracket || (++i < tokens.size() && tokens[i].type != Comment)))
								return "";
						}
						else if (tokens[i].type != rightBracket || (++i < tokens.size() && tokens[i].type != Comment))
							return "";
					}
				}
			}
			else if (tokens[i].type == Nb)
			{
				nbStr << tokens[i].str;
				if (!*type && (tokens[++i].type != rightBracket || (++i < tokens.size() && tokens[i].type != Comment)))
					return "";
				else if (*type) {
					if (tokens[++i].type == Dot) {
						nbStr << tokens[i].str << tokens[i + 1].str;
						if (tokens[++i].type != Nb || (tokens[++i].type != rightBracket || (++i < tokens.size() && tokens[i].type != Comment)))
							return "";
					}
					else if (tokens[i].type != rightBracket || (++i < tokens.size() && tokens[i].type != Comment))
						return "";
				}
			}
			else
				return "";
		}
	}
	return nbStr.str();
}

void	parser::manageCommandsTokens(std::vector<std::vector<token> > commandsTokens, std::vector<std::string> commands)
{
	number		number;
	bool		exit = false;
	bool		error = true;
	int			type;
	std::string	nbStr;
	bool		badInstruction = false;

	for (unsigned int i = 0; i < commandsTokens.size() && !exit; ++i) {
		int typeInstruction = _checkInstruction(commandsTokens[i][0]);
		if (typeInstruction != 2)
		{
			if (typeInstruction != -1)
				if (!commandsTokens[i][0].str.compare("exit"))
					exit = true;
				if ((error = _checkNumberOfTokens(commandsTokens[i], typeInstruction)) != false)
					nbStr = _checkOrderOfTokens(commandsTokens[i], typeInstruction, &type);
			if (typeInstruction == -1 || error == false || !nbStr.compare(""))
			{
				if (badInstruction == true)
					std::cout << std::endl;
				if (vm::options.c)
					std::cerr << "\033[5;31mbad instruction: line " << i + 1 << " : " << commands[i] << "\033[0m";
				else
					std::cerr << "bad instruction: line " << i + 1 << " : " << commands[i];
				badInstruction = true;
			}
			else {
				commands[i] = commandsTokens[i][0].str;
				if (typeInstruction == 1) {
					number.type = _getType(commandsTokens[i][1].str);
					number.value = nbStr;
					this->_numbers.push_back(number);
				}
			}
		}
		else
			commands[i] = "";
	}
	if (!exit)
	{
		if (badInstruction == true)
			std::cout << std::endl;
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mThe program doesn’t have an exit instruction\033[0m");
		else
			throw LogicErrorException("The program doesn’t have an exit instruction");
	}
	else if (badInstruction) {
		throw LogicErrorException("");
	}
	this->_execInstructions(commands);
}

void	parser::_execInstructions(std::vector<std::string> commands)
{
	unsigned int j = 0;

	for (unsigned int i = 0; i < commands.size(); ++i) {
		if (commands[i].compare("")) {
			if (!commands[i].compare("push") || !commands[i].compare("assert"))
				_number = _numbers[j++];
			(this->*_instructions.at(commands[i]))();
		}
	}
}

void	parser::_push(void)
{
	this->_stack.push_front(_factory->createOperand(_number.type, _number.value));
	if (vm::options.v)
	{
		if (vm::options.c)
			std::cout << GREEN << "push: " << END << _number.value << std::endl;
		else
			std::cout << "push: " << _number.value << std::endl;
	}
}

void	parser::_pop(void)
{
	if (this->_stack.size() < 1)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mpop: Empty stack\033[0m");
		else
			throw LogicErrorException("pop: Empty stack");
	}
	else
	{
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "pop: " << END << static_cast<const IOperand*>(*(_stack.begin()))->toString() << std::endl;
			else
				std::cout << "pop: " << static_cast<const IOperand*>(*(_stack.begin()))->toString() << std::endl;
		}
		this->_stack.pop_front();
	}
}

void	parser::_assert(void)
{
	if (this->_stack.size() < 1)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31massert: Empty stack\033[0m");
		else
			throw LogicErrorException("assert: Empty stack");
	}

	const IOperand* v1 = *(this->_stack.begin());

	if (v1->getType() != _number.type)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31massert: Different type\033[0m");
		else
	        throw LogicErrorException("assert: Different type");
	}
	if (_number.type > Int32)
	{
		if (std::stod(v1->toString()) != std::stod(_number.value))
		{
			if (vm::options.c)
				throw LogicErrorException("\033[5;31massert: Different value\033[0m");
			else
	        	throw LogicErrorException("assert: Different value");
    	}
    }
    else
    	if (std::stoi(v1->toString()) != std::stoi(_number.value))
        {
        	if (vm::options.c)
				throw LogicErrorException("\033[5;31massert: Different value\033[0m");
			else
	        	throw LogicErrorException("assert: Different value");
        }
    if (vm::options.v)
	{
		if (vm::options.c)
			std::cout << GREEN << "assert: " << END << v1->toString() << " and " << _number.value << std::endl;
		else
			std::cout << "assert: " << v1->toString() << " and " << _number.value << std::endl;
	}
}

void	parser::_add(void)
{
	if (this->_stack.size() < 2)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31madd: Stack has less than two values\033[0m");
		else
			throw LogicErrorException("add: Stack has less than two values");
	}
	else
	{
		const IOperand* v1 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* v2 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* newValue = *v2 + *v1;
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "add: " << END << v2->toString() << YELLOW << " + " << END << v1->toString() << YELLOW << " = " << END << newValue->toString() << std::endl;
			else
				std::cout << "add: " << v2->toString() << " + " << v1->toString() << " = " << newValue->toString() << std::endl;
		}
		delete v1;
		delete v2;
		this->_stack.push_front(newValue);
	}
}

void	parser::_sub(void)
{
	if (this->_stack.size() < 2)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31msub: Stack has less than two values\033[0m");
		else
			throw LogicErrorException("sub: Stack has less than two values");
	}
	else
	{
		const IOperand* v1 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* v2 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* newValue = *v2 - *v1;
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "sub: " << END << v2->toString() << YELLOW << " - " << END << v1->toString() << YELLOW << " = " << END << newValue->toString() << std::endl;
			else
				std::cout << "sub: " << v2->toString() << " - " << v1->toString() << " = " << newValue->toString() << std::endl;
		}
		delete v1;
		delete v2;
		this->_stack.push_front(newValue);
	}
}

void	parser::_mul(void)
{
	if (this->_stack.size() < 2)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mmul: Stack has less than two values\033[0m");
		else
			throw LogicErrorException("mul: Stack has less than two values");
	}
	else
	{
		const IOperand* v1 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* v2 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* newValue = *v2 * *v1;
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "mul: " << END << v2->toString() << YELLOW << " * " << END << v1->toString() << YELLOW << " = " << END << newValue->toString() << std::endl;
			else
				std::cout << "mul: " << v2->toString() << " * " << v1->toString() << " = " << newValue->toString() << std::endl;
		}
		delete v1;
		delete v2;
		this->_stack.push_front(newValue);
	}
}

void	parser::_div(void)
{
	if (this->_stack.size() < 2)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mdiv: Stack has less than two values\033[0m");
		else
			throw LogicErrorException("div: Stack has less than two values");
	}
	else
	{
		const IOperand* v1 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* v2 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* newValue = *v2 / *v1;
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "div: " << END << v2->toString() << YELLOW << " / " << END << v1->toString() << YELLOW << " = " << END << newValue->toString() << std::endl;
			else
				std::cout << "div: " << v2->toString() << " / " << v1->toString() << " = " << newValue->toString() << std::endl;
		}
		delete v1;
		delete v2;
		this->_stack.push_front(newValue);
	}
}

void	parser::_mod(void)
{
	if (this->_stack.size() < 2)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mmod: Stack has less than two values\033[0m");
		else
			throw LogicErrorException("mod: Stack has less than two values");
	}
	else
	{
		const IOperand* v1 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* v2 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* newValue = *v2 % *v1;
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "mod: " << END << v2->toString() << YELLOW << " % " << END << v1->toString() << YELLOW << " = " << END << newValue->toString() << std::endl;
			else
				std::cout << "mod: " << v2->toString() << " % " << v1->toString() << " = " << newValue->toString() << std::endl;
		}
		delete v1;
		delete v2;
		this->_stack.push_front(newValue);
	}
}

void	parser::_pow(void)
{
	const IOperand* 	newValue;
	std::string			number;
	std::stringstream	strstream;

	if (this->_stack.size() < 2)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mpow: Stack has less than two values\033[0m");
		else
			throw LogicErrorException("pow: Stack has less than two values");
	}
	else
	{
		const IOperand* v1 = *(_stack.begin());
		this->_stack.pop_front();
		const IOperand* v2 = *(_stack.begin());
		this->_stack.pop_front();
		eOperandType type = v2->getType();
		if (v1->getType() > Int32 || v1->getNb() < 0)
			type = Double;
		
		strstream << pow(v2->getNb(), v1->getNb());
		strstream >> number;
		if (type > Int32)
			newValue = this->_factory->createOperand(type, number);
		else
			newValue = this->_factory->createOperand(type, number);
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "pow: " << END << v2->toString() << YELLOW << "^" << END << v1->toString() << YELLOW << " = " << END << newValue->toString() << std::endl;
			else
				std::cout << "pow: " << v2->toString() << "^" << v1->toString() << " = " << newValue->toString() << std::endl;
		}
		delete v1;
		delete v2;
		this->_stack.push_front(newValue);
	}
}

void	parser::_max(void)
{
	if (this->_stack.size() < 1)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mmax: Stack has less than one value\033[0m");
		else
			throw LogicErrorException("max: Stack has less than one value");
	}
	else
	{
		const IOperand* max = *(_stack.begin());
		this->_stack.pop_front();
		for (std::list<const IOperand*>::const_iterator it=_stack.begin(); it != _stack.end(); ++it)
		{
			if (max->getNb() < (*it)->getNb())
				max = *it;
			this->_stack.pop_front();
		}
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "max: " << END << max->toString() << std::endl;
			else
				std::cout << "max: " << max->toString() << std::endl;
		}
		this->_stack.push_front(max);
	}
}

void	parser::_min(void)
{
	if (this->_stack.size() < 1)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mmin: Stack has less than one value\033[0m");
		else
			throw LogicErrorException("min: Stack has less than one value");
	}
	else
	{
		const IOperand* min = *(_stack.begin());
		this->_stack.pop_front();
		for (std::list<const IOperand*>::const_iterator it=_stack.begin(); it != _stack.end(); ++it)
		{
			if (min->getNb() > (*it)->getNb())
				min = *it;
			this->_stack.pop_front();
		}
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "min: " << END << min->toString() << std::endl;
			else
				std::cout << "min: " << min->toString() << std::endl;
		}
		this->_stack.push_front(min);
	}
}

void	parser::_avg(void)
{
	std::string			number;
	std::stringstream	strstream;

	if (this->_stack.size() < 1)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mavg: Stack has less than one value\033[0m");
		else
			throw LogicErrorException("avg: Stack has less than one value");
	}
	else
	{
		const IOperand* avg;
		const IOperand*		total = this->_factory->createOperand(Int8, "0");

		for (std::list<const IOperand*>::const_iterator it=_stack.begin(); it != _stack.end(); ++it)
		{
			const IOperand* tmp = **it + *total;
			delete total;
			total = tmp;
		}

		strstream << (total->getNb() / _stack.size());
		strstream >> number;
		this->_stack.clear();
		if (total->getType() > Int32)
			avg = this->_factory->createOperand(total->getType(), number);
		else
			avg = this->_factory->createOperand(total->getType(), number);
		if (vm::options.v)
		{
			if (vm::options.c)
				std::cout << GREEN << "avg: " << END << avg->toString() << std::endl;
			else
				std::cout << "avg: " << avg->toString() << std::endl;
		}
		delete total;
		this->_stack.push_front(avg);
	}
}

void	parser::_print(void)
{
	if (_stack.size() == 0)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mprint: Empty stack\033[0m");
		else
			throw LogicErrorException("print: Empty stack");
	}
	const IOperand* v1 = *(_stack.begin());
	if (v1->getType() != Int8)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mprint: Not on 8-bit integer\033[0m");
		else
			throw LogicErrorException("print: Not on 8-bit integer");
	}
	if (vm::options.v)
	{
		if (vm::options.c)
			std::cout << GREEN << "print: " << END << std::endl;
		else
			std::cout << "print: ";
	}
	std::cout << static_cast<char>(std::stoi(v1->toString()));
	if (vm::options.v)
		std::cout << std::endl;
}

void	parser::_dump(void)
{
	std::list<const IOperand*>::iterator it;

	if (_stack.size() == 0)
	{
		if (vm::options.c)
			throw LogicErrorException("\033[5;31mdump: Empty stack\033[0m");
		else
			throw LogicErrorException("dump: Empty stack");
	}
	if (vm::options.v)
	{
		if (vm::options.c)
			std::cout << GREEN << "dump:" << END << std::endl;
		else
			std::cout << "dump:" << std::endl;
	}
	for (it = _stack.begin(); it != _stack.end(); ++it)
		std::cout << (*it)->toString() << std::endl;
}

void	parser::_exit(void)
{
	if (vm::options.v)
	{
		if (vm::options.c)
			std::cout << GREEN << "exit" << END << std::endl;
		else
			std::cout << "exit" << std::endl;
	}
	std::exit(0);
}

parser &	parser::operator=(parser const &rhs)
{
	static_cast<void>(rhs);
	return (*this);
}
