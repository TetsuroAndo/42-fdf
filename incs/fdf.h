/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teando <teando@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 06:16:58 by teando            #+#    #+#             */
/*   Updated: 2024/12/11 16:29:32 by teando           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx/mlx.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define ESC 65307
# define CLOSE_WINDOW 17
# define M_PI 3.14159265358979323846
# define DEFAULT_COLOR 0xFFFFFF

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

/**
 * @brief 3Dマップデータを保持する構造体
 *
 * @details
 * ファイルから読み込まれたマップは、pointsとして2次元配列で格納されます。
 * width, heightはマップの横幅と縦幅を示し、min_z, max_zはマップ中で最小および最大のZ値を保持します。
 * これによりマップ全体の範囲や標高の幅を把握することができます。
 * 	t_point **points; ///< 2次元配列として格納されたマップ上の各点 (x, y, z)
	size_t width;     ///< マップの横方向の点数
	size_t height;    ///< マップの縦方向の点数
	int min_z;        ///< マップ上の最小Z値
	int max_z;        ///< マップ上の最大Z値
 */
typedef struct s_map
{
	t_point		**points;
	size_t		width;
	size_t		height;
	int			min_z;
	int			max_z;
}				t_map;

/**
 * @brief ウィンドウおよび描画に関する情報を保持する構造体
 *
 * @details
 * width, heightはウィンドウサイズ、mlx_ptrはMLXの初期化時に取得するポインタ、
 * win_ptrはウィンドウそのものへのポインタ、img_ptrは描画用イメージのポインタを指します。
 * data_addr、bits_per_pixel、size_line、endianはイメージデータへのアクセスや
 * ピクセル描画に用いられます。
 * 	int width;          ///< ウィンドウの幅
	int height;         ///< ウィンドウの高さ
	void *mlx_ptr;      ///< MLXインスタンスへのポインタ
	void *win_ptr;      ///< ウィンドウを指すポインタ
	void *img_ptr;      ///< 描画用イメージバッファを指すポインタ
	char *data_addr;    ///< イメージバッファ先頭アドレス (ピクセルデータ操作に使用)
	int bits_per_pixel; ///< ピクセルあたりのビット数
	int size_line;      ///< イメージデータ1行あたりのバイト数
	int endian;         ///< エンディアン情報 (0:リトルエンディアン, 1:ビッグエンディアン)
 */
typedef struct s_window
{
	int			width;
	int			height;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_window;

/**
 * @brief 全体の状態を包括的に扱う構造体
 *
 * @details
 * fdf構造体は、ロードされたマップデータ(map)、表示用ウィンドウ情報(window)、
 * および描画のために必要なスケールやシフト情報などをまとめて管理します。
 * projectedは投影後の点群データを保持し、scaleやz_scaleは等角投影時のスケーリング係数、
 * shift_x, shift_yは描画位置補正のための平行移動量を示します。
 *	t_point **projected; // < 投影後の2D座標群 (map.pointsを投影して格納)
	t_map map;           // < 読み込まれた3Dマップデータとその範囲情報
	t_window window;     // < ウィンドウおよび描画イメージに関する情報
	double scale;        // < 2D描画時のスケーリング係数(横幅高さ方向)
	double z_scale;      // < Z軸方向のスケーリング係数(標高の強調用)
	int shift_x;         // < 描画開始位置のX方向シフト量
	int shift_y;         // < 描画開始位置のY方向シフト量
 */
typedef struct s_fdf
{
	t_point		**projected;
	t_map		map;
	t_window	window;
	double		scale;
	double		z_scale;
	int			shift_x;
	int			shift_y;
}				t_fdf;

/*** events ***/
int				key_press(int keycode, t_fdf *fdf);

/*** render ***/
void			draw_map(t_fdf *fdf);
void			draw_line_low(t_fdf *fdf, t_point start, t_point end);
void			draw_line_high(t_fdf *fdf, t_point start, t_point end);
void			project_points(t_fdf *fdf);
void			free_projected(t_fdf *fdf);

/*** set data ***/
int				open_file(char *file_name, t_fdf *fdf);
t_map			read_map(char *file_name, t_fdf *fdf);
t_point			**allocate_points(t_fdf *fdf);
void			parse_map_size(int fd, t_fdf *fdf);
void			parse_line(char *line, size_t y, t_fdf *fdf);
void			adjust_view(t_fdf *fdf);

/*** window ***/
void			put_pixel(t_fdf *fdf, int x, int y, int color);
int				init_window(t_fdf *fdf);
int				close_window(t_fdf *fdf);

/*** srcs ***/
void			ft_error(char *msg, t_fdf *fdf);
void			free_fdf(t_fdf *fdf);

#endif