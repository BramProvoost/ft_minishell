# Variables
NAME			:= minishell
CC 				:= gcc
CFLAGS			:= -Wall -Wextra -Werror
SOURCES			:= $(shell find ./srcs -iname "*.c")
OBJECTS			:= $(SOURCES:.c=.o)

LIBFT			:= old_minishell/libs/libft
LIBS			:= $(LIBFT)/libft.a
RL_LIB	:= -L/Users/$(USER)/homebrew/opt/readline/lib -lreadline -lhistory
RL_INC	:= -I/Users/$(USER)/homebrew/opt/readline/include

# Default target
all: $(NAME)

# Link object files to create NAME
$(NAME): libft $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBS) $(RL_LIB) -o $@

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< $(RL_INC) -o $@

libft:
	$(MAKE) bonus -C $(LIBFT)

# Clean up object files and NAME
clean:
	rm -f $(OBJECTS)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)

# Rule for creating dependencies
depend: $(SOURCES)
	$(CC) $(CFLAGS) -MM $^ > dependencies.d

-include dependencies.d
