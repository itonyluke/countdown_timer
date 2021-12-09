//
// Created by itonyluke@gmail.com on 25.11.21
//

#include "../include/countdown_timer.hpp"

//handle signals
static void	signalHandler(int signum)
{
	std::cout << "\b\b\n" << DEFAULT << std::flush;
	std::cout << GREY << "Interrupt signal (" << signum << ") received." << DEFAULT << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;

	// cleanup and close up stuff here
	// terminate program

	exit (signum);
}

//initialize variables
static void	initialize_variables(t_s *s)
{
	s->hour = 0;
	s->minutes = 0;
	s->seconds = 0;
}

//prompt how to run
static void	prompt_correct_usage()
{
	std::cout << GREY << START_END << DEFAULT << std::endl;
	std::cout << GREY << "Usage: " << DEFAULT << std::endl
			  << "./countdown" << std::endl
			  << GREY << "or" << DEFAULT << std::endl
			  << "./countdown <HH:MM>" << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;
}

//if (argc == 1)
static void	argc_equals_one(t_s *s, char **argv)
{
	(void) argv;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	output_prompt();
	receive_input_and_handle_errors(s);

	//output current time
	std::cout << GREY << "start\t";
	output_current_time(ltm);
	std::cout << std::endl;
	//output the time of the deadline
	std::cout << GREY << "end\t";
	std::cout << GREY << "> " << s->hour << ":" << add_zero(s->minutes) << s->minutes << ":00" << DEFAULT << std::endl;
	//output the countdown timer and the current time on the same line
	while_for_outputting_countdown_timer_and_current_time_on_the_same_line(s);
	//output current time after deadline occurred;
	output_current_time_after_deadline_occurred();
	std::cout << GREY << START_END << DEFAULT << std::endl;
}

//else if (argc == 2)
static void	argc_equals_two(t_s *s, char **argv)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	std::cout << GREY << START_END << DEFAULT << std::endl;
	if (arg_length_is_fine(argv) && argument_is_fine(argv))
	{
		check_case(s, argv);
		//output current time
		std::cout << GREY << "start\t";
		output_current_time(ltm);
		std::cout << std::endl;
		//output the time of the deadline
		std::cout << GREY << "end\t";
		std::cout << GREY << "> " << s->hour << ":" << add_zero(s->minutes) << s->minutes << ":00" << DEFAULT << std::endl;
		//output the countdown timer and the current time on the same line
		while_for_outputting_countdown_timer_and_current_time_on_the_same_line(s);
		//output current time after deadline occurred;
		output_current_time_after_deadline_occurred();
		//output ********************* in GREY
		std::cout << GREY << START_END << DEFAULT << std::endl;
	}
	else
	{
		std::cout << RED << "argument is wrong" << DEFAULT << std::endl;
		prompt_correct_usage();
	}
}

int	main(int argc, char **argv)
{
	t_s	s;

	initialize_variables(&s);
	system("clear");
	signal(SIGINT, signalHandler);
	if (argc == 1)
		argc_equals_one(&s, argv);
	else if (argc == 2)
		argc_equals_two(&s, argv);
	else
		prompt_correct_usage();
	return (0);
}
