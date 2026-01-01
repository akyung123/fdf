/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 03:49:30 by akkim             #+#    #+#             */
/*   Updated: 2026/01/01 16:07:20 by akkim            ###   ########.fr       */
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

typedef struct l_vars
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
}	t_vars;

typedef struct l_image
{
	int	width;
	int	height;
	int	bpp;        // bits per pixel
	int size_line;  // 한 줄을 저장하는 데 필요한 바이트 수
	int endian;     // 픽셀 저장 방식
}	t_image;

int mouse_event(int button, int x, int y, void *param);
int close_window(void *param);
int expose_event(void *param);
int key_event(int keycode, void *param);
void	draw_image(unsigned char *img_addr, t_image image);
void init_file(t_image *image, char *path);

#endif