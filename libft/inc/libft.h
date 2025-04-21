/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igvisera <igvisera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 00:04:22 by drestrep          #+#    #+#             */
/*   Updated: 2025/04/21 20:56:06 by igvisera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdint.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 69
# endif

// LIBFT
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_strlen(const char *str);
int		ft_isalpha(int c);
int		ft_isdigit(int n);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_issign(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_atoi(const char *str);
int		ft_atoi_base(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_lstsize(t_list *lst);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_get_string(char *s1, char start, char end);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strcmp(const char *str1, const char *str2);
char	*ft_revstrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_itoa(int n);
char	**ft_split(char const *s, char c);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// 		GET_NEXT_LINE
char	*get_next_line(int fd);
char	*ft_readed(int fd, char *readed);
char	*ft_get_line(char *left_str);
char	*ft_next_line_gnl(char *readed);
char	*ft_strchr_gnl(char *s, int c);
int		ft_strlen_gnl(const char *str);
char	*ft_strjoin_gnl(char *readed, char *stash);
void	*ft_calloc_gnl(size_t count, size_t size);

//		FT_PRINTF
int		ft_printf(char const *str, ...);
void	ft_datatype(va_list list, char c, int *len, int *i);
void	ft_putchar(char c, int *len);
void	ft_putstr(char *str, int *len);
void	ft_putptr(size_t ptr, int *len);
void	ft_putnbr(int nbr, int *len);
void	ft_unsigned_int(int var, int *len);
void	ft_hexadecimal(unsigned int nbr, int *len, char c);

//		FT_MALLOC
void	*ft_malloc(int size);

//		FT_EXIT
void	*ft_exit(char *message);

#endif
