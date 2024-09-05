#include <stdint.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_bzero(void *str, size_t n)
{
	unsigned char	*ptr;

	if (!str)
		return ;
	ptr = (unsigned char *)str;
	while (n > 0)
	{
		*ptr++ = 0;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void *result;
	size_t res_size;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	res_size = count * size;
	result = malloc(res_size);
	if (!result)
		return (NULL);
	ft_bzero(result, res_size);
	return (result);
}