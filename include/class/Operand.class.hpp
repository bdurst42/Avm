#ifndef OPERAND_CLASS_HPP
#define OPERAND_CLASS_HPP

#include "class/IOperand.class.hpp"
#include "class/AvmException.class.hpp"
#include "class/OperandFactory.class.hpp"
#include "class/vm.class.hpp"
#include <iomanip>
#include <sstream>
#include <limits>

template<typename T>
class Operand: public IOperand
{
		  public:

					 Operand(void);
					 Operand(Operand const &src);
					 ~Operand(void)
					 {
					 	;
					 }
					 
					 Operand(std::string value, eOperandType type): _str(value), _type(type)
					 {
						std::stringstream ss(value);

					 	ss >> this->_nb;
						this->_checkOverUnderFlow();
						this->_setPrecision(value);
						this->_factory = new OperandFactory;
					 }

					 int	getPrecision( void ) const
					 {
					 	return _precision;
					 }

					 eOperandType	getType( void ) const
					 {
					 	return _type;
					 }

					 long double	getNb(void) const
					 {
					 	return _nb;
					 }

					 IOperand const * operator+( IOperand const & rhs ) const
					 {
					 	eOperandType type = (this->_type >= rhs.getType()) ? this->_type : rhs.getType();
					 	std::stringstream ss;

					 	if (type > Int32)
					 	{
					 		std::stringstream tmp;
					 		long double newNb = std::stod(this->_str) + std::stod(rhs.toString());
					 		tmp << newNb;
					 		
					 		std::size_t founde = tmp.str().find("e");
					 		std::size_t foundDot= tmp.str().find(".");
					 		if (type > Int32 && founde == std::string::npos)
			 					ss << std::setprecision(this->_managePrecision(foundDot, tmp.str().length(), newNb, rhs)) << newNb;
					 	}
					 	else
					 	{
					 		long newNb = std::stoi(this->_str) + std::stoi(rhs.toString());
					 		ss << newNb;
					 	}
					 	return this->_factory->createOperand(type, ss.str());
					 }

					 IOperand const * operator-( IOperand const & rhs ) const
					 {
					 	eOperandType type = (this->_type >= rhs.getType()) ? this->_type : rhs.getType();
					 	std::stringstream ss;

					 	if (type > Int32)
					 	{
					 		std::stringstream tmp;
					 		long double newNb = std::stod(this->_str) - std::stod(rhs.toString());
					 		tmp << newNb;
					 		
					 		std::size_t founde = tmp.str().find("e");
					 		std::size_t foundDot= tmp.str().find(".");
					 		if (type > Int32 && founde == std::string::npos)
			 					ss << std::setprecision(this->_managePrecision(foundDot, tmp.str().length(), newNb, rhs)) << newNb;
					 	}
					 	else
					 	{
					 		long newNb = std::stoi(this->_str) - std::stoi(rhs.toString());
					 		ss << newNb;
					 	}
					 	return this->_factory->createOperand(type, ss.str());
					 }

					 IOperand const * operator*( IOperand const & rhs ) const
					 {
					 	eOperandType type = (this->_type >= rhs.getType()) ? this->_type : rhs.getType();
					 	std::stringstream ss;

					 	if (type > Int32)
					 	{
					 		std::stringstream tmp;
					 		long double newNb = std::stod(this->_str) * std::stod(rhs.toString());
				 			tmp << newNb;
					 		
					 		std::size_t founde = tmp.str().find("e");
					 		std::size_t foundDot= tmp.str().find(".");
					 		if (type > Int32 && founde == std::string::npos)
			 					ss << std::setprecision(this->_managePrecision(foundDot, tmp.str().length(), newNb, rhs)) << newNb;
					 	}
					 	else
					 	{
					 		long newNb = std::stoi(this->_str) * std::stoi(rhs.toString());
					 		ss << newNb;
					 	}
					 	return this->_factory->createOperand(type, ss.str());
					 }

