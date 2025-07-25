#include "count_islands.h"

void find_len(islands* data)
{
    int i = 0;
    int len = 0;
    while (data->raw[i])
    {
        if (data->raw[i] == '\n')
        {
            len++;
        }
        i++;
    }
    data->len = len + (data->raw[i-1] != '\n');
}

void find_width(islands *data)
{
    int i = 0;
    while (data->raw[i] && data->raw[i] != '\n')
    {
        i++;
    }
    data->width = i + 1;
}

void fill_map(islands *data)
{
    data->map = (int **)malloc(sizeof(int *) * data->len);
    int i = 0;
    int x = 0;
    while (i < data->len)
    {
        data->map[i] = (int *)malloc(sizeof(int) * (data->width));
        int j = 0;
        while (j < data->width)
        {
            if (data->raw[x] == 'X')
                data->map[i][j] = -1;
            else
                data->map[i][j] = -2;
            x++;
            j++;
        }
        i++;
    }
}

void print_map(islands *data)
{
    int i = 0;
    printf("\n\n-------------------------------------\n\n");
    while (i < data->len)
    {
        int j = 0;
        while (j < data->width)
        {
            printf("%d", data->map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }

    printf("\n\n-------------------------------------\n\n");
}

void fill_zeros(char **str, int len)
{
    int i = 0;

    while (i < len)
    {
        (*str)[i] = '\0';
        i ++;
    }
}

int ft_strlen(char *s)
{
    int i = 0;
    while (s[i])
        i++;
    return i;
}

char* ft_strjoin(char *s1, char *s2)
{
    int l1 = ft_strlen(s1);
    int l2 = ft_strlen(s2);
    char *total;
    
    total = (char *)malloc(sizeof(char) * (l1 + l2 + 1));
    int i = 0;
    int x = 0;
    while (i < l1)
    {
        total[x] = s1[i];
        i++;
        x++;
    }
    i = 0;
    while (i < l2)
    {
        total[x] = s2[i];
        i++;
        x++;
    }
    total[x] = '\0';
    free(s1);
    return (total);
}


void print_data(islands *data)
{
    // printf("file_fd: %d\n", data->file_fd);
    printf("len: %d\n", data->len);
    printf("width: %d\n", data->width);
}

void parser(char **av, islands *data)
{  
    char buffer[1024];
    data->file_fd = open(av[1], O_RDONLY);
    if (data->file_fd == -1)
        exit(EXIT_FAILURE);
    data->raw = (char *)malloc(sizeof(char));
    while (read(data->file_fd, buffer, BUFFERSIZE) > 0)
    {
        data->raw = ft_strjoin(data->raw, buffer);
    }
    
    find_width(data);
    find_len(data);
    fill_map(data);
    // print_map(data);
    // print_data(data);

}


void count_islands(islands *data, int y, int x, int *size)
{
    if (x < 0 || x >= data->width || y < 0 || y >= data->len)
        return;
    if (data->map[y][x] != -1)
        return;
    
    data->map[y][x] = data->total_islands;
    (*size)++;

    count_islands(data, y, x + 1, size);
    count_islands(data, y, x - 1, size);
    count_islands(data, y + 1, x, size);
    count_islands(data, y - 1, x, size);
}

void check_each_square(islands *data)
{
    int x = 0;
    int y = 0;
    while (y < data->len)
    {
        x = 0;
        while (x < data->width)
        {
            if (data->map[y][x] == -1)
            {
                int size = 0;
                count_islands(data, y, x, &size);
                
                if (size > data->biggest_island)
                {
                    data->biggest_island = size;
                    data->which_island = data->total_islands;
                }
                
                data->total_islands++;
            }
            x++;
        }
        y++;
    }
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_final(int n)
{
    if (n == -2)
    {
        ft_putchar('.');
        return ;
    }
	if (n >= 10)
	{
		print_final(n / 10);
	}
	ft_putchar(n % 10 + '0');
}

void set_back(islands *data)
{
    int x = 0;
    int y = 0;
    while (y < data->len)
    {
        x = 0;
        while (x < data->width - 1)
        {
            print_final(data->map[y][x]);
            x++;
        }
        write(1,"\n", 1);
        y++;
    }
}

int main(int ac, char **av)
{
    static islands data;

    if (ac != 2) {
        printf("Usage: %s map_file\n", av[0]);
        return 1;
    }

    data.total_islands = 0;
    data.biggest_island = 0;
    data.which_island = 0;

    parser(av, &data);
    // print_map(&data);
    check_each_square(&data);
    set_back(&data);
    // print_map(&data);
    printf("biggest island: %d with %d characters", data.which_island, data.biggest_island);
}

return '0' +