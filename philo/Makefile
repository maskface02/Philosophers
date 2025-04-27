NAME = philo
CC = cc -g
CFLAGS = -Wall -Wextra -Werror 


SRCS = clean.c init.c philo.c simulation.c utils.c check_utils.c utils_2.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): philo.h $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
 
.PHONY: clean
