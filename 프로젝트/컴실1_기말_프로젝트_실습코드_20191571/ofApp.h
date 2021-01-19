#pragma once

#include "ofMain.h"
#include "bst.h"

typedef struct node *node_pointer;//그래프 구현을 위한 node구성
typedef struct node {
	int vertex;//해당 정점 번호 저장
	node_pointer link;//인접 리스트 구현을 위해서
};

typedef struct shortpath *short_pointer;
//기존 숙제에서 bfs로 최단경로를 구할때 사용했던 구조체를 수정하여 사용한다.
typedef struct shortpath {
	int vertex;//정점 저장
	short_pointer left;//역순으로 연결한다.
}shortbfs;//bfs에서 사용


class ofApp : public ofBaseApp{

	public:
	
		char **maze;//.maz파일 저장받은걸 한줄씩 읽어서 maze에 저장
		int level = 0,width=0;//레벨,가로(혹은 세로) 길이. 
		//정사각형 미로들이라 가로/세로의 길이는 같다.
		int state = 0;//4이면 미로출력한다.5면 랭킹시스템
		//state:0(초기화면)1,2,3일때 결과에 따라 출력될 화면을 결정한다.
		void setup();//초기 설정, 사진들을 연다
		void update();//변경된 것들 
		void draw();//화면 출력
		void draw(int x, int y);//캐릭터 이동할때
		void keyPressed(int key);//키버튼이 눌러지면 그에 따른 동작을 수행하도록하는 함수
		void keyReleased(int key);//키버튼이 눌러지면 그에 따른 동작을 수행하도록 함
	
		void drawmaze();//maze출력
		void readFile();//파일 읽기
		void makegraph();//그래프 만들기
		void initgraph();//그래프 초기화
		node_pointer *graph, temp, pNew;//그래프,temp,pNew(동적할당할때 사용)
		void freegraph();//매 레벨마다 그래프+maze를 free해야한다.
		int* visited;//방문여부를 저장할 포인터
		int istarget,isfind,ishint;//target,도착지점을 찾았는지 나타내는 변수,hint를 표시해야하는지 나타내는 변수
		int maze_row = 0;//미로의 가로(세로)
		double play_time = 0;//남은 시간: level마다 달라짐 
		ofImage photo0,photo1, photo2, photo3, target, chara,explain,ranking;
		//ofimage로 이미지를 출력할 것이다.
		void makemaze();//미로를 만든다
		void drawhint();//hint를 출력할수있게 한다.
		void BFS1();//출발~target
		void BFS2();//target~도착
		node_pointer front, rear;//queue(bfs)
		void addq(int);//큐에 데이터 넣기
		int deleteq();//큐에 데이터 삭제
		bool deletestate;//이미 노드를 삭제했는지 판단하는 변수
		void gettime();//남은 시간을 구하는 함수
		double lefttime;//남은 시간을 나타냄
		double lefthinttime;//힌트 남은시간을 나타냄(한번 누를때 1초동안 출력)
		void gettargetxy();//target의 x,y좌표를 무작위로 정하는 함수
		bool ischaramove(int charax, int charay, int key);//캐릭터가 움직일수 있는지 확인하는 함수
		int targetx, targety;//target의 x,y좌표
		int targetindex;//target의 index
		int charax, charay;//캐릭터의 x,y좌표
		
		

		void findname(treePtr);//랭킹에서 이름으로 search하는 함수
		void showranking();//binary search tree으로 랭킹을 구현한다.
		void inorder(treePtr);//순서대로 출력하려면 중위순회하면 된다.
		int printnum,rankstate;//printnum:지금까지 몇개 출력했는지,
		//rankstate:rank에서 전체출력/범위 출력/이름검색/삭제 인지 표시하는 변수
		int x, y;//rank를 x부터 y까지 출력한다고 할 때 입력받는 것
		char username[50];//게임이 끝나고 user의 이름을 입력받는다.
		
	
		void rangeSearch(treePtr, int, int);//해당 범위만큼 출력
	
		int deletenum;//지워야하는 순위

		void mazevariable();//미로 레벨이 증가할때 미로 관련 변수들을 초기화하는 함수
		int totalscore;//총점수
		void getresult();//결과에 따라 state를 변경하는 함수
		void isreach();//target,도착지점에 닿았는지 확인하는 함수
		void freebfs1();//각 게임이 끝날때마다 bfs에서 동적할당했던 걸 해제해야한다.
		void freebfs2();//bfs2에서 동적할당 했던것들을 해제한다.
		void drawbfs();//bfs1,2로 구한걸 출력한다
		short_pointer *searchshort;//bfs1에서 최단경로를 구할때 쓰인다. 
		short_pointer *searchshort2;//bfs2에서 최단경로를 구할때 쓰인다.
};
