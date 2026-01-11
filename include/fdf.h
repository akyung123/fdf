/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 03:49:30 by akkim             #+#    #+#             */
/*   Updated: 2026/01/11 17:10:46 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

// 그냥 pipex 포함 헤더 다 가져옴. 수정해야함
# include "libft.h"
# include "get_next_line.h"
# include "printf.h"
# include <mlx.h>
# include <math.h>
// # include <keysymdef.h>

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# define HEIGHT 1080
# define WIDTH 1920
// 임의의 고정 크기, 추후 파일의 크기에 따라서 변함

typedef struct l_point
{
	int x;
	int	y;
	int	z;
} t_point;

typedef struct s_map
{
	int		width;
	int		height;
	int		**z_matrix; // ?
	int		z_min;
	int		z_max;
}	t_map;

typedef struct l_image
{
	void	*img_ptr;
	void *addr;
	int	width;
	int	height;
	int	bpp;        // bits per pixel
	int size_line;  // 한 줄을 저장하는 데 필요한 바이트 수
	int endian;     // 픽셀 저장 방식
}	t_image;

typedef struct l_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	image;
	t_map	map;
	double	zoom;
	double	z_scale;
	double	angle;
	int		offset_x;
	int		offset_y;
}	t_fdf;


int create_argb(int a, int r, int g, int b);
int mouse_event(int button, int x, int y, void *param);
int close_window(void *param);
int expose_event(void *param);
int key_event(int keycode, void *param);
void	draw(t_fdf *fdf);
void init_file(t_fdf *fdf);
void	read_map(char *file_name, t_fdf *fdf);
int	get_default_color(int z);
int	get_color(t_point current, t_point p1, t_point p2, int p1_color, int p2_color);

#endif