//
// Created by Waves Anisha on 12/9/21.
//

#include "../include/countdown_timer.hpp"

void output_divider_line()
{
	t_w w;
	int term_fd;

	term_fd = open("/dev/tty", O_RDONLY);
	if (term_fd == -1)
	{
		std::cout << "/dev/tty: fd == -1" << std::endl;
		exit(EXIT_FAILURE);
	}
	/* Get window size of terminal. */
	if (ioctl(term_fd, TIOCGWINSZ, &w) == -1)
		std::cout << "ioctl == -1" << std::endl;
//	std::cout << "\033[90mThis terminal window is\n" << w.ws_rows << " rows by " << w.ws_cols << " columns\033[0m\n";

	for (unsigned int i = 0; i < w.ws_cols; i++)
		std::cout << DARK_GREY << "*";
	std::cout << DEFAULT;
	return ;
}

