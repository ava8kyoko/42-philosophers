# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchampag <mchampag@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/23 09:25:26 by mchampag          #+#    #+#              #
#    Updated: 2023/08/17 18:17:26 by mchampag         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = philo

# Flags
AR = ar
CC = gcc
ARFLAG = rcs
CFLAG = -Wall -Wextra -Werror -g 
# -fsanitize=thread
LDFLAGS = -phtread -lpthread

# Files sources
S = src/
SRC_FILE = main.c parsing.c print.c routine.c sleep_time.c
SRC = $(addprefix $S, $(SRC_FILE))

# Object conversion
O = obj/
OBJ= $(SRC:$S%=$O%.o)
$O%.o: $S%
	@printf "$R■$W "
	@$(CC) $(CFLAG) -c $< -o $@

# Main rule
all: init $(NAME)
	@echo "$G$(NAME) compiled$W"
	
# Initialise librairies and making objs folder
init:
	@mkdir -p $O
	@echo "$GLibrary's initialisation$W"
# @$(MAKE) -s -C
# @printf "$CCreating $(NAME)\n$W"

# Creating  executable
$(NAME): $(OBJ)
	@$(CC) $(CFLAG) -o $@ $^

# Cleaning/
REMOVE = rm -rf

clean:
	@$(REMOVE) $O
# @$(MAKE) -s clean -C

fclean: clean
	@$(REMOVE) $(NAME)
# @$(MAKE) -s fclean -C

re:	fclean all
