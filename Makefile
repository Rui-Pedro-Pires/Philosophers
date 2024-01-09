SRC = finex.c philo.c rotine.c \
		time_utils.c init.c monitoring.c \
		mutex_utils1.c mutex_utils2.c atoi.c checkers.c

OBJ = $(SRC:.c=.o)

CFLAGS = -pthread -Wall -Werror -Wextra -fsanitize=thread

CC = cc

RM = rm -f

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all