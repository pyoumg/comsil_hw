#ifndef __waterObj__
#define __waterObj__
class waterObj {//선분으로 표현할 예정

public: int *x1, *y1, numx, numy;// 선분의 끝 점 좌표
		int flag;
		waterObj(int max); //맨 처음에 생성 
		void water_init(int x, int y);
		~waterObj();
		void calculate_water(int  *l_x1, int*l_x2, int*l_y1, int*l_y2, int index_line,int height);//
		int water_index();

};
#endif