					 IOperand const * operator/( IOperand const & rhs ) const
					 {
					 	eOperandType type = (this->_type >= rhs.getType()) ? this->_type : rhs.getType();
					 	std::stringstream ss;

					 	if (type > Int32)
					 	{
					 		std::stringstream tmp;
						 	if (std::stod(rhs.toString()) == 0)
						 	{
						 		if (vm::options.c)
									throw LogicErrorException("\033[5;31mdiv: Divisor is equal to 0\033[0m");
						 		else
									throw LogicErrorException("div: Divisor is equal to 0");
					 		}

					 		long double newNb = std::stod(this->_str) / std::stod(rhs.toString());
				 			tmp << newNb;

					 		std::size_t founde = tmp.str().find("e");
					 		std::size_t foundDot= tmp.str().find(".");
					 		if (type > Int32 && founde == std::string::npos)
			 					ss << std::setprecision(this->_managePrecision(foundDot, tmp.str().length(), newNb, rhs)) << newNb;
					 	}
					 	else
					 	{
					 		if (std::stol(rhs.toString()) == 0)
							{
						 		if (vm::options.c)
									throw LogicErrorException("\033[5;31mdiv: Divisor is equal to 0\033[0m");
						 		else
									throw LogicErrorException("div: Divisor is equal to 0");
					 		}
					 		
					 		long newNb = std::stoi(this->_str) / std::stoi(rhs.toString());
					 		ss << newNb;
					 	}
					 	return this->_factory->createOperand(type, ss.str());
					 }

					 IOperand const * operator%( IOperand const & rhs ) const
					 {
					 	eOperandType type = (this->_type >= rhs.getType()) ? this->_type : rhs.getType();
					 	
					 	if (type > Int32)
					 	{
					 		if (vm::options.c)
								throw LogicErrorException("\033[5;31mmod: Modulo of floats or doubles are impossible\033[0m");
					 		else
						 		throw LogicErrorException("mod: Modulo of floats or doubles are impossible");
					 		return NULL;
					 	}
					 	else
					 	{
					 		if (std::stol(rhs.toString()) == 0)
							{
						 		if (vm::options.c)
									throw LogicErrorException("\033[5;31mmod: Divisor is equal to 0\033[0m");
						 		else
									throw LogicErrorException("mod: Divisor is equal to 0");
					 		}

					 		long newNb = std::stoi(this->_str) % std::stoi(rhs.toString());
					 		std::stringstream ss;
					 		
					 		ss << newNb;
					 		return this->_factory->createOperand(type, ss.str());
					 	}
					 }

					 std::string const & toString( void ) const
					 {
					 	return _str;
					 }

					 Operand &	operator=(Operand const &rhs);

			private:

					 std::string	_str;
					 eOperandType	_type;
					 long double		_nb;
					 int				_precision;
					 OperandFactory *	_factory;

					 void	_checkOverUnderFlow(void) const
					 {
						if (this->_nb < std::numeric_limits<T>::max() * -1 - 1)
						{
							if (vm::options.c)
								throw UnderflowException("\033[5;31mUnderflow\033[0m");
						 	else
								throw UnderflowException("Underflow");
						}
						else if (this->_nb > std::numeric_limits<T>::max())
						{
							if (vm::options.c)
								throw OverflowException("\033[5;31mOverflow\033[0m");
						 	else
								throw OverflowException("Overflow");
						}
					 }

					 void	_setPrecision(std::string str)
					 {
					 	std::size_t found = str.find(".");

					 	if (found != std::string::npos)
					 		this->_precision = str.size() - (found + 1);
					 	else
							this->_precision = 0;
					 }

					 int	_managePrecision(std::size_t foundDot, int precision, long double newNb, IOperand const & rhs) const
					 {
					 	if (foundDot != std::string::npos)
					 		--precision;
					 	if (newNb < 0)
					 		--precision;
					 	--foundDot;
					 	if (static_cast<unsigned long>(this->_precision) > precision - foundDot)
							precision = foundDot + this->_precision;
			 			if (static_cast<unsigned long>(rhs.getPrecision()) > precision - foundDot && rhs.getPrecision() > this->_precision)
							precision = foundDot + rhs.getPrecision(); 

			 			return precision;
					 }
};

#endif
