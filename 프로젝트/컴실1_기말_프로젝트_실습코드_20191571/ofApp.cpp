#include "ofApp.h"
bst bstree(0);//객체 생성
//--------------------------------------------------------------
void ofApp::setup(){//초기값 설정
	ofSetFrameRate(15);//초당 15프레임
	ofBackground(255, 255, 255);//white
	state = 0;//값 초기화
	totalscore = 0;//총점수
	istarget = 0,ishint=0;//target을 찾았는지, 힌트버튼을 눌렀는지
	photo0.load("img_0.png");//초기화면
	photo1.load("img_1.png");//target==1,시간내에 들어옴
	photo2.load("img_2.png");//target==0.시간내에 들어옴
	photo3.load("img_3.png");//시간내에 못들어옴
	target.load("target.png");//콜라
	explain.load("game_explain.png");//게임설명
	ranking.load("ranking.png");//랭킹
	chara.load("character.png");//캐릭터 이미지 로드
	charax = 100, charay = 50;//캐릭터 시작점

	rankstate = 0;//랭킹시스템에서 초기화면(전체출력)
	
}

//--------------------------------------------------------------
void ofApp::update() {
	if (state == 4) {//미로
		gettime();//남은시간구하기

		if (lefttime == 0)//시간이 다되면
			getresult();//결과를 구하기
		isreach();//특정 지점에 도달했는지 구하기
		if (ishint == 1)//힌트를 표시해야하면
			drawhint();//1초 지났는지 아닌지 확인
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (state==0) {//초기화면이면
		
		photo0.draw(0, 0);//초기화면 배경을 출력
		
		ofSetColor(0);//검정
		
		ofDrawBitmapString("comsil project",590,350);
		ofDrawBitmapString("20191571 Kim Seyoung", 570, 400);
		ofDrawBitmapString("press space to start game", 550, 550);
		ofDrawBitmapString("press 'r' to see ranks", 558, 575);//'r'이나 'R'누르면 랭킹시스템으로 넘어감
		ofDrawBitmapString("press 'q' to quit", 575, 595);//'q'나'Q'누르면 종료
		ofSetColor(255);//기본값
	}
	else if (state == 4) {//미로는 이미 만든 상태
		ofSetColor(0);//검정
		
		ofDrawBitmapString("level: " +ofToString(level + 1), 200+(width-1)*20, 100);//레벨 출력
		ofDrawBitmapString("time: " + ofToString(lefttime), 200 + (width - 1) * 20, 150);//시간 출력
		ofDrawBitmapString("'h': hint ", 200 + (width - 1) * 20, 200);//h누르면 힌트 표시됨
		ofDrawRectangle((width - 1) * 20 + 400, 0, 1250, 780);//화면 오른쪽에 검은색으로 네모 출력
		ofSetColor(0, 255, 0);//초록
		ofDrawCircle((width - 2) * 20 + 100, (width - 2) * 20 + 50, 15);//도착지점 초록색으로 그리기
		ofSetColor(0);//검정
		drawmaze();//미로그리기
		ofSetColor(255);//기본값
		draw(charax, charay);//캐릭터그리기
		if(istarget==0)//target을 찾지 않으면
			target.draw(targetx, targety);//닿으면 없어지기
		if (ishint == 1) {//힌트를 그려야하면
			drawbfs();//힌트를 그리기
		}
	
	}
	else if (state == 5) {//게임설명
		explain.draw(0, 0);//설명화면 출력
		ofSetColor(0);//검정
		ofDrawBitmapString("press space to start game", 570, 730);//스페이스바 누르면 넘어감
		ofSetColor(255);//기본값
	}
	else if (state == 1) {//target도 찾고 시간내에 도착함
		photo1.draw(0, 0);//화면 출력
		ofSetColor(0);//검정
		ofDrawBitmapString("press space", 570, 740);//스페이스바 누르면 넘어감
		ofSetColor(255);//기본값
	}
	else if (state == 2) {//target은 못찾고 시간내에 도착함
		photo2.draw(0, 0);//화면 출력
		ofSetColor(0);//검정
		ofDrawBitmapString("press space", 570, 740);//스페이스바
		ofSetColor(255);//기본값
	}
	else if (state == 3) {//시간내에 도착못함
		photo3.draw(0, 0);//화면출력
		ofSetColor(0);//검정
		ofDrawBitmapString("press space", 570, 740);//스페이스바
		ofSetColor(255);//기본값
	}
	else if (state == 6) {//랭킹시스템
		ranking.draw(0, 0);//랭킹배경 출력
		ofSetColor(0);//검정
		showranking();//랭킹 표시
		ofSetColor(255);//기본값
	}

}
void ofApp::draw(int x, int y) {//캐릭터 이동
	chara.draw(x, y);//캐릭터 그리기
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){//키를 누르면
	if (key == 'r' || key == 'R') {//r누르면 랭킹 봄
		if (state == 0) {//초기화면에서만 눌러야 랭킹 봄
			ofClear(255, 255, 255);//화면 지우기
			state = 6;//state를 랭킹보는것으로 변경
		}
	}
	if (key == ' ') {//스페이스
		if (state == 0)//초기화면
		{
			ofClear(255, 255, 255);//화면지우기
			state=5;//게임설명
		}
		else if (state == 5) {//게임설명에서 스페이스 누르면
			ofClear(255, 255, 255);//화면 지우기
			state = 4, level = 0;//레벨은 0(시작값),미로화면

			makemaze();//미로 만들기
			mazevariable();//변수들초기화
			BFS1();//시작~target
			BFS2();//target~도착
		}
		else if (state >= 1 && state <= 3) {//결과화면
			ofClear(255, 255, 255);//화면지우기
			freebfs1();//bfs1관련 동적할당 했던것 해제
			freebfs2();//bfs2관련 동적할당했던 것 해제 (미로를 새롭게 그려야함)
			if (level < 2)//또 미로 만들어야하면
			{
				level++;//레벨1증가
				state = 4;//미로화면
				
				makemaze();//미로만들기
				mazevariable();//변수들초기화
				BFS1();//시작~target
				BFS2();//target~끝
			}
			else {//이제 게임 끝이면
				printf("score: %d\n", totalscore);//총점수 출력
				printf("your name: ");//이름 입력받기
				bstree.totaldata++;//총 노드수 늘어남
				scanf("%s", username);//이름을 입력받음
				bstree.insert(&(bstree.tree),totalscore, username);//bst에 삽입
				level = 0;//레벨 초기화
				state = 0;//초기화면 이동
			}

		}
	}

	
	if (key == '1') {//1누르면 범위만큼 출력함
		if (state == 6&&bstree.tree!=NULL) {//랭킹화면이고 tree가 비어있지 않을때
			rankstate = 1;//rankstate변경
			printf("X: ");//시작 범위 받기
			scanf("%d", &x);//x에 저장
			printf("Y: ");//끝 범위 받기
			scanf("%d", &y);//y에 저장
			
		}
	}
	if (key == '2') {//이름으로 검색하기
		if (state == 6 && bstree.tree != NULL) {//랭킹화면이고 트리가 비어있지 않음
			printf("Input the name: ");//이름 입력
			scanf("%s", username);//입력받아서 username에 저장
			rankstate = 2;//rankstate변경

		}
	}
	if (key == '3')//삭제
	{
		if (state == 6 && bstree.tree != NULL) {//랭킹화면이고 트리가 비어있지 않음
			printf("Input the rank: ");//삭제할 순위 
			scanf("%d", &deletenum);//deletenum으로 입력받기
			rankstate = 3;//rankstate변경
			deletestate = false;//deletestate초기화
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {//키를 눌렀다 '떼면'
	
	
	if (state==4) {//게임화면일때
		//캐릭터를 움직인다
		if (key == OF_KEY_RIGHT) {//오른키 누름
			if (ischaramove(charax, charay, key) == true) {//캐릭터가 움직일 수 있음
				charax += 40;//x좌표 40증가
			}
		}
		
		if(key==OF_KEY_LEFT){//왼쪽 키 눌렀다 뗌
			if (ischaramove(charax, charay, key) == true) {//캐릭터가 움직일 수 있음
					charax -= 40;//x좌표 40감소
				
			}
		}
		if (key == OF_KEY_DOWN) {//아래키
			if (ischaramove(charax, charay, key) == true) {//캐릭터가 움직일 수 있음
				charay += 40;//y좌표 40증가(아래로 내려감)
				
			}
		}
		if (key == OF_KEY_UP) {//위
			if (ischaramove(charax, charay, key) == true) {//캐릭터가 움직일 수 있음
				charay -= 40;//y좌표 40감소(위로 올라감
					
			}
		}
		if (key == 'h' || key == 'H') {//힌트버튼 누름
			lefthinttime = clock();//현재 시간을 저장
			ishint = 1;//힌트를 얻는다고 변경
		}
		
	}

	if (key == 'q' || key == 'Q') {//q키를 누르면 
		if (state == 6) {//랭킹화면이면
			state = 0;//초기화면으로 이동
			rankstate = 0;//rankstate초기화
		}
		else if (state == 0) {//초기화면이면
			_Exit(0);//프로그램 종료
		}
	}
}

//--------------------------------------------------------------

void ofApp::drawmaze() {
	ofSetColor(100);//검정
	ofSetLineWidth(5);//선굵기
	//y축 50,x축 100씩 여유공간 있음
	ofDrawLine(100, 50, (width - 1) * 20+100, 50);//가로1
	ofDrawLine(100, 50, 100, (width - 1) * 20+50);//세로1
	ofDrawLine(100, (width - 1) * 20+50, (width - 1) * 20+100, (width - 1) * 20+50);//가로2
	ofDrawLine((width - 1) * 20+100, 50, (width - 1) * 20+100, (width - 1) * 20+50);//세로2,테두리 그리기
	for (int i = 1; i < width - 1; i++) {//테두리 제외하고 그리기
		for (int j = 1; j < width - 1; j++) {//테두리 제외하고 그리기
			if (maze[i][j] == '|') {//|면 세로선 출력

				ofDrawLine(j * 20+100, (i - 1) * 20+50, j * 20+100, (i + 1) * 20+50);//세로선 출력
			}
			else if (maze[i][j] == '-') {//-면 가로선 출력
				ofDrawLine((j - 1) * 20+100, i * 20+50, (j + 1) * 20+100, i * 20+50);//가로선 출력
			}

		}
	}
	ofSetColor(255);//기본값

}

//--------------------------------------------------------------

void ofApp::readFile() {//파일을 읽는 함수
	char openstr[12] = "maze0_0.maz";//str의 기본형

	int temp = rand() % 2;//랜덤으로 둘중 하나 고르도록
	openstr[4] = level + '0';//level 숫자
	openstr[6] = temp + '0';//무작위로 2개중에 1개를 고른다
	
	if (level == 0) {//미로의 레벨로 가로,세로를 알 수 있으므로 이에 맞게 동적할당 한다
		width = 21;//21
	}
	else if (level == 1) {//level이 1이면
		width = 31;//width를 설정한다.
	}
	else {//level:2
		width = 35;//width를 설정한다.
	}
	maze = (char**)malloc(sizeof(char*) * (width + 1));//maze동적할당
	for (int i = 0; i < width + 1; i++) {//반복문 이용
		maze[i] = (char*)malloc(sizeof(char)*(width + 1));//2차원 배열이니까 maze[i]도 동적할당해야한다
	}
	
	FILE* fp = NULL;//파일
	char tempstr[50];//임시로 한줄씩 저장할 배열
	if (0 == fopen_s(&fp,ofToDataPath(openstr).c_str(), "r")) {//파일이 열리면 
	for(int i=0;i<width;i++){//width만큼(미로의 가로세로를 이미 알고있는것을 전제)
		fgets(tempstr, 50, fp);//한줄받기
		for (int j = 0; j < width; j++)//width만큼만
		{
			maze[i][j] = tempstr[j];//maze에 옮기기
		}
	}
	
	}
	fclose(fp);//파일 닫기
}

//--------------------------------------------------------------
void ofApp::initgraph() {//그래프 초기화
	for (int i = 0; i < maze_row*maze_row; i++) {//인덱스는 미로의 세로*가로 만큼 있다
		graph[i] = (node*)malloc(sizeof(node));//동적할당
		graph[i]->vertex = i;//인덱스
		graph[i]->link = NULL;//초기값
		visited[i] = 0;//아직 방문하지 않음
	}
}
//--------------------------------------------------------------
void ofApp::makegraph() {//char** maze로 저장해둔 것을 그래프로 나타낸다.
	maze_row = (width - 1) / 2;//미로의 가로(세로)
	graph = (node_pointer*)malloc(sizeof(node_pointer)*maze_row*maze_row);//동적할당
	visited = (int*)malloc(sizeof(int)*maze_row*maze_row);//방문 동적할당
	initgraph();//그래프 초기화
	for (int i = 1; i < width - 1; i++) {//width-1나 0이면 테두리이기 때문에 읽지 않아도 됨
		for (int j = 1; j < width - 1; j++) {//width-1이나 0이면 테두리이기 때문에 읽지 않아도 됨
			if (i % 2 == 1 && j % 2 == 0 && maze[i][j] == ' ') {//칸들이 연결되어있으면
				temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2)];//그래프 인덱스를 찾음
				while (temp->link != NULL)
					temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
				pNew = (node_pointer)malloc(sizeof(node));//동적할당
				temp->link = pNew;//연결
				pNew->link = NULL;//마지막 노드의 link는 NULL
				pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2 + 1);//왼쪽에 있는 노드에 오른쪽에 있는 노드를 연결
				//그 오른쪽에 있는 노드도 연결해야함
				temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2) + 1];//인덱스 찾기
				while (temp->link != NULL)
					temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
				pNew = (node_pointer)malloc(sizeof(node));//동적할당
				temp->link = pNew;//그래프에 연결
				pNew->link = NULL;//마지막 노드의 link는 NULL
				pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2);//오른쪽에 있는 노드에 왼쪽에 있는 노드를 연결

			}
			else if (i % 2 == 0 && j % 2 == 1 && maze[i][j] == ' ') {//위아래로 연결되어있음
				temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2)];//인덱스찾기
				while (temp->link != NULL)
					temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
				pNew = (node_pointer)malloc(sizeof(node));//동적할당한다
				temp->link = pNew;//인접리스트에 연결
				pNew->link = NULL;//마지막 노드의 link는 NULL
				pNew->vertex = ((i - 1) / 2 + 1)*maze_row + ((j - 1) / 2);//위쪽에 있는 노드에 아래쪽에 있는 노드를 연결
				//그 오른쪽에 있는 노드도 연결해야함
				temp = graph[((i - 1) / 2 + 1)*maze_row + ((j - 1) / 2)];//인덱스 찾기
				while (temp->link != NULL)
					temp = temp->link;//인접리스트에 연결된 마지막 노드를 찾는다
				pNew = (node_pointer)malloc(sizeof(node));//동적할당
				temp->link = pNew;//인접리스트에 연결
				pNew->link = NULL;//마지막 노드의 link는 NULL
				pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2);//아래쪽에 있는 노드에 위쪽에 있는 노드를 연결

			}
		}
	}


}
//--------------------------------------------------------------
void ofApp::freegraph() {//그래프가 레벨마다 새로 그려지기 때문에 동적할당 해제가 필요하다
	node_pointer pPre;
	for (int i = 0; i < maze_row*maze_row; i++) {//미로의 가로*세로만큼 동적할당 했었음
		temp = graph[i];//그래프
		while (temp != NULL) {
			pPre = temp->link;//링크를 타고
			free(temp);//계속 동적할당을 해제함
			temp = pPre;//링크를 타고 감
		}
	}
	for (int i = 0; i < width + 1;i++) {
		free(maze[i]);//입력받았던 maze도 해제
	}
	free(maze);//이차원 배열이기 때문에 나눠서 해제해야한다.
}
//--------------------------------------------------------------
void ofApp::makemaze() {//미로를 플레이할때 처음 실행해야할 함수들을 호출함
	readFile();//파일 읽어서 maze에 저장
	makegraph();//그래프 만들기: 
    drawmaze();//maze로 화면에 출력
	
}
//--------------------------------------------------------------
void ofApp :: gettargetxy() {//targetx,targety의 값을 정하는 함수
	maze_row = (width - 1) / 2;//미로의 가로(세로)
	targetx = rand() % maze_row;//무작위로 정함
	targety = rand() % maze_row;//무작위로 정함
	while ((targetx == maze_row - 1 && targety == maze_row - 1)||(targetx==0&&targety==0) ){
		targetx = rand() % maze_row;//출발점이나 도착점이면 의미가 없으므로 다시 정함
		targety = rand() % maze_row;//다시정함
	}
	targetindex = targety * maze_row + targetx;//target의 index
	targetx = targetx * 40 + 100;//실제 출력되는 x좌표
	targety = targety * 40 + 50;//실제 출력되는 y좌표
}
//--------------------------------------------------------------
void ofApp::gettime() {//시간을 구하는 함수
	//level이 0:20,1:35,2:50초의 제한시간을 부여한다
	double limittime = level * 15 + 20;//제한시간
	lefttime = limittime - (clock() - play_time) / CLOCKS_PER_SEC;//남은 시간을 구함
	if (lefttime <= 0)//0보다 작으면
		lefttime = 0;//0으로 함
	return;

}
//--------------------------------------------------------------
bool ofApp::ischaramove(int charax, int charay, int key) {//캐릭터가 움직일 수 있는지
	int charaindex = (charax-100)/40+(charay-50)/40*(width-1)/2;//캐릭터의 위치에 해당하는 인덱스
	temp = graph[charaindex];//그래프에서 인덱스에 해당하는 것을 찾는다
	if (key == OF_KEY_RIGHT) {//오른쪽
		if (charax < (width - 3) * 20 + 100) {//우선 움직일 수 있음
			
			while (temp != NULL) {
				if (temp->vertex == charaindex + 1)//방들이 연결되어있다
					break;//반복문 탈출
				temp = temp->link;//아니면 다음 링크를 타고 찾는다
				
			}
			if (temp == NULL)//NULL이면 못찾은 것이다
				return false;//false로 return
			else {//찾으면
				return true;//true로 return
			}
		}
		return false;//움직일 수 없으므로 false
	}
	if (key == OF_KEY_LEFT) {//왼쪽
		if (charax > 100) {//움직일 수 있음(움직여도 미로 안이다)
			while (temp != NULL) {//반복문
				if (temp->vertex == charaindex -1)//방들이 연결되어있다
					break;//반복문 탈출
				temp = temp->link;//아니면 다음 링크를 타고 찾는다

			}
			if (temp == NULL)//못찾았으면
				return false;//false로 return
			else {//찾았으면
				return true;//true로 return
			}
		}
		return false;//charax가 100보다 작거나 같음
	}
	if (key == OF_KEY_DOWN) {//아래키
		if (charay < (width - 3) * 20 + 50) {//미로에서 우선 움직일 수 있으면
			while (temp != NULL) {//반복문
				if (temp->vertex == charaindex +(width-1)/2)//방들이 연결되어있으면
					break;//반복문 탈출
				temp = temp->link;//아니면 다음 링크를 타고 찾는다

			}
			if (temp == NULL)//못찾았으면
				return false;//false
			else {//찾았으면
				return true;//true
			}
		}
		return false;//움직일 수 없으면 false로 return
	}
	if (key == OF_KEY_UP) {//위
		if (charay > 50) {//미로에서 움직일 수 있으면
			while (temp != NULL) {
				if (temp->vertex == charaindex - (width - 1) / 2)//방들이 연결되어있으면
					break;//반복문 탈출
				temp = temp->link;//다음 링크 타고 확인

			}
			if (temp == NULL)//못찾았으면
				return false;//false로 return
			else {//찾았으면
				return true;//true로 return
			}
		}
		return false;//움직일 수 없으면 false
	}
	return false;//이에 해당하지 않으면 false
}
//--------------------------------------------------------------
void ofApp::getresult() {//게임이 끝났을때 state와 totalscore을 정하는 함수
	if (istarget == 1) {//타겟 도달하면
		totalscore += 1500+level*200;//1500점+레벨에따라 플러스 올라감
	}
	if (isfind == 1) {//목표찾으면
		totalscore += 1000 + level * 300;//1000+레벨에 따라 플러스
	}
	if (lefttime > 0) {//시간이 남으면
		totalscore += (int)lefttime * 80 * (level + 1);//초 당 80*(레벨+1)
	}
	if (istarget == 1 && isfind == 1)//타겟 도달하고 목표도 찾으면
		state = 1;//1
	if (istarget == 0 && isfind == 1)//타겟은 못찾고 목표는 찾으면
		state = 2;//2
	if (isfind == 0)//목표를 못찾으면(타겟은 관련없지만 점수에는 반영된다)
		state = 3;//3
}
//--------------------------------------------------------------
void ofApp::isreach() {//해당 지점에 도달했는지 확인
	if (charax == targetx && charay == targety)//target에 도달했는가
	{
		istarget = 1;//도달했으면 1
	}
	if (charax == (width - 3) * 20 + 100 && charay == (width - 3) * 20 + 50) {
		//목표지점에 도달했는가
		isfind = 1;//도달했으면 1
		getresult();//점수구하기
	}
}
//--------------------------------------------------------------
void ofApp::mazevariable() {//미로 관련 변수 초기화
	if (level == 0)//처음 시작하는거면
		totalscore = 0;//총점수0
	play_time = clock();//측정 시작
	istarget = 0, isfind = 0,ishint=0;//타겟,도착점,힌트 변수 초기화
	charax = 100, charay = 50;//캐릭터 위치 초기화
	lefthinttime = 0;//힌트 남은 시간 초기화
	gettargetxy();//targetx,targety 정하기
}
//--------------------------------------------------------------
void ofApp::BFS1() {//출발점~target


	node_pointer w;//지역변수(임시로 쓰임)
	searchshort = (short_pointer*)malloc(sizeof(short_pointer)*maze_row*maze_row);//동적할당
	for (int i = 0; i < maze_row*maze_row; i++) {//미로의 가로*세로만큼
		searchshort[i] = NULL;//초기화
	}
	int v,deletedata;//v:큐에서 delete된 값 저장, deletedata는 탐색이 끝난후 큐에 남아있는 데이터가 없도록 할때 임시로 사용됨
	front = rear = NULL;//초기화
	for (int i = 0; i < maze_row*maze_row; i++) {
		visited[i] = 0;//초기화
	}
	visited[0] = 1;//시작지점을 방문하면서 시작
	addq(0);//큐에 넣음
	searchshort[0] = (short_pointer)malloc(sizeof(shortbfs));//동적할당
	searchshort[0]->left = NULL;//초기화
	searchshort[0]->vertex = 0;//vertex 정하기
	while (front) {
		v = deleteq();//큐에 있는 값을 pop
		for (w = graph[v]; w; w = w->link) {//연결되어있는 방들
			if (!visited[w->vertex]) {//방문하지 않았으면
				if (w->vertex == maze_row * maze_row - 1) {//target을 가져갈때 도착점을 거쳐야하는경우->
					//도착점을 거치면 무조건 state가 변하게 되어있으므로 target에 도달할 수 없는 경우가 생김.
					//다른 경우를 구해야함
					freebfs1();//지금까지 구했던 것 할당해제함
					gettargetxy();//targetx,y다시 구함
					BFS1();//다시 bfs1함
					return;//return
				}
				if(searchshort[w->vertex]==NULL){
				searchshort[w->vertex] = (short_pointer)malloc(sizeof(shortbfs));//동적할당
				searchshort[w->vertex]->left = NULL;//초기화
				searchshort[w->vertex]->vertex = w->vertex;//vertex 정하기
				}

				searchshort[w->vertex]->left = searchshort[v];//역방향으로 연결함
				addq(w->vertex);//큐에 넣음
				visited[w->vertex] = 1;//방문함
			}
			if (w->vertex == targetindex) {//목표점을 찾음
				while (front != NULL) {
					deletedata=deleteq();//큐 비우기
				}
				return ;
			}
		}
	}
	printf("error\n");//못찾았으면 에러메시지
	return;
}
//--------------------------------------------------------------

