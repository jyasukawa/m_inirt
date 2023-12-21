/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kousuzuk <kousuzuk@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:14:13 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/12/05 15:09:42 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <errno.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define ON 1
# define OFF 0

# define YES -1
# define NO 1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

// Part 1 functions
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t			ft_strlen(char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, void *src, size_t n);
void				*ft_memmove(void *dst, void *src, size_t len);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, char *src, size_t dstsize);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(char *s, int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(char *s1, char *s2, size_t n);
void				*ft_memchr(void *s, int c, size_t n);
int					ft_memcmp(void *s1, void *s2, size_t n);
char				*ft_strnstr(char *haystack, char *needle, size_t len);
int					ft_atoi(char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(char *s1);
char				*ft_strndup(char *s1, size_t n);

// Part 2 functions
char				*ft_substr(char *s, unsigned int start, size_t len);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strtrim(char *s1, char *set);
char				**ft_split(char *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

// Bonus functions
t_list			*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_printf(char *format, ...);
void				ft_putnbr_count(int n, int *count);
void				ft_putaddress_count(uintptr_t address, int *count,
						int flag);
void				ft_putunsigned_count(unsigned int u, int *count);
void				ft_puthex_count(unsigned int u, int *count, char c);
void				ft_putchar_count(int c, int *count);
void				ft_putstr_count(char *s, int *count);

char				*get_next_line(int fd);
char				*ft_strchr_null(char *s, char c);
char				*ft_strjoin_free(char *buffer, char *tmp, int *is_error);
char				*ft_calloc_forone(size_t count, size_t size);
char				*ft_error_found(char *buffer, int *is_error);

int					ft_printf_stderr(char *format, ...);
void				ft_putnbr_count_stderr(int n, int *count);
void				ft_putaddress_count_stderr(uintptr_t address, int *count,
						int flag);
void				ft_putunsigned_count_stderr(unsigned int u, int *count);
void				ft_puthex_count_stderr(unsigned int u, int *count, char c);
void				ft_putchar_count_stderr(int c, int *count);
void				ft_putstr_count_stderr(char *s, int *count);

#endif
