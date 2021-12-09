//
// Created by itonyluke@gmail.com on 28.11.21
// contributions by fmalphit https://t.me/acalabash
//
// built and tested on Darwin Kernel Version 18.7.0: Tue Jun 22 19:37:08 PDT 2021; root:xnu-4903.278.70~1/RELEASE_X86_64 x86_64

#include "../include/countdown_timer.hpp"

//output hours of a countdown timer
void	output_hours(t_s *s, tm *ltm)
{
	unsigned int	hours;

	if (s->hour == ltm->tm_hour)
		std::cout << GREY << "left\t>" << DEFAULT << " 00" << ":";
	else if (s->minutes <= ltm->tm_min)
	{
		hours = s->hour - ltm->tm_hour - 1;
		std::cout << GREY << "left\t> " << DEFAULT << add_zero(hours) << hours << ":";
	}
	else
	{
		hours = s->hour - ltm->tm_hour;
		std::cout << GREY << "left\t> " << DEFAULT << add_zero(hours) << hours << ":";
	}
}

//add zeros where necessary
const char	*add_zero(int num)
{
	return (num < 10 ? "0" : "\0");
}

//output minutes of a countdown timer
void	output_minutes(t_s *s, tm *ltm)
{
	int	minutes = 0;
	int	amount_of_minutes_left_in_this_hour = 59 - ltm->tm_min;

	if (s->minutes - ltm->tm_min == 1)
		std::cout << "00:";
	else if (s->hour == ltm->tm_hour)
	{
		minutes = s->minutes - ltm->tm_min - 1;
		std::cout << add_zero(minutes) << minutes << ":";
	}
	else if ((amount_of_minutes_left_in_this_hour + s->minutes) > 60)
	{
		minutes = amount_of_minutes_left_in_this_hour + s->minutes - 60;
		std::cout << add_zero(minutes) << minutes << ":";
	}
	else
	{
		minutes = amount_of_minutes_left_in_this_hour + s->minutes;
		std::cout << add_zero(minutes) << minutes << ":";
	}
}

//output seconds of a countdown timer
void	output_seconds(tm *ltm)
{
	int	amount_of_seconds_left_in_this_minute = 60 - ltm->tm_sec;

	if (ltm->tm_sec == 0)
		std::cout << "00   ";
	else
		std::cout << add_zero(amount_of_seconds_left_in_this_minute) << amount_of_seconds_left_in_this_minute << "   ";
}

//output the current time
void	output_current_time(tm *ltm)
{
	std::cout << GREY << "> "<< add_zero(ltm->tm_hour) << ltm->tm_hour << ":";
	std::cout << add_zero(ltm->tm_min) << ltm->tm_min << ":";
	std::cout << add_zero(ltm->tm_sec) << ltm->tm_sec << "                                       " << DEFAULT;
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
void	output_current_time_after_deadline_occurred(void)
{
	while (1)
	{
		time_t now = time(0);
		tm *ltm = localtime(&now);

		std::cout << GREY << "it is\t> " << DEFAULT << add_zero(ltm->tm_hour) << ltm->tm_hour << ":";
		std::cout << add_zero(ltm->tm_min) << ltm->tm_min << ":";
		std::cout << add_zero(ltm->tm_sec) << ltm->tm_sec;
		std::cout << GREY << " now";
		std::cout << "\r" << std::flush;
		sleep(1);
	}
}
