#---------------------------------------------------#
CC 			= c++

CFLAGS 		= #-Wall -Wextra -Werror -std=c++98

NAME 		= ircserv
#---------------------------------------------------#
SRCS		= \
src/main.cpp\


OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

HEADERS		= \
headers/global.hpp\
headers/Channel.hpp\
headers/Client.hpp\
headers/Command.hpp\
headers/CommandHandler.hpp\
headers/Server.hpp

#---------------------------------------------------#
all:
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I headers/ -o $(NAME)

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