CC = c++
FTNAME = ft_containers
STDNAME = std_containers
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -O3
SRC = main.cpp
HEADERS = ./utils/*.hpp ./*.hpp

all: $(FTNAME) $(STDNAME)

$(FTNAME): $(SRC) $(HEADERS)
	@$(CC) $(CPPFLAGS) $(SRC) -o $(FTNAME)

$(STDNAME): $(SRC) $(HEADERS)
	@$(CC) $(CPPFLAGS) $(SRC) -o $(STDNAME) -DSTD

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(FTNAME)
	@rm -f $(STDNAME)

re: fclean all
