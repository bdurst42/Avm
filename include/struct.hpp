#ifndef STRUCT_HPP
# define STRUCT_HPP

typedef struct	s_options
{
	bool		c;	
	bool		v;	
}				t_options;

enum tokenTypes
{
		  String,
		  leftBracket,
		  rightBracket,
		  Nb,
		  Dot,
		  Sign,
		  Comment,
		  Unknow
};

struct token
{
	tokenTypes		type;
	std::string		str;
};

#endif