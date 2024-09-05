#ifndef CYBERLIB_H
# define CYBERLIB_H

#include <unistd.h>

#define BUFFER_SIZE 4096

// BASE64
char *base64_encode(const char *data);
char *base64_decode(const char *data);

//URL
char *url_encode(const char *str);
char *url_decode(const char *str);

// UTILS
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);

#endif