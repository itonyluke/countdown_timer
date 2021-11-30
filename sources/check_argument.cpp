//
// Created by itonyluke@gmail.com on 27.11.21
//

#include "../include/countdown_timer.hpp"

//check the length of the argument
bool	arg_length_is_fine(char **argv)
{
	size_t	arg_length;

	arg_length = strlen(argv[1]);
	if (arg_length >= 3 && arg_length <= 5)
		return (true);
	return (false);
}

//check whether argument is valid
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

//output prompt that input is wrong
static void	output_input_is_wrong(int i)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (i == 1)
		std::cout << RED << "deadline hour cannot be in the past" << DEFAULT << std::endl;
	else
		std::cout << RED << "deadline minute cannot be in the past" << DEFAULT << std::endl;
	std::cout << "current time: ";
	std::cout << add_zero(ltm->tm_hour) << ltm->tm_hour << ":";
	std::cout << add_zero(ltm->tm_min) << ltm->tm_min << ":";
	std::cout << add_zero(ltm->tm_sec) << ltm->tm_sec << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;
	exit(EXIT_FAILURE);
}

//check that input hour is correct
void check_hour_and_output_if_wrong(t_s *s)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (!(s->hour == 0 || s->hour >= 24 || s->hour < ltm->tm_hour))
		;
	else
		output_input_is_wrong(1);
}

//check that input minutes are correct
void check_minutes_and_output_if_wrong(t_s *s)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	if (!(s->hour == ltm->tm_hour && s->minutes <= ltm->tm_min))
		;
	else
		output_input_is_wrong(2);
}
