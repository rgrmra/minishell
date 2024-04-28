# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 10:09:46 by yuuko             #+#    #+#              #
#    Updated: 2024/04/28 18:55:16 by rde-mour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	minishell

# **************************************************************************** #
#    Misc                                                                      #
# **************************************************************************** #

RED			:=	$(shell tput setaf 1)
GREEN		:=	$(shell tput setaf 2)
YELLOW		:=	$(shell tput setaf 3)
BLUE		:=	$(shell tput setaf 4)
MAGENTA		:=	$(shell tput setaf 5)
CYAN		:=	$(shell tput setaf 6)
WHITE		:=	$(shell tput setaf 7)
ERROR		:=	$(shell tput setab 1)$(WHITE)
SUCCESS		:=	$(shell tput setab 2)$(WHITE)
WARNING		:=	$(shell tput setab 3)$(WHITE)
INFO		:=	$(shell tput setab 4)$(WHITE)
RESET		:=	$(shell tput sgr0)
CLEAR		:=	$(shell tput cuu1; tput el)
TITLE		:=	$(YELLOW)$(basename $(NAME))$(RESET)

# 1: action, 2: target, 3: color
define message
	$(info [$(TITLE)] $(3)$(1)$(RESET) $(2))
endef

RM			:=	rm -f
MAKEFLAGS	+=	--no-print-directory

# **************************************************************************** #
#    Dependencies                                                              #
# **************************************************************************** #

LIBS		:=	\
	lib/libft/libft.a \

INCS		:=	\
	include \
	lib/libft/include \

# **************************************************************************** #
#    Sources                                                                   #
# **************************************************************************** #

SRC_DIR		:=	./

SRCS		:=	\
	src/main.c \
	src/getenv/get_env.c \
	src/getenv/get_env_utils.c \
	src/prompt/prompt.c \
	src/prompt/format_input.c \
	src/tokenizer/tokenizer.c \
	src/tokenizer/append_commands.c \
	src/parser/parser.c \
	src/expansions/var_expansions.c \
	src/expansions/command_expansions.c \
	src/expansions/remove_quotes.c \
	src/ast/ast.c \
	src/ast/ast_utils.c \
	src/builtin/heredoc.c \
	src/builtin/exit.c \
	src/execution/execution.c \
	src/execution/execute_condition.c \
	src/execution/execute_subshell.c \
	src/execution/execute_redirection.c \
	src/execution/execute_pipe.c \
	src/execution/execute_command.c \
	util/arraylist.c \
	util/strjoinsep.c \
	util/strrplc.c \

SRCS		:=	$(addprefix $(SRC_DIR)/, $(SRCS))

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #

BUILD_DIR	:=	build

OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:=	$(OBJS:.o=.d)

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror
CPPFLAGS	:=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:=	$(addprefix -L,$(dir $(LIBS)))
LDLIBS		:=	-lft -lreadline

ifdef WITH_DEBUG
	TITLE += $(MAGENTA)debug$(RESET)
	CFLAGS += -g3
endif

ifdef WITH_SANITIZER
	TITLE += $(MAGENTA)sanitizer$(RESET)
	CFLAGS += -fsanitize=address
endif

all: $(NAME)

$(NAME): $(LIBS) $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(NAME)
	$(call message,CREATED,$(NAME),$(BLUE))

$(LIBS):
	$(MAKE) -C $(@D)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	$(call message,CREATED,$(basename $(notdir $@)),$(GREEN))

clean:
	for lib in $(dir $(LIBS)); do $(MAKE) -C $$lib clean; done
	$(RM) -r $(BUILD_DIR)
	$(call message,DELETED,$(BUILD_DIR),$(RED))

fclean: clean
	for lib in $(dir $(LIBS)); do $(MAKE) -C $$lib fclean; done
	$(RM) $(NAME)
	$(call message,DELETED,$(NAME),$(RED))

re:
	$(MAKE) fclean
	$(MAKE) all

run: re
	./$(NAME)

update:
	git stash
	git pull
	git submodule update --init
	git stash pop

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v 'info'

print-%:
	$(info '$*'='$($*)')

.PHONY: all clean fclean re run update
.SILENT:
.IGNORE: clean fclean run update

-include $(DEPS)
