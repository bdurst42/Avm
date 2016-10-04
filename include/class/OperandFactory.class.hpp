#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "class/IOperand.class.hpp"

class OperandFactory
{
	public:
		
		OperandFactory(void);
		OperandFactory(OperandFactory const &src);
		~OperandFactory(void);
		IOperand const * createOperand( eOperandType type, std::string const & value ) const;

		OperandFactory &	operator=(OperandFactory const &rhs);

	private:

		IOperand const *	createInt8( std::string const & value ) const;
		IOperand const *	createInt16( std::string const & value ) const;
		IOperand const *	createInt32( std::string const & value ) const;
		IOperand const *	createFloat( std::string const & value ) const;
		IOperand const *	createDouble( std::string const & value ) const;

		IOperand const * (OperandFactory::*_tab[5])(std::string const & value) const;
};


#endif
