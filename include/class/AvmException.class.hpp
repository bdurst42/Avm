#ifndef AVM_EXCEPTION_HPP
# define AVM_EXCEPTION_HPP

#include <iostream>
#include <stdexcept>

class InvalidArgException : public std::invalid_argument
{
		  public:
					 InvalidArgException();
					 InvalidArgException(const std::string &msg);
					 InvalidArgException(const InvalidArgException &src);
					 InvalidArgException& operator=(const InvalidArgException &rhs) throw();
					 virtual const char* what() const throw ();

					 virtual ~InvalidArgException() throw ();
		  private:
					 std::string         _msg;
};

class OverflowException : public std::overflow_error
{
		  public:
					 OverflowException();
					 OverflowException(const std::string &msg);
					 OverflowException(const OverflowException &src);
					 OverflowException& operator=(const OverflowException &rhs) throw();
					 virtual const char* what() const throw ();

					 virtual ~OverflowException() throw ();
		  private:
					 std::string         _msg;
};

class UnderflowException : public std::underflow_error
{
		  public:
					 UnderflowException();
					 UnderflowException(const std::string &msg);
					 UnderflowException(const UnderflowException &src);
					 UnderflowException& operator=(const UnderflowException &rhs) throw();
					 virtual const char* what() const throw ();

					 virtual ~UnderflowException() throw ();
		  private:
					 std::string         _msg;
};

class LogicErrorException : public std::logic_error
{
		  public:
					 LogicErrorException();
					 LogicErrorException(const std::string &msg);
					 LogicErrorException(const LogicErrorException &src);
					 LogicErrorException& operator=(const LogicErrorException &rhs) throw();
					 virtual const char* what() const throw ();

					 virtual ~LogicErrorException() throw ();
		  private:
					 std::string         _msg;
};

#endif
