NAME = RPN
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address
SRCS = RPN.cpp main.cpp
OBJS = $(SRCS:.cpp=.o)
INCS = RPN.hpp
RM = rm -f
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
all: $(NAME)
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all