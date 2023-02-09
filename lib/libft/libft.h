/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:21:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/08 16:53:16 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

/*
**	Linked lists
**
** +--------------+-------------+              +--------------+-------------+
** |              |             |            \ |              |             |
** |   CONTENT    |     NEXT    |--------------|   CONTENT    |     NEXT    |
** |              |             |            / |              |             |
** +--------------+-------------+              +--------------+-------------+
** https://www.learn-c.org/en/Linked_lists
** https://www.youtube.com/watch?v=o1QaGUEi6ew
** https://www.youtube.com/watch?v=roei8Vd5814
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *str);
void	ft_bzero(char *s, int n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_isupper(int c);
char	*ft_itoa(int n);
char	*ft_itoa_base(long number, int base);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(
			t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
int		ft_putstr_fd(char *s, int fd);
/*
	Allocates (with malloc(3)) and returns an array of strings obtained by 
	splitting ’s’ using the character ’c’ as a delimiter. The array ends
	with a NULL pointer.
*/
char	**ft_split(char const *s, char c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strlendump(const char *str, size_t length);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(
			const char *source, const char *to_find, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
void	ft_strrev(char *src, char *dst);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strtolower(char *str);
char	*ft_strtoupper(char *str);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
// void	ft_striteri(char *s, void (*f)(unsigned int, char*));

#endif
