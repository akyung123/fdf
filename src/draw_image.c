/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 04:50:51 by akkim             #+#    #+#             */
/*   Updated: 2026/01/01 15:56:29 by akkim            ###   ########.fr       */
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

//이미지 생성하는 함수
// 이제 이미지 생성만 잘하면 됨!
void	draw_image(unsigned char *img_addr, t_image image)
{
	int i = 0;
	int j = 0;
	int x;
	int y;
	int x_init = image.width / 2;
	int y_init = image.height / 2;
// 	// 주어진 한칸 위치 계산해서 점 찍기
// 	// 첫 값을 찍고(0, 0) 
//	// (0, 1)이면 (30 * cos(60 * DEG), - 30 * sin(60 * DEG))
//	// (0, 2)이면 (2 * 30 * cos(60 * DEG), 2 * 30 * sin(60 * DEG))
// 	// x축으로 1 증가한다면
// 	// 가로로 cos(60), 세로로 sin(60)증가한 곳에 점이 찍힌다
// 	// y축으로 1 증가한다면
//	// 가로로 -sin(60), 세로로 -cos(6)인 곳에 점이 찍힌다.
	unsigned char *data = img_addr;
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			// 10은 임의의 값으로, 창 사이즈나 파일 크기에 따라서 바뀌는 값으로 수정해야함
			x = x_init + (i - j) * 20 * sin(60 * DEG);
			y = y_init + (i + j) * 20 * cos(60 * DEG); // y값이 증가하면 내려감!, 파싱한 값에 따라서 변하기
			if (x >= 0 && x < 500 &&
                y >= 0 && y < 500)
            {
				data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
				*(unsigned int*)data = create_argb(0,0,255,0);
			}
			j += 1;
		}
		i += 1;
	}
	// x = 250;
	// y = 250;
	// data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
	// *(unsigned int*)data = create_argb(0,255,255,0);
	// x = 250 + 10 * sin(60 * DEG);
	// y = 250 + 10 * cos(60 * DEG);
	// data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
	// *(unsigned int*)data = create_argb(0,0,255,0);
	// x = 250 - 10 * sin(60 * DEG);
	// y = 250 + 10 * cos(60 * DEG);
	// data = img_addr + ft_memaddr(x, y, image.size_line, image.bpp);
	// *(unsigned int*)data = create_argb(0,0,255,0);
// 	// 점을 잇는 선분 그리기

}