void ofApp::addq(int data) {//큐에 데이터를 넣는 함수
	temp = (node_pointer)malloc(sizeof(node));//동적할당
	temp->vertex = data;//temp에 data넣기
	if (front == NULL) {//큐가 비어있으면
		front = temp;//front를 temp로 하기
		rear = temp;//rear도 temp로 하기
		front->link = NULL;//link는 NULL
	}
	else {//큐가 비어있지 않으면
		temp->link = NULL;//link는 NULL
		rear->link = temp;//rear에 temp를 연결한다
		rear = temp;//rear는 temp
	}
}

//--------------------------------------------------------------

int ofApp::deleteq() {//큐에 저장된 데이터를 pop하는 함수
	int data;//return할때 쓰이는 변수,pop된 노드의 데이터를 저장함
	if (front == NULL) {//큐가 비어있으면
		return 0;//return
	}
	else {//큐가 비어있지 않으면
		temp = front;//front를 pop해야한다
		front = front->link;//front를 그 다음 노드로 변경
		data = temp->vertex;//temp->vertex를 return해야한다
		free(temp);//동적할당 해제
		return data;//pop한 데이터를 return
	}
}
//--------------------------------------------------------------
void ofApp::freebfs1() {//bfs1에서 동적할당 했던 searchshort를 free
	for (int i = 0; i < maze_row*maze_row; i++) {
		if (searchshort[i] != NULL) {
			free(searchshort[i]);//searchshort free
		}
	}
	free(searchshort);
}
//--------------------------------------------------------------
void ofApp::BFS2() {//target~도착점


	node_pointer w;
	searchshort2 = (short_pointer*)malloc(sizeof(short_pointer)*maze_row*maze_row);//동적할당
	for (int i = 0; i < maze_row*maze_row; i++) {//미로의 가로*세로만큼
		searchshort2[i] = NULL;//초기값
	}
	int v,deletedata;//v: deleteq할때 리턴값을 저장
	//deletedata: 도착점을 찾고나서 큐를 비울때 임시로 사용
	front = rear = NULL;//초기값
	for (int i = 0; i < maze_row*maze_row; i++) {
		visited[i] = 0;//초기화
	}
	visited[targetindex] = 1;//targetindex에서 시작한다.
	addq(targetindex);//큐에 넣는다
	searchshort2[targetindex] = (short_pointer)malloc(sizeof(shortbfs));//동적할당
	searchshort2[targetindex]->left = NULL;//초기값
	searchshort2[targetindex]->vertex = targetindex;//vertex는 해당 인덱스로 한다.
	while (front) {
		v = deleteq();//v는 queue에서 pop한 값
		for (w = graph[v]; w; w = w->link) {//그래프에서 연결되어있는 노드들을 link를 따라서 간다.

			if (!visited[w->vertex]) {//방문하지 않았으면
				if (searchshort2[w->vertex] == NULL) {
					searchshort2[w->vertex] = (short_pointer)malloc(sizeof(shortbfs));//동적할당
					searchshort2[w->vertex]->left = NULL;//초기값
					searchshort2[w->vertex]->vertex = w->vertex;//vertex는 해당 인덱스로 한다.
				}

				searchshort2[w->vertex]->left = searchshort2[v];//역으로 연결
				addq(w->vertex);//큐에 넣는다
				visited[w->vertex] = 1;//방문표시
			}
			if (w->vertex == maze_row * maze_row - 1) {//도착지점을 찾으면
				while (front != NULL) {//큐가 비어있지 않으면
					deletedata=deleteq();//큐 비우기
				}
				return;
			}
		}
	}
	printf("error\n");//못찾으면 에러메시지 출력
	return;
}
//--------------------------------------------------------------
void ofApp::freebfs2() {//bfs2에서 사용된것들을 동적할당 해제
	for (int i = 0; i < maze_row*maze_row; i++) {
		if(searchshort2[i]!=NULL)
			free(searchshort2[i]);//searchshort2 free
	}
	free(searchshort2);
}
//--------------------------------------------------------------
void ofApp::drawbfs() {//bfs1,2에서 구한 것들을 화면에 출력
	
	short_pointer temp3;//도착지점부터 시작지점까지 링크를 타고 올라갈때 사용된다.

	temp3 = searchshort[targetindex];//역으로 link했기 때문에 bfs1의 도착지점에서 시작한다.
	ofSetColor(0, 0, 100);//파란 계열
	while (temp3->left != NULL) {//반복문으로 도착부터 시작까지(초기값설정에서 NULL로 했기때문에 시작지점의 left는 NULL이다)
		ofDrawLine(temp3->vertex % maze_row * 40 + 20+100, temp3->vertex / maze_row * 40 + 20+50, temp3->left->vertex  % maze_row * 40 + 20+100, temp3->left->vertex / maze_row * 40 + 20+50);//선분 출력
		temp3 = temp3->left;//링크를 타고 이동
	}//bfs1
	temp3 = searchshort2[maze_row*maze_row - 1];//도착지점
	ofSetColor(0, 100, 0);//초록 계열
	while (temp3->left != NULL) {//targetindex까지
		ofDrawLine(temp3->vertex % maze_row * 40 + 20+100, temp3->vertex / maze_row * 40 + 20+50, temp3->left->vertex  % maze_row * 40 + 20+100, temp3->left->vertex / maze_row * 40 + 20+50);//선분 출력
		temp3 = temp3->left;//링크를 타고 이동
	}//bfs2

}
//--------------------------------------------------------------
void ofApp::drawhint() {//h를 누른 후 1초동안만 hint를 표시하도록
	if ((clock() - lefthinttime) / CLOCKS_PER_SEC >= 1)//1초가 지나거나 같으면
	{
		ishint = 0;//ishint=0으로 함
		return;
	}
}

