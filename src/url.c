#include "../inc/cyberlib.h"
#include <ctype.h>
#include <stdio.h>

char	*url_encode(const char *str)
{
	char	*encoded_str;
	char	*pencoded;

	encoded_str = ft_calloc(sizeof(char), (ft_strlen(str) * 3) + 1);
	if (!encoded_str)
	{
		return (NULL);
	}
	pencoded = encoded_str;
	while (*str)
	{
		if (isalnum((unsigned char)*str) || *str == '-' || *str == '_'
			|| *str == '.' || *str == '~')
			*pencoded++ = *str;
		else
			pencoded += sprintf(pencoded, "%%%02X", (unsigned char)*str);
		str++;
	}
	*pencoded = '\0';
	return (encoded_str);
}

char	*url_decode(const char *str)
{
	char *decoded_str;
	char *pdecoded;
	int value;

	decoded_str = (char *)ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!decoded_str)
		return (NULL);
	pdecoded = decoded_str;
	while (*str)
	{
		if (*str == '%')
		{
			if (str[1] && str[2] && isxdigit((unsigned char)str[1])
				&& isxdigit((unsigned char)str[2]))
			{
				sscanf(str + 1, "%2x", &value);
				*pdecoded++ = (char)value;
				str += 3;
			}
			else
				*pdecoded++ = *str++;
		}
		else
			*pdecoded++ = *str++;
	}
	*pdecoded = '\0';
	return (decoded_str);
}