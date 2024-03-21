# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rde-mour <rde-mour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/02 19:57:40 by rde-mour          #+#    #+#              #
#    Updated: 2024/03/21 11:05:16 by rde-mour         ###   ########.org.br    #
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
RESET		:=	$(shell tput sgr0)
TITLE		:=	$(YELLOW)$(basename $(NAME))$(RESET)

# 1: action, 2: target, 3: color
define message
	$(info [$(TITLE)] $(3)$(1)$(RESET) $(2))
endef

RM			:=	rm -f
MAKEFLAGS	+=	--silent --no-print-directory

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
	src/get_env.c \
	src/get_env_utils.c \
	src/strfmt.c \
	src/tokenizer.c \
	src/append_flags.c \
	src/parser.c \
	src/var_expansions.c \
	src/command_expansions.c \
	src/ast.c \
	util/arraylist.c \
	util/strjoinsep.c \
	util/ft_printf/ft_build_bonus.c \
	util/ft_printf/ft_build_character_bonus.c \
	util/ft_printf/ft_build_config_bonus.c \
	util/ft_printf/ft_build_hexadecimal_bonus.c \
	util/ft_printf/ft_build_number_bonus.c \
	util/ft_printf/ft_build_pointer_bonus.c \
	util/ft_printf/ft_build_string_bonus.c \
	util/ft_printf/ft_build_unsigned_bonus.c \
	util/ft_printf/ft_find_characters_bonus.c \
	util/ft_printf/ft_printf_bonus.c \
	util/ft_printf/ft_printf_utils_bonus.c \

SRCS		:=	$(addprefix $(SRC_DIR)/,$(SRCS))

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #
BUILD_DIR	:=	build

OBJS		:=	$(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS		:=	$(OBJS:.o=.d)

CC			:=	cc
CFLAGS		:=	-Wall -Wextra -Werror -g3
CPPFLAGS	:=	$(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS		:=	$(addprefix -L,$(dir $(LIBS)))
LDLIBS		:=	-lft -lreadline

ifdef WITH_DEBUG
	TITLE += $(MAGENTA)debug$(RESET)
	CFLAGS += -g
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
