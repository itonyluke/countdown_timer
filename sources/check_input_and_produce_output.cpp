//
// Created by itonyluke@gmail.com on 30.11.21
//

#include "../include/countdown_timer.hpp"

//output the prompt
void	output_prompt(void)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::cout << GREY << START_END << DEFAULT << std::endl;
	std::cout << "it is a countdown timer" << std::endl;
	std::cout << "it is ";
	std::cout << add_zero(ltm->tm_hour) << ltm->tm_hour << ":";
	std::cout << add_zero(ltm->tm_min) << ltm->tm_min << ":";
	std::cout << add_zero(ltm->tm_sec) << ltm->tm_sec;
	std::cout << " now" << std::endl;
	std::cout << "when is the deadline?" << std::endl;
	std::cout << "enter the hour: __\b\b" << BOLD;
}

//receive input and handle the errors
void	receive_input_and_handle_errors(t_s *s)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::cin >> s->hour;
	if (s->hour == 0 || s->hour >= 24 || s->hour < ltm->tm_hour)
	{
		if (s->hour < ltm->tm_hour)
			std::cout << RED << "deadline hour cannot be in the past" << DEFAULT << std::endl;
		else
		{
			std::cout << RED << "the input is wrong" << std::endl;
			std::cout << "deadline will come anyway" << std::endl;
			std::cout << "you just waisted your life time" << DEFAULT << std::endl;
		}
		std::cout << GREY << START_END << DEFAULT << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << DEFAULT << "enter the minutes: __\b\b" << BOLD;
	std::cin >> s->minutes;
	if (s->minutes >= 60 || (s->hour == ltm->tm_hour && s->minutes <= ltm->tm_min))
	{
		if (s->minutes < ltm->tm_min)
			std::cout << RED << "deadline minute cannot be in the past" << DEFAULT << std::endl;
		else
		{
			std::cout << RED << "the input is wrong" << std::endl;
			std::cout << "deadline will come anyway" << std::endl;
			std::cout << "you just waisted your life time" << DEFAULT << std::endl;
		}
		std::cout << GREY << START_END << DEFAULT << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << DEFAULT;
}

//output the countdown timer and the current time on the same line
void	while_for_outputting_countdown_timer_and_current_time_on_the_same_line(t_s *s)
{
	while (1)
	{
		time_t now = time(0);
		tm *ltm = localtime(&now);

		//output the countdown timer
		if ((s->hour - ltm->tm_hour) == 0 && (s->minutes - ltm->tm_min) == 0 && (s->seconds - ltm->tm_sec) == 0)
		{
			std::cout << "\r" << std::flush << RED << "time is up                             " << "\a" << DEFAULT << std::endl << std::flush;
			break ;
		}
		else
			output_countdown_timer(s, ltm);
	}
}

//convert string to check whether hours and minutes are in an appropriate range
void	check_hour_and_minutes(t_s *s, std::string &h, std::string &m)
{
	s->hour = std::stoi(h);
	check_hour_and_output_if_wrong(s);
	s->minutes = std::stoi(m);
	check_minutes_and_output_if_wrong(s);
}

//the argument may come in four different cases (1:1, 11:1, 1:11, 11:11)
void	check_case(t_s *s, char **argv)
{
	std::string	argument = argv[1];

	if (strlen(argv[1]) == 3 && std::isdigit(argv[1][0]) && argv[1][1] == ':' && std::isdigit(argv[1][2]))
	{
		std::string h = argument.substr(0, 1);
		std::string m = argument.substr(2, 1);
		check_hour_and_minutes(s, h, m);
	}
	else if (strlen(argv[1]) == 5 && std::isdigit(argv[1][0]) && std::isdigit(argv[1][1]) && argv[1][2] == ':' && std::isdigit(argv[1][3]) && std::isdigit(argv[1][4]))
	{
		std::string h = argument.substr(0, 2);
		std::string m = argument.substr(3, 2);
		check_hour_and_minutes(s, h, m);
	}
	else if (strlen(argv[1]) == 4 && std::isdigit(argv[1][0]) && std::isdigit(argv[1][1]) && argv[1][2] == ':' && std::isdigit(argv[1][3]))
	{
		std::string h = argument.substr(0, 2);
		std::string m = argument.substr(3, 1);
		check_hour_and_minutes(s, h, m);
	}
	else if (strlen(argv[1]) == 4 && std::isdigit(argv[1][0]) && argv[1][1] == ':' && std::isdigit(argv[1][2]) && std::isdigit(argv[1][3]))
	{
		std::string h = argument.substr(0, 1);
		std::string m = argument.substr(2, 2);
		check_hour_and_minutes(s, h, m);
	}
}
