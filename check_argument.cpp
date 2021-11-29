//
// Created by Waves Anisha on 11/27/21.
//

#include "countdown_timer.hpp"

bool	arg_length_is_fine(char **argv)
{
	size_t arg_length;

	arg_length = strlen(argv[1]);
	if (arg_length >= 3 && arg_length <= 5)
		return (true);
	return (false);
}

bool	argument_is_fine(char **argv)
{
	if (std::isdigit(argv[1][0]) && argv[1][1] == ':' && std::isdigit(argv[1][2]) && argv[1][3] == '\0')
		return (true);
	else if (std::isdigit(argv[1][0]) && std::isdigit(argv[1][1]) && argv[1][2] == ':' && std::isdigit(argv[1][3]) && argv[1][4] == '\0')
		return (true);
	else if (std::isdigit(argv[1][0]) && argv[1][1] == ':' && std::isdigit(argv[1][2]) && std::isdigit(argv[1][3]) && argv[1][4] == '\0')
		return (true);
	else if (std::isdigit(argv[1][0]) && std::isdigit(argv[1][1]) && argv[1][2] == ':' && std::isdigit(argv[1][3]) && std::isdigit(argv[1][4]) && argv[1][5] == '\0')
		return (true);
	else
		return (false);
}

void prompt_correct_usage()
{
	std::cout << GREY << START_END << DEFAULT << std::endl;
	std::cout << GREY << "Usage: " << DEFAULT << std::endl
			  << "./a.out" << std::endl
			  << GREY << "or" << DEFAULT << std::endl
			  << "./a.out <HH:MM>" << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;
}

void output_input_is_wrong()
{
	std::cout << RED << "the input is wrong" << std::endl;
	std::cout << "deadline will come anyway" << std::endl;
	std::cout << "you just waisted your life time" << DEFAULT << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;
	exit(EXIT_FAILURE);
}

void check_hour_and_output(t_s *s)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (!(s->hour == 0 || s->hour >= 23 || s->hour < ltm->tm_hour))
		;
	else
		output_input_is_wrong();
}

void check_minutes_and_output(t_s *s)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (!(s->hour == ltm->tm_hour && s->minutes <= ltm->tm_min))
		;
	else
		output_input_is_wrong();
}