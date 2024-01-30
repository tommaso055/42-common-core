#include <stdlib.h>
#include <unistd.h>

#define BUFF_SIZE 1

char	*get_next_line(fd)
{
	static char	*remaining;
	size_t		i;
	char		*temp_str;
	int			keep_itering;

	keep_itering = 1;
	remaining = NULL;
	if (remaining)
		temp_str = remaining;
	else
		read(fd, temp_str, BUFF_SIZE);
	while (keep_itering)
	{
		while (temp_str[i] != '\0' && keep_itering)
		{
			if(temp_str[i] == '\n')
				keep_itering = 0;
			i++;
		}
		if (keep_itering)
			s = strjoin();
	}
}