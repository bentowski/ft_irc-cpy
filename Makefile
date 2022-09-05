NAME = ircserv

SRCDIR = ./sources

#SRCS = $(shell find $(SRCDIR) -name *.cpp -or -name *.c -or -name *.s)
SRCS = 	main.cpp \
		sources/Server.cpp \
		sources/User.cpp \
		sources/Channel.cpp \
		sources/reply.cpp \
		sources/utils.cpp \
		sources/Commands/CAP.cpp \
		sources/Commands/NICK.cpp \
		sources/Commands/USER.cpp \
		sources/Commands/DIE.cpp \
		sources/Commands/JOIN.cpp \
		sources/Commands/KICK.cpp \
		sources/Commands/LIST.cpp \
		sources/Commands/PING.cpp \
		sources/Commands/MODE.cpp \
		sources/Commands/NAMES.cpp \
		sources/Commands/NOTICE.cpp \
		sources/Commands/OPER.cpp \
		sources/Commands/PART.cpp \
		sources/Commands/PASS.cpp \
		sources/Commands/PRIVMSG.cpp \
		sources/Commands/QUIT.cpp \
		sources/Commands/TOPIC.cpp \
		sources/Commands/WALLOPS.cpp \
		sources/Commands/INVITE.cpp \
		sources/Commands/WHOIS.cpp

INCDIR = ./includes

INCS = $(shell find $(INCDIR) -type d)

OBJDIR = ./objects

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

DEPS = $(OBJS:.o=.d)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -I $(INCDIR) -MMD -MP -std=c++98 -g3 #-fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) -r $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
