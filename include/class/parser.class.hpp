#ifndef PARSER_CLASS_HPP
# define PARSER_CLASS_HPP

#include <regex>
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <iterator>
#include "class/IOperand.class.hpp"
#include "class/AvmException.class.hpp"
#include "class/OperandFactory.class.hpp"
#include "class/vm.class.hpp"
#include "struct.hpp"

#define END "\033[0m"
#define RED "\033[5;31m"
#define ORANGE "\033[1;31m"
#define GREEN "\033[5;32m"
#define YELLOW "\033[5;33m"
#define BLUE "\033[5;34m"
#define GREY "\033[1;34m"
#define PURPLE "\033[5;35m"
#define PINK "\033[1;35m"
#define TURQUOISE "\033[5;36m"
#define WHITE "\033[1;37m"

struct number
{
	eOperandType	type;
	std::string		value;
};

class parser
{

	public:

						parser(void);
						parser(parser const &src);
						~parser(void);
		void			manageCommandsTokens(std::vector<std::vector<token> >, std::vector<std::string>);
		
		parser &		operator=(parser const &rhs);

	private:

		std::list<const IOperand*>						_stack;
		std::vector<number>								_numbers;
		number											_number;
		std::map<std::string, void (parser::*)(void)>	_instructions;
		std::shared_ptr<OperandFactory>					_factory;

		void			_push(void);
		void			_pop(void);
		void			_assert(void);
		void			_add(void);
		void			_sub(void);
		void			_mul(void);
		void			_div(void);
		void			_mod(void);
		void			_pow(void);
		void			_max(void);
		void			_min(void);
		void			_avg(void);
		void			_print(void);
		void			_dump(void);
		void			_exit(void);
		void			_execInstructions(std::vector<std::string> commands);
		eOperandType	_getType(std::string type);
		char			_checkType(token token);
		char			_checkInstruction(token token);
		bool			_checkNumberOfTokens(std::vector<token> tokens, char typeInstruction);
		std::string		_checkOrderOfTokens(std::vector<token> tokens, char typeInstruction, int *type);
};

#endif
