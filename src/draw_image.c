/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 04:50:51 by akkim             #+#    #+#             */
/*   Updated: 2026/01/11 22:43:09 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define DEG 0.01745329252  // PI / 180

// 아니 제가 꿈에서 분명 다 짰거든요...
// 왜 일어나니깐 현실 반영이 안되어잇지
// 슬프네요 
// 다시 짜야하는 현실이...

// RGB 값을 받아서 mlx용 색상 정수로 반환
int create_argb(int a, int r, int g, int b)
{
    // r, g, b는 0~255 범위라고 가정
    return (a << 24 | r << 16) | (g << 8) | b;
}

int ft_memaddr(int x, int y, int sl, int bpp)
{
	return (y * sl + x * bpp / 8);
}

void    mlx_pixel_put_to_image(t_image *image, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < image->width && y >= 0 && y < image->height)
    {
        dst = image->addr + (y * image->size_line + x * (image->bpp / 8));
        *(unsigned int*)dst = color;
    }
}

// 점 찍기 함수
// 어떤 이미지에 점을 찍을 건지
// 위치는 어디인지, 어떤 색깔인지
void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char *dst;

	if (x >= 0 && x < WIDTH && y>= 0 && y < HEIGHT)
	{
		dst = image->addr + (y * image->size_line + x * (image->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

// 점 위치 계산 함수 -> 점 위치를 이동시켜줌
void	isometric(t_point *p, t_fdf *fdf) // 점의 위치를 바꿔야하기에 포인터 사용
{
	int	prev_x;
	int	prev_y;
	(void) fdf;
	
	// 점들 사의 거리는 보통 1
	// 이를 zoom 변수를 이용해서 조정한다
	// p->x *= 25;
	p->x -= fdf->map.width / 2;
	p->y -= fdf->map.height / 2;

	p->x *= fdf->zoom;
	p->y *= fdf->zoom;
	p->z *= fdf->z_scale;
	// 0.1을 z_ratio와 같은 변수로 만든 후 조절하는 걸 추천함

	prev_x = p->x;
	prev_y = p->y;

	// 위치 계산(등각투영)
	// p->x = (prev_x - prev_y) * cos(0.523599);
	// p->y = (prev_x + prev_y) * sin(0.523599) - p->z;
	// p->x = (prev_x - prev_y) * cos(30 * DEG);
	p->x = (prev_x - prev_y) * sin(fdf->angle);
	p->y = (prev_x + prev_y) * cos(fdf->angle) - p->z;
	// 우리의 mlx는 제 4분면에 위치한다...! 
	
	// 화면 중앙 기준으로 정렬시키기!
	p->x += fdf->offset_x;
	p->y += fdf->offset_y;
}

// 선긋기 함수
// 2차 방정식의 직선을 생각하면 좋다
// y = ax + b로 이루어진 직선의 방정식을 구하기위해서
// 우리는 한 번 그리는 점이 얼만큼 이동할지 생각하면 좋다
// 점 p1 과 p2를 지나는 직선의 방정식은?
// y = (p1.x - p2.x)x + (p1.y - p2.y)

void    bresenham(t_point p1, t_point p2, t_fdf *fdf)
{
	int color = create_argb(255, 255, 255, 255); // 초기 설정은 흰색으로 설정함
	int err[2]; // 차이값 <-브레젠험 함수에서 사용함!

	t_point delta;
	t_point sign;
	t_point curr;
	// int		p1_color = get_default_color(p1.z);
	// int		p2_color = get_default_color(p2.z);

	isometric(&p1, fdf);
	isometric(&p2, fdf);

	delta.x = abs(p2.x - p1.x);
	delta.y = abs(p2.y - p1.y);
	sign.x = p1.x < p2.x ? 1 : -1;
	sign.y = p1.y < p2.y ? 1 : -1;
	err[0] = delta.x - delta.y;
	curr = p1; // 움직이면서 그려지는 점

	while (1)
    {
        color = get_color(curr, p1, p2, get_default_color(p1.z), get_default_color(p2.z));
        my_mlx_pixel_put(&fdf->image, curr.x, curr.y, color);
        
        if (curr.x == p2.x && curr.y == p2.y) // 정확히 도달하면 종료
            break;

        err[1] = err[0] * 2;
        if (err[1] > -delta.y)
        {
            err[0] -= delta.y;
            curr.x += sign.x;
        }
        if (err[1] < delta.x)
        {
            err[0] += delta.x;
            curr.y += sign.y;
        }
    }
}

static void	calculate_vertical_offset(t_fdf *fdf)
{
	double	y_min;
	double	y_max;
	double	y_proj;
	double	x_scaled;
	double	y_scaled;

	x_scaled = (fdf->map.width / 2.0) * fdf->zoom;
	y_scaled = (fdf->map.height / 2.0) * fdf->zoom;
	y_proj = (x_scaled + y_scaled) * cos(fdf->angle);
	y_max = y_proj - (fdf->map.z_min * fdf->z_scale);
	y_min = -y_proj - (fdf->map.z_max * fdf->z_scale);
	fdf->offset_y = HEIGHT / 2 - (y_max + y_min) / 2;
}

void	draw(t_fdf *fdf)
{
	int	x;
	int	y;

	// 1. 이미지 버퍼 초기화 (검은색으로 채우기)
	ft_bzero(fdf->image.addr, WIDTH * HEIGHT * (fdf->image.bpp / 8));

	// 2. 현재 zoom, angle, z_scale을 기준으로 시각적 중심 계산
	calculate_vertical_offset(fdf);

	// 3. 맵 그리기
	// (기존 코드는 여기에 있었음)

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				bresenham((t_point){x, y, fdf->map.z_matrix[y][x]}, \
						(t_point){x + 1, y, fdf->map.z_matrix[y][x + 1]}, fdf);
			if (y < fdf->map.height - 1)
				bresenham((t_point){x, y, fdf->map.z_matrix[y][x]}, \
						(t_point){x, y + 1, fdf->map.z_matrix[y + 1][x]}, fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->image.img_ptr, 0, 0);
}

// // 점 위치 생성하는 함수
// t_coordinate	**ft_dot(unsigned char *img_addr, t_image image)
// {
// 	t_coordinate **coords;
// 	int i = 0;
// 	int j = 0;
// 	// int x_init = image.width / 2;
// 	// int y_init = image.height / 2;
// 	int x_init = 250;
// 	int y_init = 250;
// 	// 	// 주어진 한칸 위치 계산해서 점 찍기
// 	// 	// 첫 값을 찍고(0, 0) 
// 	//	// (0, 1)이면 (30 * cos(60 * DEG), - 30 * sin(60 * DEG))
// 	//	// (0, 2)이면 (2 * 30 * cos(60 * DEG), 2 * 30 * sin(60 * DEG))
// 	// 	// x축으로 1 증가한다면
// 	// 	// 가로로 cos(60), 세로로 sin(60)증가한 곳에 점이 찍힌다
// 	// 	// y축으로 1 증가한다면
// 	//	// 가로로 -sin(60), 세로로 -cos(6)인 곳에 점이 찍힌다.
// 	//unsigned char *data = 
// 	(void)img_addr;

// 	// 점 위치 관리를 위한 자원 할당
// 	coords = malloc(image.width * sizeof(t_coordinate *));
// 	if (!coords)
// 		return (NULL);
// 	while (i < image.width)
// 	{
// 		coords[i] = (t_coordinate *)malloc(image.height * sizeof(t_coordinate));
//         if (!coords[i])
// 			return (NULL);
// 		i++;
// 	}

// 	// 실제로 점 위치 계산
// 	i = 0;
// 	while (i < image.width)
// 	{
// 		j = 0;
// 		while (j < image.height)
// 		{
// 			// 10은 임의의 값으로, 창 사이즈나 파일 크기에 따라서 바뀌는 값으로 수정해야함
// 			coords[i][j].x = x_init + (i - j) * 20 * sin(60 * DEG);
// 			coords[i][j].y = y_init + (i + j) * 20 * cos(60 * DEG); // y값이 증가하면 내려감!, 파싱한 값에 따라서 변하기
// 			if (coords[i][j].x < 0 || coords[i][j].x >= image.width ||
//                 coords[i][j].y < 0 || coords[i][j].y >= image.height)
//             {
//                 // 범위를 벗어난 좌표일 경우 예외 처리
//                 coords[i][j].x = -1;  // 예시: 유효하지 않은 좌표로 설정
//                 coords[i][j].y = -1;
//             }
// 			// if (x >= 0 && x < 500 &&
//             //     y >= 0 && y < 500)
//             // {
// 			// 	data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
// 			// 	*(unsigned int*)data = create_argb(0,0,255,0);
// 			// 	printf("점 하나 출력 (%d, %d)\n", i, j);
// 			// }
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (coords);
// }

//이미지 생성하는 함수
// 이제 이미지 생성만 잘하면 됨!
// void	draw_image(t_image *image, t_coordinate **coords)
// {
// 	int i = 0;
// 	int j = 1;
// 	// 선분 그리는 방법
// 	// 가로 선분 그리기
	
// 	while (coords[i])
// 	{
// 		j = 1;
// 		while (coords[i][j].x != -1) 
// 		{
// 			if (coords[i][j - 1].x != -1 && coords[i][j].x != -1)
// 				bresenham(coords[i][j - 1], coords[i][j], image, create_argb(0,0,255,0));
// 			// data = img_addr + ft_memaddr(coords[i][j].x, coords[i][j].xy, image.size_line, image.bpp);
// 			// *(unsigned int*)data = create_argb(0,0,255,0);
// 			j++;
// 		}
// 		i++;
// 	}
// 	// x = 250;
// 	// y = 250;
// 	// data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
// 	// *(unsigned int*)data = create_argb(0,255,255,0);
// 	// x = 250 + 10 * sin(60 * DEG);
// 	// y = 250 + 10 * cos(60 * DEG);
// 	// data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
// 	// *(unsigned int*)data = create_argb(0,0,255,0);
// 	// x = 250 - 10 * sin(60 * DEG);
// 	// y = 250 + 10 * cos(60 * DEG);
// 	// data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
// 	// *(unsigned int*)data = create_argb(0,0,255,0);
// // 	// 점을 잇는 선분 그리기

// }
