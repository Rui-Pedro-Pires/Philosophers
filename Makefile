SRC = finex.c philo.c rotine.c utils.c init.c

OBJ = $(SRC:.c=.o)

CFLAGS = -pthread -Wall -Werror -Wextra

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