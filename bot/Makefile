#---------------------------------------------------#
CC 			= c++

CFLAGS 		= -Wall -Wextra -Werror -std=c++98

NAME 		= rocketBot
#---------------------------------------------------#
SRCS		= \
main.cpp\
IRCBot.cpp\

OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

HEADERS		= \
IRCBot.hpp\

#---------------------------------------------------#
all:
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : %.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I headers/ -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re:	fclean
	$(MAKE) all

.PHONY: all clean fclean re
#---------------------------------------------------#