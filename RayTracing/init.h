#ifndef _INIT_H_
#define _INIT_H_

#include "stdlib.h"

/*视窗像素*/
#define PIXEL_W	1000
#define PIXEL_H	1000

/*视窗尺寸*/
#define VIEW_W 20.0f
#define VIEW_H 20.0f

/*图片像素*/
#define JPG_PIXEL_W	500
#define JPG_PIXEL_H	500

#define DEFAULTR 0.05
#define DEFAULTS 0.2

#define DEPTH 4 //光线递归深度

#define INFINITY 1000000.0f //无穷大
#define SMALL 0.0001f//无穷小

#define MAX(a, b) (((a) > (b)) ? (a) : (b)) /*取最大值*/
#define DOT(A, B) (A.x*B.x+A.y*B.y+A.z*B.z) /*向量点乘*/

/*相交类型，INTERSECTED_IN相交在内部，MISS未相交，INTERSECTED相交在外部*/
enum INTERSECTION_TYPE { INSEC_IN = -1, MISS = 0, INTERSECTED = 1 };

#endif