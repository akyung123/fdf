/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   passing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 15:23:33 by akkim             #+#    #+#             */
/*   Updated: 2026/01/11 23:16:43 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_split(char **split)
{
	int	i = 0;

	if (!split)
		return;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	get_width(char *file_name)
{
	int		first_width;
	int		current_width;
	int		fd;
	char	*line;
	char	*trimmed_line;
	char	**split;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (-1); // 파일 열기 실패 시
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 0); // 빈 파일
	trimmed_line = ft_strtrim(line, " \n");
	free(line);
	split = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	first_width = 0;
	while (split && split[first_width])
		first_width++;
	free_split(split);
	while ((line = get_next_line(fd)))
	{
		trimmed_line = ft_strtrim(line, " \n");
		free(line);
		split = ft_split(trimmed_line, ' ');
		free(trimmed_line);
		current_width = 0;
		while (split && split[current_width])
			current_width++;
		free_split(split);
		if (current_width != first_width)
			return (-1); // 직사각형이 아님
	}
	close(fd);
	return (first_width);
}

int	get_height(char *file_name)
{
	int		height;
	int		fd;
	char	*line;

	fd = open(file_name, O_RDONLY);
	height = 0;
	while ((line = get_next_line(fd)))
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

void	fill_z_matrix(int *z_line, char *line, t_fdf *fdf, int width)
{
	char	**split;
	char	*trimmed_line;
	int		i;
	int		current_z;

	trimmed_line = ft_strtrim(line, " \n");
	split = ft_split(trimmed_line, ' ');
	free(trimmed_line); // ft_split이 끝난 후 trimmed_line 메모리 해제
	i = 0;
	while (split[i] && i < width)
	{
		current_z = ft_atoi(split[i]);
		z_line[i] = current_z;
		if (current_z > fdf->map.z_max)
			fdf->map.z_max = current_z;
		if (current_z < fdf->map.z_min)
			fdf->map.z_min = current_z;
		i++;
	}
	free_split(split);
}

void	read_map(char *file_name, t_fdf *fdf)
{
	int	i;
	int	fd;
	char *line;

	// 예외처리해야함
	// 파일 내 정보가 직사각형의 좌표값인지
	// 모든 행에서 같은 크기의 열인지
	// 파일 내 정보고 숫자로만 이루어져있는지
	fdf->map.width = get_width(file_name);
	if (fdf->map.width <= 0)
	{
		ft_putstr_fd("Error: Invalid map format or empty file.\n", 2);
		exit(1);
	}
	fdf->map.z_min = 2147483647; // INT_MAX
	fdf->map.z_max = -2147483648; // INT_MIN
	fdf->map.height = get_height(file_name);
	fdf->map.z_matrix = (int **)malloc(sizeof(int *) * fdf->map.height);
	i = 0;
	while (i < fdf->map.height)
		fdf->map.z_matrix[i++] = (int*)malloc(sizeof(int) * fdf->map.width);
	// z 데이터 입력하기
	fd = open(file_name, O_RDONLY); 
	i = 0;
	while ((line = get_next_line(fd)))
	{
		fill_z_matrix(fdf->map.z_matrix[i], line, fdf, fdf->map.width);
		free(line);
		i++;
	}
	// Z축 높이까지 고려한 최종 Zoom 계산
	double zoom_x;
	double zoom_y;
	double angle_rad = 70 * (M_PI / 180.0); // init_file과 동일한 각도
	int z_range;

	z_range = fdf->map.z_max - fdf->map.z_min;
	zoom_x = WIDTH / ((fdf->map.width + fdf->map.height) * sin(angle_rad));
	zoom_y = HEIGHT / ((fdf->map.width + fdf->map.height) * cos(angle_rad) + z_range);

	fdf->zoom = (zoom_x < zoom_y ? zoom_x : zoom_y) * 0.7; // 더 작은 zoom 값에 70% 여백 적용
	// z_scale을 맵의 평균 크기와 높이 범위에 따라 동적으로 조절
	fdf->z_scale = fdf->zoom * (fdf->map.width + fdf->map.height) / (z_range + 1) / 20;
	if (fdf->z_scale < 0.1)
		fdf->z_scale = 0.1;
	if (fdf->z_scale > fdf->zoom)
		fdf->z_scale = fdf->zoom;
	close(fd);
}

void init_file(t_fdf *fdf)
{
	fdf->mlx_ptr = mlx_init();
	if (!fdf->mlx_ptr)
		perror("MLX init failed");
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, WIDTH, HEIGHT, "FdF - akkim");
	fdf->image.img_ptr = mlx_new_image(fdf->mlx_ptr, WIDTH, HEIGHT);
	fdf->image.addr = mlx_get_data_addr(fdf->image.img_ptr, &fdf->image.bpp, \
										&fdf->image.size_line, &fdf->image.endian);
	fdf->angle = 50 * (M_PI / 180.0); // 50 degrees
	fdf->offset_x = WIDTH / 2;
	fdf->offset_y = HEIGHT / 2;
}
