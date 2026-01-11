/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkim <akkim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 04:26:02 by akkim             #+#    #+#             */
/*   Updated: 2026/01/10 04:26:04 by akkim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_default_color(int z)
{
	// double	percentage;

	// 맵의 최대/최소 높이를 파싱 단계에서 미리 구해두면 좋습니다.
	// 여기선 예시로 0~20 범위를 기준으로 잡았습니다.
	if (z == 0)
		return (0xFFFFFF); // 평지는 흰색
	if (z > 0)
		return (0xAF11FF); // 높은 곳은 보라/핑크 계열
	return (0x42E1FF);     // 마이너스 높이는 하늘색 계열
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(t_point current, t_point p1, t_point p2, int p1_color, int p2_color)
{
	int		r;
	int		g;
	int		b;
	double	percentage;

	if (p1_color == p2_color)
		return (p1_color);
	// 선 전체 길이 대비 현재 점의 위치 비율 계산
	if (abs(p2.x - p1.x) > abs(p2.y - p1.y))
		percentage = (double)(current.x - p1.x) / (p2.x - p1.x);
	else
		percentage = (double)(current.y - p1.y) / (p2.y - p1.y);

	r = get_light((p1_color >> 16) & 0xFF, (p2_color >> 16) & 0xFF, percentage);
	g = get_light((p1_color >> 8) & 0xFF, (p2_color >> 8) & 0xFF, percentage);
	b = get_light(p1_color & 0xFF, p2_color & 0xFF, percentage);

	return ((r << 16) | (g << 8) | b);
}