//--------------------------------------------------------------

void ofApp::showranking() {//전체, 부분출력,검색 알고리즘 구현
	ofDrawBitmapString("'q' :return to main page", 800, 100);//q누르면 초기화면으로 이동
	if (bstree.tree == NULL) {//트리가 비어있으면
		ofDrawBitmapString("No data",400,400);//도착지점 초록색으로 그리기
	}
	else {//비어있지 않으면
		
		if(rankstate==0){//초기화면
			printnum = 0;//초기화
			inorder(bstree.tree);//초기에는 다 출력하기
			
		
		}
		else if (rankstate == 1) {//부분출력
			printnum = 0;//초기화
			if (x <= y&&y>0&&x<=bstree.totaldata) {//range가 잘못되지 않으면
				rangeSearch(bstree.tree, x, y);//rangesearch()호출
			}
			else {//range가 잘못되어있으면
				ofDrawBitmapString("range error", 100, 200);//에러메시지 출력
			}
		}
		else if(rankstate==2){//rankstate가 2일때( 이름검색)
			printnum = 0;//초기화
			findname(bstree.tree);//findname()호출
			if(printnum==0)//하나도 찾지 못했으면
				ofDrawBitmapString("search failure", 100, 200);//실패 메시지 출력
		}
		else {//rankstate==3( 삭제)
			if ((deletestate==false&&deletenum > bstree.totaldata)|| (deletestate==true&&deletenum>bstree.totaldata+1)|| deletenum <= 0) {
				//삭제하지 않았는데 지워야할 랭크가 기존 노드보다 크거나, 삭제했는데 지워야할(지운)랭크가 기존노드(삭제한노드+1)보다 크면,혹은 삭제할 랭크가 0보다 같거나 작으면
				ofDrawBitmapString("delete failure", 100, 200);//에러 메시지 출력
			}
			else {//삭제할 수 있으면
				
				if (deletestate == false) {//deletestate는 key를 눌렀을때 false로 초기화된다.
					bstree.deleterank(&(bstree.tree), deletenum);//node를 delete한다.
					deletestate = true;//한번만 delete하기 위함이다.
				}
				printnum = 0;//초기화
				inorder(bstree.tree);//노드를 삭제한 이후의 트리를 출력
			}
		}
		ofDrawBitmapString("1.list ranks from X to Y", 800, 200);//1누르면 부분검색
		ofDrawBitmapString("2.list ranks by a specific name", 800, 250);//2누르면 이름검색
		ofDrawBitmapString("3.delete a specific rank", 800, 300);//3누르면 삭제
	}

}
//--------------------------------------------------------------
void ofApp::inorder(treePtr ptr) {//중위순회(내림차순)
	if (ptr) {//트리가 비어있지 않으면
		inorder(ptr->lchild);//재귀적으로 구현
		if (ptr->ranknum!=printnum+1)	//ranknum이 지금 구한것과 다르면
			ptr->ranknum = printnum+1;//ranknum을 변경
		ofDrawBitmapString(ofToString(ptr->ranknum)+" Name: "+ofToString(ptr->name)+" Score: "+ofToString(ptr->data), 100, 200+20*printnum++);
		//rank,이름,점수를 출력, printnum은 지금까지 출력한 것의 개수이므로 1증가
		inorder(ptr->rchild);//재귀적으로 구현
	}

}
//--------------------------------------------------------------


