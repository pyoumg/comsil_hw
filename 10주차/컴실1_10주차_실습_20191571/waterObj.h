#ifndef __waterObj__
#define __waterObj__
class waterObj {//�������� ǥ���� ����

public: int *x1, *y1, numx, numy;// ������ �� �� ��ǥ
		int flag;
		waterObj(int max); //�� ó���� ���� 
		void water_init(int x, int y);
		~waterObj();
		void calculate_water(int  *l_x1, int*l_x2, int*l_y1, int*l_y2, int index_line,int height);//
		int water_index();

};
#endif