#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>
# include <unistd.h>

size_t	ft_strlen(char const *str);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char const *str, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_bzero(void *s, size_t n);

#endif