void ofApp::rangeSearch(treePtr ptr, int p,int q) {//중위순회를 변형하여 범위 검색
	if (ptr == NULL) {
		return;//노드가 비어있음
	}
	
	rangeSearch(ptr->lchild, p,q);//재귀적 구현
	
	if (ptr->ranknum>=p&&ptr->ranknum<=q)//범위에 해당되면 
		ofDrawBitmapString(ofToString(ptr->ranknum)+ " Name: " + ofToString(ptr->name) + " Score: " + ofToString(ptr->data), 100, 200 + 20 * printnum++);//랭크,이름,점수를 출력
	//printnum은 지금까지 print한것의 개수이므로 1증가
	rangeSearch(ptr->rchild, p,q);//재귀적 구현

	
}
//--------------------------------------------------------------

void ofApp::findname(treePtr ptr) {//이름 검색,중위순회를 변형하여 내림차순으로
	if (ptr) {//비어있지 않으면
		findname(ptr->lchild);//재귀적 구현
		if(strcmp(ptr->name,username)==0)//이름이 일치하면
			ofDrawBitmapString(ofToString(ptr->ranknum)+" Name: " + ofToString(ptr->name) + " Score: " + ofToString(ptr->data), 100, 200 + 20 * printnum++);
		//랭크 이름 점수 출력,printnum 1 증가
		findname(ptr->rchild);//재귀적 구현(중위순회)
	}
}
//--------------------------------------------------------------
