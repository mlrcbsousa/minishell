/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msousa <msousa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 23:15:21 by manuel            #+#    #+#             */
/*   Updated: 2022/02/11 15:32:43 by msousa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <errno.h>
# include <limits.h>

# include "ft_boolean.h"
# include "ft_printf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

# ifndef STDIN
#  define STDIN 0
# endif

# ifndef STDOUT
#  define STDOUT 1
# endif

# ifndef STDERR
#  define STDERR 2
# endif

# define DECIMAL "0123456789"
# define HEX "0123456789abcdef"
# define HEXU "0123456789ABCDEF"
# define BINARY "01"
# define OCTAL "01234567"

// Boolean
t_bool	ft_isalpha(int c);
t_bool	ft_isdigit(int c);
t_bool	ft_isalnum(int c);
t_bool	ft_isascii(int c);
t_bool	ft_isprint(int c);
t_bool	ft_isspace(char c);
t_bool	ft_isfloat(char *str);
t_bool	ft_isnumber(char *str);
t_bool	ft_isnumber_u(char *str);
t_bool	ft_ternary(int condition, int a, int b);

// Convert
double	ft_atof(char *str);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
char	*ft_itoa(int n);
char	*ft_uitoa(unsigned int n);
char	*ft_ultoa_base(unsigned long n, char *radix);

// List
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstfind(t_list *list, void *data, int (*cmp)());
t_list	*ft_lstat(t_list *list, unsigned int nbr);
t_list	*ft_lstdup_int(t_list *list);
void	*ft_lstmin_int(t_list *list);
void	*ft_lstmax_int(t_list *list);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstsort(t_list *list, int start, int end);
t_bool	ft_islstsorted_int(t_list *list);

// Math
int		ft_abs(int n);
size_t	ft_ullen(unsigned long nbr);
size_t	ft_ullen_base(unsigned long nbr, int base);
char	*ft_ultoa_base(unsigned long n, char *radix);
long	ft_pow(int nb, int power);
double	ft_fabs(double n);

// Memory
void	*ft_memset(void *str, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *str1, const void *str2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

// Print
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putnbr_base(long long nb, char *radix);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putendl(char *str);

// String
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strcpy(char *dst, const char *src);
int		ft_strnchr(const char *str, int c);
int		get_next_line(int fd, char **line);
int		ft_strcmp(const char *s1, const char *s2);
t_bool	ft_streq(char const *s1, char const *s2);

#endif
