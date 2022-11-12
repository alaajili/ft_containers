NAME = z
SRCS = z.cpp 
OBJS = $(SRCS:.cpp=.o)
CC = clang++
CPPFLAGS = -Wall -Werror -Wextra -std=c++11 #-fsanitize=address
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all