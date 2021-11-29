//
// Created by itonyluke@gmail.com on 25.11.21
// contributions by fmalphit https://t.me/acalabash
//

#include "countdown_timer.hpp"

//handle signals
static void signalHandler(int signum)
{
	std::cout << "\b\b\n" << DEFAULT << std::flush;
	std::cout << GREY << "Interrupt signal (" << signum << ") received." << DEFAULT << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;

	// cleanup and close up stuff here
	// terminate program

	exit (signum);
}

//initialize variables
static void initialize_variables(t_s *s)
{
	s->hour = 0;
	s->minutes = 0;
	s->seconds = 0;
}

//output the prompt
static void output_prompt(void)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::cout << GREY << START_END << DEFAULT << std::endl;
	std::cout << "it is a countdown timer" << std::endl;
	std::cout << "it is ";
	std::cout << ltm->tm_hour << ":";
	std::cout << ltm->tm_min << ":";
	std::cout << ltm->tm_sec;
	std::cout << " now" << std::endl;
	std::cout << "when is the deadline?" << std::endl;
	std::cout << "enter the hour: __\b\b" << BOLD;
}

//receive the input and handle the errors
static void receive_input_and_handle_errors(t_s *s)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::cin >> s->hour;
	if (s->hour == 0 || s->hour >= 24 || s->hour < ltm->tm_hour)
	{
		std::cout << RED << "the input is wrong" << std::endl;
		std::cout << "deadline will come anyway" << std::endl;
		std::cout << "you just waisted your life time" << DEFAULT << std::endl;
		std::cout << GREY << START_END << DEFAULT << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << DEFAULT << "enter the minutes: __\b\b" << BOLD;
	std::cin >> s->minutes;
	if (s->hour == ltm->tm_hour && s->minutes <= ltm->tm_min)
	{
		std::cout << RED << "the input is wrong" << std::endl;
		std::cout << "deadline will come anyway" << std::endl;
		std::cout << "you just waisted your life time" << DEFAULT << std::endl;
		std::cout << GREY << START_END << DEFAULT << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << DEFAULT;
}

void	while_for_outputing_countdown_timer_and_current_time_on_the_same_line(t_s *s)
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

void check_hour_and_minutes(t_s *s, std::string &h, std::string &m)
{
	s->hour = std::stoi(h);
	check_hour_and_output(s);
	s->minutes = std::stoi(m);
	check_minutes_and_output(s);
}

int main(int argc, char **argv)
{
	t_s s;

	initialize_variables(&s);
	system("clear");
	signal(SIGINT, signalHandler);

	if (argc == 1)
	{
		(void) argv;

		output_prompt();
		receive_input_and_handle_errors(&s);

		//output the time of the deadline
		std::cout << GREY << "> " << s.hour << ":" << add_zero(s.minutes) << s.minutes << ":00" << DEFAULT << std::endl;

		//output the countdown timer and the current time on the same line
		while_for_outputing_countdown_timer_and_current_time_on_the_same_line(&s);

//		output current time after deadline occurred;
		output_current_time_after_deadline_occurred();

		std::cout << GREY << START_END << DEFAULT << std::endl;
	}
	else if (argc == 2)
	{
		std::string argument = argv[1];

		std::cout << GREY << START_END << DEFAULT << std::endl;
		if (arg_length_is_fine(argv) && argument_is_fine(argv))
		{
			if (strlen(argv[1]) == 3 && std::isdigit(argv[1][0]) && argv[1][1] == ':' && std::isdigit(argv[1][2]))
			{
				std::string h = argument.substr(0, 1);
				std::string m = argument.substr(2, 1);
				check_hour_and_minutes(&s, h, m);
			}
			else if (strlen(argv[1]) == 5 && std::isdigit(argv[1][0]) && std::isdigit(argv[1][1]) && argv[1][2] == ':' && std::isdigit(argv[1][3]) && std::isdigit(argv[1][4]))
			{
				std::string h = argument.substr(0, 2);
				std::string m = argument.substr(3, 2);
				check_hour_and_minutes(&s, h, m);
			}
			else if (strlen(argv[1]) == 4 && std::isdigit(argv[1][0]) && std::isdigit(argv[1][1]) && argv[1][2] == ':' && std::isdigit(argv[1][3]))
			{
				std::string h = argument.substr(0, 2);
				std::string m = argument.substr(3, 1);
				check_hour_and_minutes(&s, h, m);
			}
			else if (strlen(argv[1]) == 4 && std::isdigit(argv[1][0]) && argv[1][1] == ':' && std::isdigit(argv[1][2]) && std::isdigit(argv[1][3]))
			{
				std::string h = argument.substr(0, 1);
				std::string m = argument.substr(2, 2);
				check_hour_and_minutes(&s, h, m);
			}
//			output the time of the deadline
			std::cout << GREY << "> " << s.hour << ":" << add_zero(s.minutes) << s.minutes << ":00" << DEFAULT << std::endl;

			//output the countdown timer and the current time on the same line
			while_for_outputing_countdown_timer_and_current_time_on_the_same_line(&s);

			//output current time after deadline occurred;
			output_current_time_after_deadline_occurred();

			std::cout << GREY << START_END << DEFAULT << std::endl;
		}
		else
		{
			std::cout << RED << "argument is wrong" << DEFAULT << std::endl;
			prompt_correct_usage();
		}
	}
	else
		prompt_correct_usage();

	return (0);
}
