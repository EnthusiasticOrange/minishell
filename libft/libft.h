/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjuli <mjuli@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 10:50:09 by mjuli             #+#    #+#             */
/*   Updated: 2020/12/19 15:00:48 by mjuli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# define UNUSED(x)	(void)(x)

void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(char *str, char *to_find, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strdup(const char *s);
void			*ft_calloc(size_t nmemb, size_t size);

int				ft_isspace(int c);
int				ft_isupper(int c);
int				ft_islower(int c);

char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

size_t			ft_strspn(const char *str1, const char *str2);
size_t			ft_strcspn(const char *str1, const char *str2);

char			*ft_strjoin_array(const char **array);
int				ft_strcmp(const char *s1, const char *s2);

typedef struct	s_list {
	void			*content;
	struct s_list	*next;
}				t_list;

t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **lst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
							void (*del)(void *));
t_list			*ft_lstfind(t_list *begin_list,
							void *data_ref, int (*cmp)());
void			ft_lstremove_if(t_list **begin_list,
								void *data_ref, int (*cmp)());
void			ft_lstsort(t_list **begin_list, int (*cmp)());
void			ft_lstpush_back(t_list **begin_list, void *data);

# define BUFFER_SIZE 1024

typedef	struct	s_gnl_state
{
	int		is_initialized;
	char	buffer[BUFFER_SIZE];
	int		fd;
	ssize_t	bytes_read;
	ssize_t	offset;
	char	*line;
	size_t	size;
	int		end_found;

}				t_gnl_state;

int				get_next_line(int fd, char **line);

int				ft_printf_fd(int fd, const char *format, ...);

#endif
