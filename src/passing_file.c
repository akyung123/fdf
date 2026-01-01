/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:23:33 by akkim             #+#    #+#             */
/*   Updated: 2026/01/01 16:11:12 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void get_map_size(t_image image, int fd)
{
	char *line;
	char **data;
	int	i;

	i = 0;
	// fd에서 한 줄씩 읽어오기
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		data = ft_split(line, ' ');
		image.width = ft_strlen(line) / 2 + 1;
		free(line);
		i++;
	}
	image.height = i;
	ft_printf("%d %d\n", image.width, image.height);
}

void init_file(t_image *image, char *path)
{
	int	fd;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("file open error");
	get_map_size(*image, fd); // fd를 통해 파일을 읽어서 맵 사이즈, 값 파싱하기
	close(fd);
	// 예외처리해야함
	// 파일 내 정보가 직사각형의 좌표값인지
	// 모든 행에서 같은 크기의 열인지
	// 파일 내 정보고 숫자로만 이루어져있는지
	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("file open error");
	// save_map_data();
	// 파일 좌표 구하기
	close(fd);
}
