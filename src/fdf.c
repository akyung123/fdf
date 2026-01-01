/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 03:47:44 by akkim             #+#    #+#             */
/*   Updated: 2026/01/01 15:55:22 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stdio.h"


int	main(int argc, char **argv)
{
	t_vars param;
	t_image image;
	int fd;
	
	if (argc != 2)
		return (0);
	// 열리지 않는 파일 혹은 권한 없을 때 종료
	// .fdf 파일인지도 검사해야함!
	// 파일 타입 검사, 함수 구현해야함
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}

	// 파일 검사하기
	// 값을 파싱하기
	init_file(&image, argv[1]);
	// 창 크기 계산하기 
	// 

	param.mlx_ptr = mlx_init();

	// 새로운 윈도우 생성
	param.win_ptr = mlx_new_window(param.mlx_ptr, 1000, 1000, "new!");

	// int color = mlx_get_color_value(param.mlx_ptr, create_argb(0,255,0, 0));
	// mlx_pixel_put (param.mlx_ptr, param.win_ptr, 150, 150, color);

	void *img_ptr = mlx_new_image(param.mlx_ptr, image.width, image.height);
	unsigned char *img_addr = (unsigned char *)mlx_get_data_addr(img_ptr, &image.bpp, &image.size_line, &image.endian);

	
    // 이미지에 빨간색 사각형 그리기
	draw_image(img_addr, image);
	mlx_put_image_to_window(param.mlx_ptr, param.win_ptr, img_ptr, 100, 100);

	mlx_mouse_hook(param.win_ptr, mouse_event, &param);
	mlx_key_hook(param.win_ptr, key_event, &param);
	mlx_expose_hook(param.win_ptr,expose_event, &param);        // expose 이벤트
    mlx_hook(param.win_ptr, 17, 0, close_window, &param);       // X 버튼
	// 닫히는 함수 간단 구현
	// esc키 혹은 x 버튼 클릭 시, 종료
	
	// 무한 루프 생성, 이벤트 기다리는 중, 창 닫히는 거 방지.
	mlx_loop(param.mlx_ptr);
}