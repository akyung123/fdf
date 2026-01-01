/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 04:04:44 by akkim             #+#    #+#             */
/*   Updated: 2026/01/01 04:40:20 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fdf.h"

int mouse_event(int button, int x, int y, void *param)
{
    (void)param; // 사용하지 않으면 경고 방지
    printf("Mouse button %d clicked at (%d, %d)\n", button, x, y);
    return 0;
}

int key_event(int keycode, void *param)
{
    t_vars *vars = (t_vars *)param;

    if (keycode == 65307) // ESC 키 (X11 기준)
    {
        printf("ESC pressed, exiting...\n");
        mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
        exit(0);
    }
    printf("key code %d clicked.\n", keycode);
    return 0;
}

int expose_event(void *param)
{
    (void)param; // 사용하지 않으면 경고 방지
    printf("Window needs to be redrawn (expose event triggered)\n");
    return 0;
}

// window 창 관리 함수
// 창을 닫는 함수
// void  mouse_close_window(void *mlx_ptr,void *win_ptr)
// {
// 	if ()
// 		mlx_destroy_window(void *mlx_ptr,void *win_ptr);
// }

// 윈도우 X 버튼 (DestroyNotify) 이벤트
int close_window(void *param)
{
    t_vars *vars = (t_vars *)param;

    printf("X button clicked, exiting...\n");
    mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
    exit(0);
    return 0;
}