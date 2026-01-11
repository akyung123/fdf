/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 03:47:44 by akkim             #+#    #+#             */
/*   Updated: 2026/01/12 01:23:03 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_filename(const char *filename)
{
	const char	*dot;

	if (!filename)
		return (0);
	dot = ft_strrchr((char *)filename, '.');
	if (!dot || dot == filename)
		return (0);
	if (ft_strncmp(dot, ".fdf", 5) == 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf *fdf;

	int fd;

	if (argc != 2)
		return (0);
	// 열리지 않는 파일 혹은 권한 없을 때 종료
	// .fdf 파일인지도 검사해야함!
	// 파일 타입 검사, 함수 구현해야함
	if (!check_filename(argv[1]))
	{
		ft_putstr_fd("Error: Invalid file extension. It must be '.fdf'\n", 2);
		exit(1);
	}
	fd = open(argv[1], O_RDONLY);
	close(fd); /* open() 성공 여부만 확인하고 바로 닫음 */
	if (fd == -1)
	{
		perror(argv[1]);
		exit(1);
	}
	fdf = (t_fdf *)malloc(sizeof(t_fdf));
	if (!fdf)
		return (1); // null 방어
	read_map(argv[1], fdf); // 파일 읽긴
	init_file(fdf); // fdf 세팅
	
	// 파일 검사하기
	// 값을 파싱하기
	// 창 크기 계산하기 

	// 데이터 만들기
	// coords = ft_dot(image.addr, image);
    // 이미지 그리기
	draw(fdf);
	
	// mlx_put_image_to_window(param.mlx_ptr, param.win_ptr, img_ptr, 100, 100);
	// mlx_mouse_hook(param.win_ptr, mouse_event, &param);
	// 마지막 매개변수로 fdf가 들어가도 되나?
	mlx_key_hook(fdf->win_ptr, key_event, fdf);
	mlx_expose_hook(fdf->win_ptr,expose_event, fdf);     // expose 이벤트
    mlx_hook(fdf->win_ptr, 17, 0, close_window, fdf);      // X 버튼
	// 닫히는 함수 간단 구현
	// esc키 혹은 x 버튼 클릭 시, 종료
	
	// 무한 루프 생성, 이벤트 기다리는 중, 창 닫히는 거 방지.
	mlx_loop(fdf->mlx_ptr);
	return (0);
}