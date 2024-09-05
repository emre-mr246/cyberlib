#include "../inc/cyberlib.h"
#include <stdint.h>
#include <stdlib.h>

static const char	base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
									"abcdefghijklmnopqrstuvwxyz"
									"0123456789+/";

char	*base64_encode(const char *data)
{
	int			mod;
	int			input_length;
	int			output_length;
	char		*encoded_data;
	uint32_t	octet_a;
	uint32_t	octet_b;
	uint32_t	octet_c;
	uint32_t	triple;
	int i, j;

	i = 0, j = 0;
	input_length = ft_strlen(data);
	output_length = 4 * ((input_length + 2) / 3);
	if (output_length + 1 > BUFFER_SIZE)
		return (NULL);
	encoded_data = (char *)ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!encoded_data)
		return (NULL);
	while (i < input_length && j < (BUFFER_SIZE - 4))
	{
		octet_a = i < input_length ? (unsigned char)data[i++] : 0;
		octet_b = i < input_length ? (unsigned char)data[i++] : 0;
		octet_c = i < input_length ? (unsigned char)data[i++] : 0;
		triple = (octet_a << 16) | (octet_b << 8) | octet_c;
		encoded_data[j++] = base64_chars[(triple >> 18) & 0x3F];
		encoded_data[j++] = base64_chars[(triple >> 12) & 0x3F];
		encoded_data[j++] = base64_chars[(triple >> 6) & 0x3F];
		encoded_data[j++] = base64_chars[triple & 0x3F];
	}
	mod = input_length % 3;
	if (mod > 0)
	{
		for (i = 0; i < 3 - mod; i++)
			encoded_data[output_length - 1 - i] = '=';
	}
	encoded_data[output_length] = '\0';
	return (encoded_data);
}

static int	base64_index(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	else if (c >= 'a' && c <= 'z')
		return (c - 'a' + 26);
	else if (c >= '0' && c <= '9')
		return (c - '0' + 52);
	else if (c == '+')
		return (62);
	else if (c == '/')
		return (63);
	else
		return (-1);
}

static char	*base64_initialize(const char *data, int *output_len)
{
	char	*decoded_data;
	int		data_len;

	if (!data)
		return (NULL);
	data_len = ft_strlen(data);
	if (data_len % 4 != 0)
		return (NULL);
	*output_len = (data_len / 4) * 3;
	if (data[data_len - 1] == '=')
		(*output_len)--;
	if (data[data_len - 2] == '=')
		(*output_len)--;
	decoded_data = (char *)ft_calloc(sizeof(char), *output_len + 1);
	if (!decoded_data)
		return (NULL);
	return (decoded_data);
}

char	*base64_decode(const char *data)
{
	int			output_length;
	char		*decoded_data;
	uint32_t	triple;

	int i, j;
	int sextet_a, sextet_b, sextet_c, sextet_d;
	decoded_data = base64_initialize(data, &output_length);
	if (!decoded_data)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while ((size_t)i < ft_strlen(data))
	{
		sextet_a = data[i] == '=' ? 0 : base64_index(data[i]);
		sextet_b = data[i + 1] == '=' ? 0 : base64_index(data[i + 1]);
		sextet_c = data[i + 2] == '=' ? 0 : base64_index(data[i + 2]);
		sextet_d = data[i + 3] == '=' ? 0 : base64_index(data[i + 3]);
		if (sextet_a == -1 || sextet_b == -1 || sextet_c == -1 || sextet_d ==
			-1)
		{
			free(decoded_data);
			return (NULL);
		}
		triple = (sextet_a << 18) | (sextet_b << 12) | (sextet_c << 6) | sextet_d;
		if (j < output_length)
			decoded_data[j++] = (triple >> 16) & 0xFF;
		if (j < output_length)
			decoded_data[j++] = (triple >> 8) & 0xFF;
		if (j < output_length)
			decoded_data[j++] = triple & 0xFF;
		i += 4;
	}
	decoded_data[output_length] = '\0';
	return (decoded_data);
}
