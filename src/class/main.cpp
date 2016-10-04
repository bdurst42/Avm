#include "class/vm.class.hpp"
#include <fstream>

int	getOptions(char const *argv[])
{
	int	i = 0;
	int j;
	
	while (argv[++i])
	{
		if (argv[i][0] != '-')
			break;
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == 'v')
				vm::options.v = true;
			else if (argv[i][j] == 'c')
				vm::options.c = true;
			else
				throw InvalidArgException("Bad options : -c -v is available");
		}
	}
	return i;
}

std::vector<std::string>	getCommands(int const argc, char const *argv[])
{
	std::vector<std::string>	commands;
	std::ifstream				file;
	std::string					line;
	int 						fileId;

	fileId = getOptions(argv);
	if (fileId == argc)
	{
		getline(std::cin, line);
		while (!strstr(line.c_str(), ";;") && std::cin.eof() != 1)
		{
			commands.push_back(line);
			getline(std::cin, line);
		}
		if (line.compare(";;"))
			commands.push_back(line);
	}
	else if (argc > 1)
	{
		if (fileId + 1 < argc)
		{
			if (vm::options.c)
				throw InvalidArgException("\033[5;31mToo many arguments\033[0m");
			else
				throw InvalidArgException("Too many arguments");
		}
		file.open(argv[fileId]);
		if (!file.is_open())
		{
			if (vm::options.c)
				throw LogicErrorException("\033[5;31mOpen failure !\033[0m");
			else
				throw LogicErrorException("Open failure !");
		}
		while (getline(file, line))
			commands.push_back(line);
		file.close();
	}
	return (commands);
}

int	main(int const argc, char const *argv[])
{
	vm			vm;

	try {
		vm.setCommands(getCommands(argc, argv));
		vm.getParser()->manageCommandsTokens(vm.getLexer()->checkCommands(vm.getCommands()), vm.getCommands());
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return (-1);
	}
	return (0);
}
