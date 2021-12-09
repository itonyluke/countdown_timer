//
// Created by Waves Anisha on 12/9/21.
//

#include "../include/countdown_timer.hpp"

//outputs the divider line that consists of '*' symbol only for the entire terminal window width
void output_divider_line()
{
//	t_w w;
//	int term_fd;
//
//	term_fd = open("/dev/tty", O_RDONLY);
//	if (term_fd == -1)
//	{
//		std::cout << "/dev/tty: fd == -1" << std::endl;
//		exit(EXIT_FAILURE);
//	}
//	//Get terminal window size
//	if (ioctl(term_fd, TIOCGWINSZ, &w) == -1)
//		std::cout << "ioctl == -1" << std::endl;
//
//	//	if you would like to see actual values uncomment the lines below
//	//	std::cout << DARK_GREY << "This terminal window is\n" << w.ws_rows << " rows by " << w.ws_cols << " columns" << DEFAULT << std::endl;
//	//	std::cout << DARK_GREY << "(" << w.ws_xpixel << " by "<< w.ws_ypixel << " pixels)" << DEFAULT << std::endl;
//
//	for (unsigned int i = 0; i < w.ws_cols; i++)
//		std::cout << DARK_GREY << "*";
//	std::cout << DEFAULT;
//	return ;
}

