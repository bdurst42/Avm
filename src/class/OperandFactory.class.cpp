#include "class/OperandFactory.class.hpp"
#include "class/Operand.class.hpp"

OperandFactory::OperandFactory(void)
{
	this->_tab[Int8] = &OperandFactory::createInt8;
	this->_tab[Int16] = &OperandFactory::createInt16;
	this->_tab[Int32] = &OperandFactory::createInt32;
	this->_tab[Float] = &OperandFactory::createFloat;
	this->_tab[Double] = &OperandFactory::createDouble;
}

OperandFactory::OperandFactory(OperandFactory const &src)
{
	*this = src;
}

OperandFactory::~OperandFactory(void)
{
	return ;
}

IOperand const *	OperandFactory::createOperand(eOperandType type, std::string const & value) const
{
	if (type >= 0 && type < 5)
	{
		return (this->*_tab[type])(value);
	}
	return NULL;
}

IOperand const *	OperandFactory::createInt8(std::string const & value) const
{
	return new Operand<char>(value, Int8);
}

IOperand const *	OperandFactory::createInt16(std::string const & value) const
{
	return new Operand<short int>(value, Int16);
}

IOperand const *	OperandFactory::createInt32(std::string const & value) const
{
	return new Operand<int>(value, Int32);
}

IOperand const *	OperandFactory::createFloat(std::string const & value) const
{
	return new Operand<float>(value, Float);
}

IOperand const *	OperandFactory::createDouble(std::string const & value) const
{
	return new Operand<double>(value, Double);
}

OperandFactory &	OperandFactory::operator=(OperandFactory const &rhs)
{
	static_cast<void>(rhs);
	return *this;
}
