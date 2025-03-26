#include "minishell.h"

int	ft_putchar_fd(char c, int fd)
{
	return ((int)write(fd, &c, 1));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			size_src;

	i = 0;
	if (src == NULL)
		return (0);
	size_src = ft_strlen(src);
	if ((int)size < 0)
		size = size_src + 1;
	if (size >= 2 && size_src != 0)
	{
		while (i < size - 1)
		{
			if (i < size_src)
				dst[i] = src[i];
			else if (i == size_src)
				dst[i] = '\0';
			i++;
		}
	}
	if (size != 0)
		dst[i] = '\0';
	return (size_src);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (nmemb <= 0 || size <= 0)
		str = (char *)malloc(1);
	else
		str = (char *)malloc(nmemb * size);
	if (!str)
		return (NULL);
	return (ft_memset(str, 0, nmemb * size));
}

int	ft_nbrlen(long n, int base)
{
	int	len;

	len = 0;
	if (!base)
		base = 10;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (i < n)
	{
		*ptr = (unsigned char)c;
		ptr++;
		i++;
	}
	return (s);
}
