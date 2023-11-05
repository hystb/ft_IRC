#---------------------------------------------------#
CC 			= c++

CFLAGS 		= #-Wall -Wextra -Werror -std=c++98

NAME 		= ircserv
#---------------------------------------------------#
SRCS		= \
src/main.cpp\
src/network/Server.cpp\
src/commandhandler/CommandHandler.cpp\
src/commandhandler/Command.cpp\
src/commandhandler/commands/invite.cpp\
src/commandhandler/commands/join.cpp\
src/commandhandler/commands/topic.cpp\
src/commandhandler/commands/kick.cpp


OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

HEADERS		= \
src/network/Server.hpp\
src/commandhandler/CommandHandler.hpp\
src/commandhandler/Command.hpp
#---------------------------------------------------#
all:
	$(MAKE) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o : %.cpp $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re:	fclean
	$(MAKE) all

.PHONY: all clean fclean re
#---------------------------------------------------#