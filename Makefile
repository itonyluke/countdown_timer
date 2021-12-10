SOURCES						:=	$(wildcard sources/*.cpp)

OBJECTS						:=	$(SOURCES:.cpp=.o)

HEADERS						:=	./include/countdown_timer.hpp

COMPILER					:=	clang++

REMOVE_DIRECTORY_ENTRIES	:=	rm -f

COMPILE_FLAGS				:=	-Wall -Wextra -Werror -std=c++98 -pedantic-errors -I

PROGRAM_NAME				:=	countdown

JIC_A_OUT					:=	a.out

%.o: %.cpp
								$(COMPILER) $(COMPILE_FLAGS) $(HEADERS) -c $< -o ${<:.cpp=.o}

all:							$(PROGRAM_NAME)

$(PROGRAM_NAME):				$(OBJECTS)
								$(COMPILER) $(COMPILE_FLAGS) $(HEADERS) $(OBJECTS) -o $(PROGRAM_NAME)

$(OBJECTS):						$(HEADERS)

clean:
								$(REMOVE_DIRECTORY_ENTRIES) $(OBJECTS) $(JIC_A_OUT)

fclean:							clean
								$(REMOVE_DIRECTORY_ENTRIES) $(PROGRAM_NAME)

re:								fclean $(PROGRAM_NAME)

.PHONY:							all clean fclean re test