//
// Created by itonyluke@gmail.com on 28.11.21
//

#ifndef COUNTDOWN_TIMER_HPP
# define COUNTDOWN_TIMER_HPP

# define BOLD "\033[97m"
# define DEFAULT "\033[0m"
# define START_END "************************************************************"
# define GREY "\033[2m"
# define RED "\033[31m"
# define GREEN "\033[32m"

# include <iostream>
# include <unistd.h>
# include <csignal>
# include <cstring>

//structure to hold the deadline time
typedef struct	s_s
{
	int			hour;
	int			minutes;
	int			seconds;
}				t_s;

void			output_hours(t_s *s, tm *ltm);
const char		*add_zero(int num);
void			output_minutes(t_s *s, tm *ltm);
void			output_seconds(tm *ltm);
void			output_current_time(tm *ltm);
void			output_countdown_timer(t_s *s, tm *ltm);
void			output_current_time_after_deadline_occurred(void);

bool			arg_length_is_fine(char **argv);
bool			argument_is_fine(char **argv);
void			check_hour_and_output_if_wrong(t_s *s);
void			check_minutes_and_output_if_wrong(t_s *s);

void			output_prompt(void);
void			receive_input_and_handle_errors(t_s *s);
void			while_for_outputting_countdown_timer_and_current_time_on_the_same_line(t_s *s);
void			check_hour_and_minutes(t_s *s, std::string &h, std::string &m);
void			check_case(t_s *s, char **argv);

#endif //COUNTDOWN_TIMER_HPP
