NAME = btc
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = BitcoinExchange.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
INCS = BitcoinExchange.hpp
RM = rm -f
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all