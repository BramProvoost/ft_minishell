# Variables
NAME			:= minishell
CFLAGS			:= -Wall -Wextra -Werror
CFLAGS			:= $(CFLAGS)$(if $(FSAN) , -fsanitize=address -g)
CFLAGS			:= $(CFLAGS)$(if $(DEBUG) , -g)
SOURCES			:= $(shell find ./srcs -iname "*.c")
OBJECTS			:= $(SOURCES:.c=.o)

LIBFT			:= lib/libft
LIBS			:= $(LIBFT)/libft.a
RL_LIB			:= -L/Users/$(USER)/homebrew/opt/readline/lib -lreadline #-lhistory
RL_INC			:= -I/Users/$(USER)/homebrew/opt/readline/include

# Default target
all: $(NAME)

# Link object files to create NAME
$(NAME): libft $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(RL_LIB) -o $@

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< $(RL_INC) -o $@

libft:
	@$(MAKE) bonus -C $(LIBFT)

# Clean up object files and NAME
clean:
	rm -f $(OBJECTS)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

re: clean all

fsan:
	@$(MAKE) FSAN=1

resan: fclean
	@$(MAKE) fsan

debug:
	@$(MAKE) DEBUG=1
