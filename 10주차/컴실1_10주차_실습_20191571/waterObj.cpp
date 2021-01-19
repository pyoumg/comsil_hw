#include "waterObj.h"
#include <iostream>
#include <cstdlib>
using namespace std;

waterObj::waterObj(int max) {
	x1 = new int[max];
	y1 = new int[max];
	numx = 0, numy = 0;
	flag = -2;
}//맨 첨에 생성 

waterObj::~waterObj() {
	delete[] x1;
	delete[] y1;
}
void waterObj::water_init(int x, int y) {
	x1[0] = x, y1[0] = y;
	numx = 0, numy = 0;
	flag = -2;
}
void waterObj::calculate_water(int  *l_x1, int*l_x2, int*l_y1, int*l_y2, int index_line,int height) {
	x1[++numx] = x1[numx - 1], y1[++numy] = height;//x1은 그대로임(밑으로 떨어지는거)
	int temp = 0;
	int sign = -1;
	
	for (int i = 0; i < index_line; i++) {
		if (l_x1[i] <= x1[numx - 1] && l_x2[i] >= x1[numx - 1]) {//x좌표 기준 점이 내려갈 수 있음
		
			temp = ((l_y2[i] - l_y1[i])*(x1[numx - 1]) + (l_x2[i] - l_x1[i])*(l_y1[i]) - (l_y2[i] - l_y1[i])*l_x1[i])/ (l_x2[i] - l_x1[i]);
			
			if (temp >= y1[numy - 1] && temp <= y1[numy]&&i!=flag)
			{
				y1[numy] = temp;
				sign = i;
			}
				
		}
	}

	if (sign==-1) {
		y1[numy] = height;//화면 끝까지 떨어짐
	}
	else {
		if (l_y1[sign] > l_y2[sign]) {// 왼쪽이 더 낮으면 
			y1[++numy] = l_y1[sign];
			x1[++numx] = l_x1[sign];
		}
		else {
			y1[++numy] = l_y2[sign];
			x1[++numx] = l_x2[sign];
		}
	}
	
	flag = sign;
}

int waterObj::water_index() {
	return numx;
}
