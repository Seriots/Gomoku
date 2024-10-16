
NAME		=	Gomoku

define SRCS =
	main.cpp
	srcs/Cell.cpp
	srcs/Board.cpp
	srcs/Game.cpp
	srcs/Game_heuristic.cpp
	srcs/Game_end.cpp
	srcs/request.cpp
	srcs/utils.cpp

endef
SRCS := $(strip $(SRCS))

OBJS_DIR	=	objs
OBJS		= 	$(addprefix $(OBJS_DIR)/,$(SRCS:.cpp=.o))
DEPS		=	$(OBJS:.o=.d)

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -Iincludes -g

# Color
# -------------------------------------------------------------------------
_GREY		= \033[30m
_RED		= \033[31m
_GREEN		= \033[32m
_YELLOW		= \033[33m
_BLUE		= \033[34m
_PURPLE		= \033[35m
_CYAN		= \033[36m
_WHITE		= \033[37m
_NO_COLOR	= \033[0m
# -------------------------------------------------------------------------

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: %.cpp
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
		echo -e "\n$(_BLUE)$(dir $@): Create$(_NO_COLOR)"; \
	fi
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR)/%.d: %.cpp Makefile
	@if [ ! -d $(dir $@) ]; then \
		mkdir -p $(dir $@); \
		echo "\n$(_BLUE)$(dir $@): Create$(_NO_COLOR)"; \
	fi
	$(CXX) -MM -MT $(@:.d=.o) $(CXXFLAGS) $(INCLUDES) $< >> $@

clean:
	rm -Rf $(OBJS_DIR) 2> /dev/null || true
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)