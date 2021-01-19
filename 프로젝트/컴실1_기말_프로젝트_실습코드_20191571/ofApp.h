#pragma once

#include "ofMain.h"
#include "bst.h"

typedef struct node *node_pointer;//�׷��� ������ ���� node����
typedef struct node {
	int vertex;//�ش� ���� ��ȣ ����
	node_pointer link;//���� ����Ʈ ������ ���ؼ�
};

typedef struct shortpath *short_pointer;
//���� �������� bfs�� �ִܰ�θ� ���Ҷ� ����ߴ� ����ü�� �����Ͽ� ����Ѵ�.
typedef struct shortpath {
	int vertex;//���� ����
	short_pointer left;//�������� �����Ѵ�.
}shortbfs;//bfs���� ���


class ofApp : public ofBaseApp{

	public:
	
		char **maze;//.maz���� ��������� ���پ� �о maze�� ����
		int level = 0,width=0;//����,����(Ȥ�� ����) ����. 
		//���簢�� �̷ε��̶� ����/������ ���̴� ����.
		int state = 0;//4�̸� �̷�����Ѵ�.5�� ��ŷ�ý���
		//state:0(�ʱ�ȭ��)1,2,3�϶� ����� ���� ��µ� ȭ���� �����Ѵ�.
		void setup();//�ʱ� ����, �������� ����
		void update();//����� �͵� 
		void draw();//ȭ�� ���
		void draw(int x, int y);//ĳ���� �̵��Ҷ�
		void keyPressed(int key);//Ű��ư�� �������� �׿� ���� ������ �����ϵ����ϴ� �Լ�
		void keyReleased(int key);//Ű��ư�� �������� �׿� ���� ������ �����ϵ��� ��
	
		void drawmaze();//maze���
		void readFile();//���� �б�
		void makegraph();//�׷��� �����
		void initgraph();//�׷��� �ʱ�ȭ
		node_pointer *graph, temp, pNew;//�׷���,temp,pNew(�����Ҵ��Ҷ� ���)
		void freegraph();//�� �������� �׷���+maze�� free�ؾ��Ѵ�.
		int* visited;//�湮���θ� ������ ������
		int istarget,isfind,ishint;//target,���������� ã�Ҵ��� ��Ÿ���� ����,hint�� ǥ���ؾ��ϴ��� ��Ÿ���� ����
		int maze_row = 0;//�̷��� ����(����)
		double play_time = 0;//���� �ð�: level���� �޶��� 
		ofImage photo0,photo1, photo2, photo3, target, chara,explain,ranking;
		//ofimage�� �̹����� ����� ���̴�.
		void makemaze();//�̷θ� �����
		void drawhint();//hint�� ����Ҽ��ְ� �Ѵ�.
		void BFS1();//���~target
		void BFS2();//target~����
		node_pointer front, rear;//queue(bfs)
		void addq(int);//ť�� ������ �ֱ�
		int deleteq();//ť�� ������ ����
		bool deletestate;//�̹� ��带 �����ߴ��� �Ǵ��ϴ� ����
		void gettime();//���� �ð��� ���ϴ� �Լ�
		double lefttime;//���� �ð��� ��Ÿ��
		double lefthinttime;//��Ʈ �����ð��� ��Ÿ��(�ѹ� ������ 1�ʵ��� ���)
		void gettargetxy();//target�� x,y��ǥ�� �������� ���ϴ� �Լ�
		bool ischaramove(int charax, int charay, int key);//ĳ���Ͱ� �����ϼ� �ִ��� Ȯ���ϴ� �Լ�
		int targetx, targety;//target�� x,y��ǥ
		int targetindex;//target�� index
		int charax, charay;//ĳ������ x,y��ǥ
		
		

		void findname(treePtr);//��ŷ���� �̸����� search�ϴ� �Լ�
		void showranking();//binary search tree���� ��ŷ�� �����Ѵ�.
		void inorder(treePtr);//������� ����Ϸ��� ������ȸ�ϸ� �ȴ�.
		int printnum,rankstate;//printnum:���ݱ��� � ����ߴ���,
		//rankstate:rank���� ��ü���/���� ���/�̸��˻�/���� ���� ǥ���ϴ� ����
		int x, y;//rank�� x���� y���� ����Ѵٰ� �� �� �Է¹޴� ��
		char username[50];//������ ������ user�� �̸��� �Է¹޴´�.
		
	
		void rangeSearch(treePtr, int, int);//�ش� ������ŭ ���
	
		int deletenum;//�������ϴ� ����

		void mazevariable();//�̷� ������ �����Ҷ� �̷� ���� �������� �ʱ�ȭ�ϴ� �Լ�
		int totalscore;//������
		void getresult();//����� ���� state�� �����ϴ� �Լ�
		void isreach();//target,���������� ��Ҵ��� Ȯ���ϴ� �Լ�
		void freebfs1();//�� ������ ���������� bfs���� �����Ҵ��ߴ� �� �����ؾ��Ѵ�.
		void freebfs2();//bfs2���� �����Ҵ� �ߴ��͵��� �����Ѵ�.
		void drawbfs();//bfs1,2�� ���Ѱ� ����Ѵ�
		short_pointer *searchshort;//bfs1���� �ִܰ�θ� ���Ҷ� ���δ�. 
		short_pointer *searchshort2;//bfs2���� �ִܰ�θ� ���Ҷ� ���δ�.
};
