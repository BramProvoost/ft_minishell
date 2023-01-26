NAME		:= minishell
CFLAGS		:= -Wextra -Wall -Werror
CFLAGS		+= $(if $(FSAN) , -fsanitize=address -g)
CFLAGS		+= $(if $(DEBUG) , -g)
CFLAGS		+= $(if $(TEST) , -lcriterion)
LIBFT		:= old_minishell/libs/libft
HEADERS	:= $(addprefix -I , \
			  libft \
			  )

LIBS		:= $(LIBFT)/libft.a
READLINE_LIB = -lreadline
SRCS		:= $(shell find ./srcs -iname "*.c")
OBJS		:= ${SRCS:.c=.o}

FUNCTIONS_OBJ=$(OBJS:.c=.o)

all: libft $(NAME)

libft:
	@echo ======== LIBFT ========
	@$(MAKE) bonus -C $(LIBFT)


%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(FUNCTIONS_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) $(READLINE_LIB)

clean:
	@rm -rf $(OBJS)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT) 

fsan:
	$(MAKE) FSAN=1

resan: fclean
	$(MAKE) fsan

debug:
	$(MAKE) DEBUG=1

rebug: fclean
	$(MAKE) debug

test:
	$(MAKE) TEST=1

retest: fclean
	$(MAKE) test


re: clean all

.PHONY: all, clean, fclean, re, libmlx
