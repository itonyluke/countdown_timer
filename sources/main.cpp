//Copyright 2021 Anton Pavlyukevich, Andrey Fomichev.

//This file is part of a countdown_timer.
//
//Countdown_timer is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//
//Countdown_timer is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with Countdown_timer.  If not, see <https://www.gnu.org/licenses/>.

//
// Created by pavlyukevich.anton@gmail.com on 25.11.21
//

// built and tested on Darwin Kernel Version 18.7.0: Tue Jun 22 19:37:08 PDT 2021; root:xnu-4903.278.70~1/RELEASE_X86_64 x86_64

#include "../include/countdown_timer.hpp"

//handle signals
static void	signalHandler(int signum)
{
	std::cout << "\b\b\n" << DEFAULT << std::flush;
	std::cout << GREY << "Interrupt signal (" << signum << ") received." << DEFAULT << std::endl;
	output_divider_line();
//	std::cout << GREY << START_END << DEFAULT << std::endl;

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
	output_divider_line();
//	std::cout << GREY << START_END << DEFAULT << std::endl;
	std::cout << GREY << "Usage: " << DEFAULT << std::endl
			  << "./countdown" << std::endl
			  << GREY << "or" << DEFAULT << std::endl
			  << "./countdown <HH:MM>" << std::endl;
	output_divider_line();
//	std::cout << GREY << START_END << DEFAULT << std::endl;
}

//if (argc == 1)
static void	argc_equals_one(t_e &e, t_s *s, char **argv)
{
	(void) argv;
	time_t now = time(0);
	tm *ltm = localtime(&now);

	output_prompt();
	receive_input_and_handle_errors(s);
	init_shell(e);

	//output current time
	std::cout << GREY << "start\t";
	output_current_time(ltm);
	std::cout << std::endl;
	//output the time of the deadline
	std::cout << GREY << "end\t";
	std::cout << GREY << "> " << s->hour << ":" << add_zero(s->minutes) << s->minutes << ":00" << DEFAULT << std::endl;
	sleep(1);
	//output the countdown timer and the current time on the same line
	while_for_outputting_countdown_timer_and_current_time_on_the_same_line(s);
	//output current time after deadline occurred;
	output_current_time_after_deadline_occurred();
	output_divider_line();
//	std::cout << GREY << START_END << DEFAULT << std::endl;
}

//else if (argc == 2)
static void	argc_equals_two(t_e &e, t_s *s, char **argv)
{
	time_t now = time(0);
	tm *ltm = localtime(&now);

	output_divider_line();
//	std::cout << GREY << START_END << DEFAULT << std::endl;
	if (arg_length_is_fine(argv) && argument_is_fine(argv))
	{
		check_case(s, argv);
		init_shell(e);
		//output current time
		std::cout << GREY << "start\t";
		output_current_time(ltm);
		std::cout << std::endl;
		//output the time of the deadline
		std::cout << GREY << "end\t";
		std::cout << GREY << "> " << s->hour << ":" << add_zero(s->minutes) << s->minutes << ":00" << DEFAULT << std::endl;
		sleep(1);
		//output the countdown timer and the current time on the same line
		while_for_outputting_countdown_timer_and_current_time_on_the_same_line(s);
		//output current time after deadline occurred;
		output_current_time_after_deadline_occurred();
		//output ********************* in GREY
		output_divider_line();
		//std::cout << GREY << START_END << DEFAULT << std::endl;
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
	t_e e;

	initialize_variables(&s);
	system("clear");
	signal(SIGINT, signalHandler);
	if (argc == 1)
		argc_equals_one(e, &s, argv);
	else if (argc == 2)
		argc_equals_two(e, &s, argv);
	else
		prompt_correct_usage();
	return (0);
}

