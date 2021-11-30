SRCS						=	sources/main.cpp \
								sources/check_input_and_produce_output.cpp \
								sources/check_argument.cpp \
								sources/output_timer_and_time.cpp

HEADERS						=	./include/

OBJS						=	$(SRCS:.cpp=.o)

COMPILER					=	clang++

REMOVE_DIRECTORY_ENTRIES	=	rm -f

COMPILE_FLAGS				=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors -I

PROGRAM_NAME				=	countdown

JIC_A_OUT					=	a.out

%.o: %.cpp
								$(COMPILER) $(COMPILE_FLAGS) $(HEADERS) -c $< -o ${<:.cpp=.o}

all:							$(PROGRAM_NAME)

$(PROGRAM_NAME):				$(OBJS)
								$(COMPILER) $(COMPILE_FLAGS) $(HEADERS) $(OBJS) -o $(PROGRAM_NAME)

clean:
								$(REMOVE_DIRECTORY_ENTRIES) $(OBJS) $(JIC_A_OUT)

fclean:							clean
								$(REMOVE_DIRECTORY_ENTRIES) $(PROGRAM_NAME)

re:								fclean $(PROGRAM_NAME)

.PHONY:							all clean fclean re test