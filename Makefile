#---------------------------------------------------#
CC 			= c++

CFLAGS 		= -g3 -fsanitize=address #-Wall -Wextra -Werror -std=c++98

NAME 		= ircserv
#---------------------------------------------------#
SRCS		= \
src/main.cpp\
src/network/Server.cpp\
src/messages/Channel.cpp\
src/messages/Client.cpp\
src/commandhandler/CommandHandler.cpp\
src/commandhandler/Command.cpp\
src/commandhandler/commands/invite.cpp\
src/commandhandler/commands/join.cpp\
src/commandhandler/commands/log.cpp\
src/commandhandler/commands/kick.cpp\
src/commandhandler/commands/mode.cpp\
src/commandhandler/commands/nick.cpp\
src/commandhandler/commands/pass.cpp\
src/commandhandler/commands/quit.cpp\
src/commandhandler/commands/topic.cpp\
src/commandhandler/commands/user.cpp\

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