#include "../include/countdown_timer.hpp"

void	reset_initial_terminal_attributes(t_e &e)
{
	int	err_check;

	err_check = tcsetattr(e.term_fd, TCSANOW, &(e.saved_term_attributes));
	if (err_check == -1)
		std::cerr << "tcsetattr() returned -1\ninitial terminal attributes were not reset" << std::endl;
}

void	error_exit(t_e &e, int err_code)
{
	std::cout << "Error" << std::endl;
	if (err_code == -1)
		std::cerr << "/dev/tty: fd == -1\n" << std::endl;
	else if (err_code == -2)
		std::cerr << "Specify a terminal type "
					 "with `setenv TERM <yourtype>'." << std::endl;
	else if (err_code == -3)
		std::cerr << "Could not access the termcap data base." << std::endl;
	else if (err_code == -4)
		std::cerr << "Terminal type `%s' is not defined." << std::endl;
	else
		std::cerr << "Ooops!" << std::endl;
	e.term.c_lflag |= ECHO;
	e.term.c_lflag |= ICANON;
	reset_initial_terminal_attributes(e);
	exit(err_code);
}

void	init_failed(t_e &e, int err_code)
{
	std::cout << "Error" << std::endl;
	if (err_code == -1)
		std::cerr << "tcgetattr() returned -1\ninitial terminal "
					 "attributes were not saved." << std::endl;
	else if (err_code == -2)
		std::cerr << "tcgetattr() returned -1\ninitial terminal "
					 "attributes were not saved." << std::endl;
	else if (err_code == -3)
		std::cerr << "tcsetattr() returned -1\nterminal "
					 "attributes were not set" << std::endl;
	e.term.c_lflag |= ECHO;
	e.term.c_lflag |= ICANON;
	reset_initial_terminal_attributes(e);
	exit(-42);
}

void	get_and_save_initial_terminal_attributes(t_e &e)
{
	int	err_check;

	err_check = tcgetattr(e.term_fd, &(e.saved_term_attributes));
	if (err_check == -1)
		init_failed(e, -1);
}

void	get_and_save_terminal_attributes(t_e &e)
{
	int	err_check;

	err_check = tcgetattr(e.term_fd, &(e.term));
	if (err_check == -1)
		init_failed(e, -2);
}

void 	set_terminal_attributes(t_e &e)
{
	int	err_check;

	err_check = tcsetattr(e.term_fd, TCSANOW, &(e.term));
	if (err_check == -1)
		init_failed(e, -3);
}

int	init_term(t_e &e)
{
	get_and_save_initial_terminal_attributes(e);
	get_and_save_terminal_attributes(e);
	e.term.c_lflag &= ~ECHO;
	e.term.c_lflag &= ~ICANON;
	set_terminal_attributes(e);
	return (0);
}

void	init_shell(t_e &e)
{
	e.term_fd = open("/dev/tty", O_RDONLY);
	if (e.term_fd == -1)
		error_exit(e, -2);
	init_term(e);
}
