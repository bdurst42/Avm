#include "class/AvmException.class.hpp"

InvalidArgException::InvalidArgException(void): std::invalid_argument(0), _msg(0)
{
	return;
}

InvalidArgException::~InvalidArgException(void) throw()
{
	return;
}

InvalidArgException::InvalidArgException(const std::string &msg): std::invalid_argument(msg), _msg(msg)
{
	return;
}

InvalidArgException::InvalidArgException(const InvalidArgException &src): std::invalid_argument(src._msg), _msg(src._msg)
{
	*this = src;

	return;
}

const char* InvalidArgException::what() const throw ()
{
	return (_msg.c_str());
}

InvalidArgException &	InvalidArgException::operator=(const InvalidArgException &rhs) throw()
{
	static_cast<void>(rhs);
	return (*this);
}

OverflowException::OverflowException(void): std::overflow_error(0), _msg(0)
{
	return;
}

OverflowException::~OverflowException(void) throw()
{
	return;
}

OverflowException::OverflowException(const std::string &msg): std::overflow_error(msg), _msg(msg)
{
	return;
}

OverflowException::OverflowException(const OverflowException &src): std::overflow_error(src._msg), _msg(src._msg)
{
	*this = src;

	return;
}

const char* OverflowException::what() const throw ()
{
	return (_msg.c_str());
}

OverflowException &	OverflowException::operator=(const OverflowException &rhs) throw()
{
	static_cast<void>(rhs);
	return (*this);
}

UnderflowException::UnderflowException(void): std::underflow_error(0), _msg(0)
{
	return;
}

UnderflowException::~UnderflowException(void) throw()
{
	return;
}

UnderflowException::UnderflowException(const std::string &msg): std::underflow_error(msg), _msg(msg)
{
	return;
}

UnderflowException::UnderflowException(const UnderflowException &src): std::underflow_error(src._msg), _msg(src._msg)
{
	*this = src;

	return;
}

const char* UnderflowException::what() const throw ()
{
	return (_msg.c_str());
}

UnderflowException &	UnderflowException::operator=(const UnderflowException &rhs) throw()
{
	static_cast<void>(rhs);
	return (*this);
}

LogicErrorException::LogicErrorException(void): std::logic_error(0), _msg(0)
{
	return;
}

LogicErrorException::~LogicErrorException(void) throw()
{
	return;
}

LogicErrorException::LogicErrorException(const std::string &msg): std::logic_error(msg), _msg(msg)
{
	return;
}

LogicErrorException::LogicErrorException(const LogicErrorException &src): std::logic_error(src._msg), _msg(src._msg)
{
	*this = src;

	return;
}

const char* LogicErrorException::what() const throw ()
{
	return (_msg.c_str());
}

LogicErrorException &	LogicErrorException::operator=(const LogicErrorException &rhs) throw()
{
	static_cast<void>(rhs);
	return (*this);
}