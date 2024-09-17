NAME = philo

SRCS = src/destroy_mutex.c src/initialization.c src/philo_main.c utils/parsing_utils.c src/fork_handle.c \
		src/philo_parsing.c src/philo_routine.c src/print_action.c src/set_time.c src/check_all.c src/create_thread.c

OBJS=$(SRCS:.c=.o)

RM=rm -f

CC= clang

CFLAGS= -Wall -Wextra -Werror -g
INCFLAGS = -includes
LDFLAGS = -lpthread

all: $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(INCFLAGS) $(CFLAGS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
