SRC = ./src/finex.c ./src/philo.c ./src/rotine.c \
		./src/time_utils.c ./src/init.c ./src/monitoring.c \
		./src/mutex_utils1.c ./src/mutex_utils2.c ./src/atoi.c ./src/checkers.c

OBJ = $(SRC:.c=.o)

CFLAGS = -pthread -Wall -Werror -Wextra -fsanitize=thread

CC = cc

RM = rm -f

NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "Compiling objects"
	@echo "Creating program philo"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all