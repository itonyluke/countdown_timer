#include <iostream>
#include <unistd.h>
#include <csignal>

#define BOLD "\033[97m"
#define DEFAULT "\033[0m"
#define START_END "************************************************************"
#define GREY "\033[2m"
#define RED "\033[31m"

//structure to hold the deadline time
typedef struct	s_s
{
	int hour;
	int minutes;
	int seconds;
}				t_s;

//handle signals
void signalHandler(int signum)
{
	std::cout << "\b\b\n" << DEFAULT << std::flush;
	std::cout << "Interrupt signal (" << signum << ") received." << std::endl;
	std::cout << GREY << START_END << DEFAULT << std::endl;

	// cleanup and close up stuff here
	// terminate program

	exit (signum);
}

//initialize variables
void initialize_variables(t_s *s)
{
	s->hour = 0;
	s->minutes = 0;
	s->seconds = 0;
}

//output the prompt
void output_prompt(void)
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
void receive_input_and_handle_errors(t_s *s)
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

//output hours of a countdown timer
void	output_hours(t_s *s, tm *ltm)
{
	if (s->hour == ltm->tm_hour)
		std::cout << "> 00" << ":";
	else if (s->minutes <= ltm->tm_min)
		std::cout << "> "<< s->hour - ltm->tm_hour - 1<< ":";
	else
		std::cout << "> "<< s->hour - ltm->tm_hour << ":";
}

//add zeros where necessary
const char *add_zero(int num)
{
	return (num < 10 ? "0" : "\0");
}

//output minutes of a countdown timer
void	output_minutes(t_s *s, tm *ltm)
{
	int num;

	if (s->minutes - ltm->tm_min == 1)
		std::cout << "00:";
	else if (s->hour == ltm->tm_hour)
	{
		num = s->minutes - ltm->tm_min - 1;
		std::cout << add_zero(num) << num << ":";
	}
	else if (((59 - ltm->tm_min) + s->minutes) > 60)
	{
		num = (59 - ltm->tm_min) - s->minutes;
		std::cout << add_zero(num) << num << ":";
	}
	else
	{
		num = (59 - ltm->tm_min) + s->minutes;
		std::cout << add_zero(num) << num << ":";
	}
}

//output seconds of a countdown timer
void	output_seconds(tm *ltm)
{
	int num;

	if (ltm->tm_sec == 0)
		std::cout << "00   ";
	else
	{
		num = 60 - ltm->tm_sec;
		std::cout << add_zero(num) << num << "   ";
	}
}

//output the current time
void	output_current_time(tm *ltm)
{
	std::cout << GREY << "> "<< ltm->tm_hour << ":";
	std::cout << ltm->tm_min << ":";
	std::cout << ltm->tm_sec << "                                       " << DEFAULT;
	std::cout << "\r" << std::flush;
	sleep(1);
}

//output the countdown time and the current time on the same line
void	output_countdown_timer(t_s *s, tm *ltm)
{
	output_hours(s, ltm);
	output_minutes(s, ltm);
	output_seconds(ltm);
	output_current_time(ltm);
}

//output the current time after the deadline is reached
void output_current_time_after_deadline_occurred(void)
{
	while (1)
	{
		time_t now = time(0);
		tm *ltm = localtime(&now);

		std::cout << "> "<< ltm->tm_hour << ":";
		std::cout << ltm->tm_min << ":";
		std::cout << ltm->tm_sec;
		std::cout << "\r" << std::flush;
		sleep(1);
	}
}

int main(void)
{
	t_s s;

	signal(SIGINT, signalHandler);
	initialize_variables(&s);
	output_prompt();
	receive_input_and_handle_errors(&s);

	//output the countdown timer and the current time on the same line
	while (1)
	{
		time_t now = time(0);
		tm *ltm = localtime(&now);

		//output the countdown timer
		if ((s.hour - ltm->tm_hour) == 0 && (s.minutes - ltm->tm_min) == 0 && (s.seconds - ltm->tm_sec) == 0)
		{
			std::cout << "\r" << std::flush << RED << "time is up                             " << "\a" << DEFAULT << std::endl << std::flush;
			break ;
		}
		else
			output_countdown_timer(&s, ltm);
	}
	output_current_time_after_deadline_occurred();

	std::cout << GREY << START_END << DEFAULT << std::endl;
}
