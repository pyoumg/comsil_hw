#include "ofApp.h"
bst bstree(0);//��ü ����
//--------------------------------------------------------------
void ofApp::setup(){//�ʱⰪ ����
	ofSetFrameRate(15);//�ʴ� 15������
	ofBackground(255, 255, 255);//white
	state = 0;//�� �ʱ�ȭ
	totalscore = 0;//������
	istarget = 0,ishint=0;//target�� ã�Ҵ���, ��Ʈ��ư�� ��������
	photo0.load("img_0.png");//�ʱ�ȭ��
	photo1.load("img_1.png");//target==1,�ð����� ����
	photo2.load("img_2.png");//target==0.�ð����� ����
	photo3.load("img_3.png");//�ð����� ������
	target.load("target.png");//�ݶ�
	explain.load("game_explain.png");//���Ӽ���
	ranking.load("ranking.png");//��ŷ
	chara.load("character.png");//ĳ���� �̹��� �ε�
	charax = 100, charay = 50;//ĳ���� ������

	rankstate = 0;//��ŷ�ý��ۿ��� �ʱ�ȭ��(��ü���)
	
}

//--------------------------------------------------------------
void ofApp::update() {
	if (state == 4) {//�̷�
		gettime();//�����ð����ϱ�

		if (lefttime == 0)//�ð��� �ٵǸ�
			getresult();//����� ���ϱ�
		isreach();//Ư�� ������ �����ߴ��� ���ϱ�
		if (ishint == 1)//��Ʈ�� ǥ���ؾ��ϸ�
			drawhint();//1�� �������� �ƴ��� Ȯ��
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (state==0) {//�ʱ�ȭ���̸�
		
		photo0.draw(0, 0);//�ʱ�ȭ�� ����� ���
		
		ofSetColor(0);//����
		
		ofDrawBitmapString("comsil project",590,350);
		ofDrawBitmapString("20191571 Kim Seyoung", 570, 400);
		ofDrawBitmapString("press space to start game", 550, 550);
		ofDrawBitmapString("press 'r' to see ranks", 558, 575);//'r'�̳� 'R'������ ��ŷ�ý������� �Ѿ
		ofDrawBitmapString("press 'q' to quit", 575, 595);//'q'��'Q'������ ����
		ofSetColor(255);//�⺻��
	}
	else if (state == 4) {//�̷δ� �̹� ���� ����
		ofSetColor(0);//����
		
		ofDrawBitmapString("level: " +ofToString(level + 1), 200+(width-1)*20, 100);//���� ���
		ofDrawBitmapString("time: " + ofToString(lefttime), 200 + (width - 1) * 20, 150);//�ð� ���
		ofDrawBitmapString("'h': hint ", 200 + (width - 1) * 20, 200);//h������ ��Ʈ ǥ�õ�
		ofDrawRectangle((width - 1) * 20 + 400, 0, 1250, 780);//ȭ�� �����ʿ� ���������� �׸� ���
		ofSetColor(0, 255, 0);//�ʷ�
		ofDrawCircle((width - 2) * 20 + 100, (width - 2) * 20 + 50, 15);//�������� �ʷϻ����� �׸���
		ofSetColor(0);//����
		drawmaze();//�̷α׸���
		ofSetColor(255);//�⺻��
		draw(charax, charay);//ĳ���ͱ׸���
		if(istarget==0)//target�� ã�� ������
			target.draw(targetx, targety);//������ ��������
		if (ishint == 1) {//��Ʈ�� �׷����ϸ�
			drawbfs();//��Ʈ�� �׸���
		}
	
	}
	else if (state == 5) {//���Ӽ���
		explain.draw(0, 0);//����ȭ�� ���
		ofSetColor(0);//����
		ofDrawBitmapString("press space to start game", 570, 730);//�����̽��� ������ �Ѿ
		ofSetColor(255);//�⺻��
	}
	else if (state == 1) {//target�� ã�� �ð����� ������
		photo1.draw(0, 0);//ȭ�� ���
		ofSetColor(0);//����
		ofDrawBitmapString("press space", 570, 740);//�����̽��� ������ �Ѿ
		ofSetColor(255);//�⺻��
	}
	else if (state == 2) {//target�� ��ã�� �ð����� ������
		photo2.draw(0, 0);//ȭ�� ���
		ofSetColor(0);//����
		ofDrawBitmapString("press space", 570, 740);//�����̽���
		ofSetColor(255);//�⺻��
	}
	else if (state == 3) {//�ð����� ��������
		photo3.draw(0, 0);//ȭ�����
		ofSetColor(0);//����
		ofDrawBitmapString("press space", 570, 740);//�����̽���
		ofSetColor(255);//�⺻��
	}
	else if (state == 6) {//��ŷ�ý���
		ranking.draw(0, 0);//��ŷ��� ���
		ofSetColor(0);//����
		showranking();//��ŷ ǥ��
		ofSetColor(255);//�⺻��
	}

}
void ofApp::draw(int x, int y) {//ĳ���� �̵�
	chara.draw(x, y);//ĳ���� �׸���
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){//Ű�� ������
	if (key == 'r' || key == 'R') {//r������ ��ŷ ��
		if (state == 0) {//�ʱ�ȭ�鿡���� ������ ��ŷ ��
			ofClear(255, 255, 255);//ȭ�� �����
			state = 6;//state�� ��ŷ���°����� ����
		}
	}
	if (key == ' ') {//�����̽�
		if (state == 0)//�ʱ�ȭ��
		{
			ofClear(255, 255, 255);//ȭ�������
			state=5;//���Ӽ���
		}
		else if (state == 5) {//���Ӽ����� �����̽� ������
			ofClear(255, 255, 255);//ȭ�� �����
			state = 4, level = 0;//������ 0(���۰�),�̷�ȭ��

			makemaze();//�̷� �����
			mazevariable();//�������ʱ�ȭ
			BFS1();//����~target
			BFS2();//target~����
		}
		else if (state >= 1 && state <= 3) {//���ȭ��
			ofClear(255, 255, 255);//ȭ�������
			freebfs1();//bfs1���� �����Ҵ� �ߴ��� ����
			freebfs2();//bfs2���� �����Ҵ��ߴ� �� ���� (�̷θ� ���Ӱ� �׷�����)
			if (level < 2)//�� �̷� �������ϸ�
			{
				level++;//����1����
				state = 4;//�̷�ȭ��
				
				makemaze();//�̷θ����
				mazevariable();//�������ʱ�ȭ
				BFS1();//����~target
				BFS2();//target~��
			}
			else {//���� ���� ���̸�
				printf("score: %d\n", totalscore);//������ ���
				printf("your name: ");//�̸� �Է¹ޱ�
				bstree.totaldata++;//�� ���� �þ
				scanf("%s", username);//�̸��� �Է¹���
				bstree.insert(&(bstree.tree),totalscore, username);//bst�� ����
				level = 0;//���� �ʱ�ȭ
				state = 0;//�ʱ�ȭ�� �̵�
			}

		}
	}

	
	if (key == '1') {//1������ ������ŭ �����
		if (state == 6&&bstree.tree!=NULL) {//��ŷȭ���̰� tree�� ������� ������
			rankstate = 1;//rankstate����
			printf("X: ");//���� ���� �ޱ�
			scanf("%d", &x);//x�� ����
			printf("Y: ");//�� ���� �ޱ�
			scanf("%d", &y);//y�� ����
			
		}
	}
	if (key == '2') {//�̸����� �˻��ϱ�
		if (state == 6 && bstree.tree != NULL) {//��ŷȭ���̰� Ʈ���� ������� ����
			printf("Input the name: ");//�̸� �Է�
			scanf("%s", username);//�Է¹޾Ƽ� username�� ����
			rankstate = 2;//rankstate����

		}
	}
	if (key == '3')//����
	{
		if (state == 6 && bstree.tree != NULL) {//��ŷȭ���̰� Ʈ���� ������� ����
			printf("Input the rank: ");//������ ���� 
			scanf("%d", &deletenum);//deletenum���� �Է¹ޱ�
			rankstate = 3;//rankstate����
			deletestate = false;//deletestate�ʱ�ȭ
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {//Ű�� ������ '����'
	
	
	if (state==4) {//����ȭ���϶�
		//ĳ���͸� �����δ�
		if (key == OF_KEY_RIGHT) {//����Ű ����
			if (ischaramove(charax, charay, key) == true) {//ĳ���Ͱ� ������ �� ����
				charax += 40;//x��ǥ 40����
			}
		}
		
		if(key==OF_KEY_LEFT){//���� Ű ������ ��
			if (ischaramove(charax, charay, key) == true) {//ĳ���Ͱ� ������ �� ����
					charax -= 40;//x��ǥ 40����
				
			}
		}
		if (key == OF_KEY_DOWN) {//�Ʒ�Ű
			if (ischaramove(charax, charay, key) == true) {//ĳ���Ͱ� ������ �� ����
				charay += 40;//y��ǥ 40����(�Ʒ��� ������)
				
			}
		}
		if (key == OF_KEY_UP) {//��
			if (ischaramove(charax, charay, key) == true) {//ĳ���Ͱ� ������ �� ����
				charay -= 40;//y��ǥ 40����(���� �ö�
					
			}
		}
		if (key == 'h' || key == 'H') {//��Ʈ��ư ����
			lefthinttime = clock();//���� �ð��� ����
			ishint = 1;//��Ʈ�� ��´ٰ� ����
		}
		
	}

	if (key == 'q' || key == 'Q') {//qŰ�� ������ 
		if (state == 6) {//��ŷȭ���̸�
			state = 0;//�ʱ�ȭ������ �̵�
			rankstate = 0;//rankstate�ʱ�ȭ
		}
		else if (state == 0) {//�ʱ�ȭ���̸�
			_Exit(0);//���α׷� ����
		}
	}
}

//--------------------------------------------------------------

void ofApp::drawmaze() {
	ofSetColor(100);//����
	ofSetLineWidth(5);//������
	//y�� 50,x�� 100�� �������� ����
	ofDrawLine(100, 50, (width - 1) * 20+100, 50);//����1
	ofDrawLine(100, 50, 100, (width - 1) * 20+50);//����1
	ofDrawLine(100, (width - 1) * 20+50, (width - 1) * 20+100, (width - 1) * 20+50);//����2
	ofDrawLine((width - 1) * 20+100, 50, (width - 1) * 20+100, (width - 1) * 20+50);//����2,�׵θ� �׸���
	for (int i = 1; i < width - 1; i++) {//�׵θ� �����ϰ� �׸���
		for (int j = 1; j < width - 1; j++) {//�׵θ� �����ϰ� �׸���
			if (maze[i][j] == '|') {//|�� ���μ� ���

				ofDrawLine(j * 20+100, (i - 1) * 20+50, j * 20+100, (i + 1) * 20+50);//���μ� ���
			}
			else if (maze[i][j] == '-') {//-�� ���μ� ���
				ofDrawLine((j - 1) * 20+100, i * 20+50, (j + 1) * 20+100, i * 20+50);//���μ� ���
			}

		}
	}
	ofSetColor(255);//�⺻��

}

//--------------------------------------------------------------

void ofApp::readFile() {//������ �д� �Լ�
	char openstr[12] = "maze0_0.maz";//str�� �⺻��

	int temp = rand() % 2;//�������� ���� �ϳ� ������
	openstr[4] = level + '0';//level ����
	openstr[6] = temp + '0';//�������� 2���߿� 1���� ����
	
	if (level == 0) {//�̷��� ������ ����,���θ� �� �� �����Ƿ� �̿� �°� �����Ҵ� �Ѵ�
		width = 21;//21
	}
	else if (level == 1) {//level�� 1�̸�
		width = 31;//width�� �����Ѵ�.
	}
	else {//level:2
		width = 35;//width�� �����Ѵ�.
	}
	maze = (char**)malloc(sizeof(char*) * (width + 1));//maze�����Ҵ�
	for (int i = 0; i < width + 1; i++) {//�ݺ��� �̿�
		maze[i] = (char*)malloc(sizeof(char)*(width + 1));//2���� �迭�̴ϱ� maze[i]�� �����Ҵ��ؾ��Ѵ�
	}
	
	FILE* fp = NULL;//����
	char tempstr[50];//�ӽ÷� ���پ� ������ �迭
	if (0 == fopen_s(&fp,ofToDataPath(openstr).c_str(), "r")) {//������ ������ 
	for(int i=0;i<width;i++){//width��ŭ(�̷��� ���μ��θ� �̹� �˰��ִ°��� ����)
		fgets(tempstr, 50, fp);//���ٹޱ�
		for (int j = 0; j < width; j++)//width��ŭ��
		{
			maze[i][j] = tempstr[j];//maze�� �ű��
		}
	}
	
	}
	fclose(fp);//���� �ݱ�
}

//--------------------------------------------------------------
void ofApp::initgraph() {//�׷��� �ʱ�ȭ
	for (int i = 0; i < maze_row*maze_row; i++) {//�ε����� �̷��� ����*���� ��ŭ �ִ�
		graph[i] = (node*)malloc(sizeof(node));//�����Ҵ�
		graph[i]->vertex = i;//�ε���
		graph[i]->link = NULL;//�ʱⰪ
		visited[i] = 0;//���� �湮���� ����
	}
}
//--------------------------------------------------------------
void ofApp::makegraph() {//char** maze�� �����ص� ���� �׷����� ��Ÿ����.
	maze_row = (width - 1) / 2;//�̷��� ����(����)
	graph = (node_pointer*)malloc(sizeof(node_pointer)*maze_row*maze_row);//�����Ҵ�
	visited = (int*)malloc(sizeof(int)*maze_row*maze_row);//�湮 �����Ҵ�
	initgraph();//�׷��� �ʱ�ȭ
	for (int i = 1; i < width - 1; i++) {//width-1�� 0�̸� �׵θ��̱� ������ ���� �ʾƵ� ��
		for (int j = 1; j < width - 1; j++) {//width-1�̳� 0�̸� �׵θ��̱� ������ ���� �ʾƵ� ��
			if (i % 2 == 1 && j % 2 == 0 && maze[i][j] == ' ') {//ĭ���� ����Ǿ�������
				temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2)];//�׷��� �ε����� ã��
				while (temp->link != NULL)
					temp = temp->link;//��������Ʈ�� ����� ������ ��带 ã�´�
				pNew = (node_pointer)malloc(sizeof(node));//�����Ҵ�
				temp->link = pNew;//����
				pNew->link = NULL;//������ ����� link�� NULL
				pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2 + 1);//���ʿ� �ִ� ��忡 �����ʿ� �ִ� ��带 ����
				//�� �����ʿ� �ִ� ��嵵 �����ؾ���
				temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2) + 1];//�ε��� ã��
				while (temp->link != NULL)
					temp = temp->link;//��������Ʈ�� ����� ������ ��带 ã�´�
				pNew = (node_pointer)malloc(sizeof(node));//�����Ҵ�
				temp->link = pNew;//�׷����� ����
				pNew->link = NULL;//������ ����� link�� NULL
				pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2);//�����ʿ� �ִ� ��忡 ���ʿ� �ִ� ��带 ����

			}
			else if (i % 2 == 0 && j % 2 == 1 && maze[i][j] == ' ') {//���Ʒ��� ����Ǿ�����
				temp = graph[((i - 1) / 2)*maze_row + ((j - 1) / 2)];//�ε���ã��
				while (temp->link != NULL)
					temp = temp->link;//��������Ʈ�� ����� ������ ��带 ã�´�
				pNew = (node_pointer)malloc(sizeof(node));//�����Ҵ��Ѵ�
				temp->link = pNew;//��������Ʈ�� ����
				pNew->link = NULL;//������ ����� link�� NULL
				pNew->vertex = ((i - 1) / 2 + 1)*maze_row + ((j - 1) / 2);//���ʿ� �ִ� ��忡 �Ʒ��ʿ� �ִ� ��带 ����
				//�� �����ʿ� �ִ� ��嵵 �����ؾ���
				temp = graph[((i - 1) / 2 + 1)*maze_row + ((j - 1) / 2)];//�ε��� ã��
				while (temp->link != NULL)
					temp = temp->link;//��������Ʈ�� ����� ������ ��带 ã�´�
				pNew = (node_pointer)malloc(sizeof(node));//�����Ҵ�
				temp->link = pNew;//��������Ʈ�� ����
				pNew->link = NULL;//������ ����� link�� NULL
				pNew->vertex = ((i - 1) / 2)*maze_row + ((j - 1) / 2);//�Ʒ��ʿ� �ִ� ��忡 ���ʿ� �ִ� ��带 ����

			}
		}
	}


}
//--------------------------------------------------------------
void ofApp::freegraph() {//�׷����� �������� ���� �׷����� ������ �����Ҵ� ������ �ʿ��ϴ�
	node_pointer pPre;
	for (int i = 0; i < maze_row*maze_row; i++) {//�̷��� ����*���θ�ŭ �����Ҵ� �߾���
		temp = graph[i];//�׷���
		while (temp != NULL) {
			pPre = temp->link;//��ũ�� Ÿ��
			free(temp);//��� �����Ҵ��� ������
			temp = pPre;//��ũ�� Ÿ�� ��
		}
	}
	for (int i = 0; i < width + 1;i++) {
		free(maze[i]);//�Է¹޾Ҵ� maze�� ����
	}
	free(maze);//������ �迭�̱� ������ ������ �����ؾ��Ѵ�.
}
//--------------------------------------------------------------
void ofApp::makemaze() {//�̷θ� �÷����Ҷ� ó�� �����ؾ��� �Լ����� ȣ����
	readFile();//���� �о maze�� ����
	makegraph();//�׷��� �����: 
    drawmaze();//maze�� ȭ�鿡 ���
	
}
//--------------------------------------------------------------
void ofApp :: gettargetxy() {//targetx,targety�� ���� ���ϴ� �Լ�
	maze_row = (width - 1) / 2;//�̷��� ����(����)
	targetx = rand() % maze_row;//�������� ����
	targety = rand() % maze_row;//�������� ����
	while ((targetx == maze_row - 1 && targety == maze_row - 1)||(targetx==0&&targety==0) ){
		targetx = rand() % maze_row;//������̳� �������̸� �ǹ̰� �����Ƿ� �ٽ� ����
		targety = rand() % maze_row;//�ٽ�����
	}
	targetindex = targety * maze_row + targetx;//target�� index
	targetx = targetx * 40 + 100;//���� ��µǴ� x��ǥ
	targety = targety * 40 + 50;//���� ��µǴ� y��ǥ
}
//--------------------------------------------------------------
void ofApp::gettime() {//�ð��� ���ϴ� �Լ�
	//level�� 0:20,1:35,2:50���� ���ѽð��� �ο��Ѵ�
	double limittime = level * 15 + 20;//���ѽð�
	lefttime = limittime - (clock() - play_time) / CLOCKS_PER_SEC;//���� �ð��� ����
	if (lefttime <= 0)//0���� ������
		lefttime = 0;//0���� ��
	return;

}
//--------------------------------------------------------------
bool ofApp::ischaramove(int charax, int charay, int key) {//ĳ���Ͱ� ������ �� �ִ���
	int charaindex = (charax-100)/40+(charay-50)/40*(width-1)/2;//ĳ������ ��ġ�� �ش��ϴ� �ε���
	temp = graph[charaindex];//�׷������� �ε����� �ش��ϴ� ���� ã�´�
	if (key == OF_KEY_RIGHT) {//������
		if (charax < (width - 3) * 20 + 100) {//�켱 ������ �� ����
			
			while (temp != NULL) {
				if (temp->vertex == charaindex + 1)//����� ����Ǿ��ִ�
					break;//�ݺ��� Ż��
				temp = temp->link;//�ƴϸ� ���� ��ũ�� Ÿ�� ã�´�
				
			}
			if (temp == NULL)//NULL�̸� ��ã�� ���̴�
				return false;//false�� return
			else {//ã����
				return true;//true�� return
			}
		}
		return false;//������ �� �����Ƿ� false
	}
	if (key == OF_KEY_LEFT) {//����
		if (charax > 100) {//������ �� ����(�������� �̷� ���̴�)
			while (temp != NULL) {//�ݺ���
				if (temp->vertex == charaindex -1)//����� ����Ǿ��ִ�
					break;//�ݺ��� Ż��
				temp = temp->link;//�ƴϸ� ���� ��ũ�� Ÿ�� ã�´�

			}
			if (temp == NULL)//��ã������
				return false;//false�� return
			else {//ã������
				return true;//true�� return
			}
		}
		return false;//charax�� 100���� �۰ų� ����
	}
	if (key == OF_KEY_DOWN) {//�Ʒ�Ű
		if (charay < (width - 3) * 20 + 50) {//�̷ο��� �켱 ������ �� ������
			while (temp != NULL) {//�ݺ���
				if (temp->vertex == charaindex +(width-1)/2)//����� ����Ǿ�������
					break;//�ݺ��� Ż��
				temp = temp->link;//�ƴϸ� ���� ��ũ�� Ÿ�� ã�´�

			}
			if (temp == NULL)//��ã������
				return false;//false
			else {//ã������
				return true;//true
			}
		}
		return false;//������ �� ������ false�� return
	}
	if (key == OF_KEY_UP) {//��
		if (charay > 50) {//�̷ο��� ������ �� ������
			while (temp != NULL) {
				if (temp->vertex == charaindex - (width - 1) / 2)//����� ����Ǿ�������
					break;//�ݺ��� Ż��
				temp = temp->link;//���� ��ũ Ÿ�� Ȯ��

			}
			if (temp == NULL)//��ã������
				return false;//false�� return
			else {//ã������
				return true;//true�� return
			}
		}
		return false;//������ �� ������ false
	}
	return false;//�̿� �ش����� ������ false
}
//--------------------------------------------------------------
void ofApp::getresult() {//������ �������� state�� totalscore�� ���ϴ� �Լ�
	if (istarget == 1) {//Ÿ�� �����ϸ�
		totalscore += 1500+level*200;//1500��+���������� �÷��� �ö�
	}
	if (isfind == 1) {//��ǥã����
		totalscore += 1000 + level * 300;//1000+������ ���� �÷���
	}
	if (lefttime > 0) {//�ð��� ������
		totalscore += (int)lefttime * 80 * (level + 1);//�� �� 80*(����+1)
	}
	if (istarget == 1 && isfind == 1)//Ÿ�� �����ϰ� ��ǥ�� ã����
		state = 1;//1
	if (istarget == 0 && isfind == 1)//Ÿ���� ��ã�� ��ǥ�� ã����
		state = 2;//2
	if (isfind == 0)//��ǥ�� ��ã����(Ÿ���� ���þ����� �������� �ݿ��ȴ�)
		state = 3;//3
}
//--------------------------------------------------------------
void ofApp::isreach() {//�ش� ������ �����ߴ��� Ȯ��
	if (charax == targetx && charay == targety)//target�� �����ߴ°�
	{
		istarget = 1;//���������� 1
	}
	if (charax == (width - 3) * 20 + 100 && charay == (width - 3) * 20 + 50) {
		//��ǥ������ �����ߴ°�
		isfind = 1;//���������� 1
		getresult();//�������ϱ�
	}
}
//--------------------------------------------------------------
void ofApp::mazevariable() {//�̷� ���� ���� �ʱ�ȭ
	if (level == 0)//ó�� �����ϴ°Ÿ�
		totalscore = 0;//������0
	play_time = clock();//���� ����
	istarget = 0, isfind = 0,ishint=0;//Ÿ��,������,��Ʈ ���� �ʱ�ȭ
	charax = 100, charay = 50;//ĳ���� ��ġ �ʱ�ȭ
	lefthinttime = 0;//��Ʈ ���� �ð� �ʱ�ȭ
	gettargetxy();//targetx,targety ���ϱ�
}
//--------------------------------------------------------------
void ofApp::BFS1() {//�����~target


	node_pointer w;//��������(�ӽ÷� ����)
	searchshort = (short_pointer*)malloc(sizeof(short_pointer)*maze_row*maze_row);//�����Ҵ�
	for (int i = 0; i < maze_row*maze_row; i++) {//�̷��� ����*���θ�ŭ
		searchshort[i] = NULL;//�ʱ�ȭ
	}
	int v,deletedata;//v:ť���� delete�� �� ����, deletedata�� Ž���� ������ ť�� �����ִ� �����Ͱ� ������ �Ҷ� �ӽ÷� ����
	front = rear = NULL;//�ʱ�ȭ
	for (int i = 0; i < maze_row*maze_row; i++) {
		visited[i] = 0;//�ʱ�ȭ
	}
	visited[0] = 1;//���������� �湮�ϸ鼭 ����
	addq(0);//ť�� ����
	searchshort[0] = (short_pointer)malloc(sizeof(shortbfs));//�����Ҵ�
	searchshort[0]->left = NULL;//�ʱ�ȭ
	searchshort[0]->vertex = 0;//vertex ���ϱ�
	while (front) {
		v = deleteq();//ť�� �ִ� ���� pop
		for (w = graph[v]; w; w = w->link) {//����Ǿ��ִ� ���
			if (!visited[w->vertex]) {//�湮���� �ʾ�����
				if (w->vertex == maze_row * maze_row - 1) {//target�� �������� �������� ���ľ��ϴ°��->
					//�������� ��ġ�� ������ state�� ���ϰ� �Ǿ������Ƿ� target�� ������ �� ���� ��찡 ����.
					//�ٸ� ��츦 ���ؾ���
					freebfs1();//���ݱ��� ���ߴ� �� �Ҵ�������
					gettargetxy();//targetx,y�ٽ� ����
					BFS1();//�ٽ� bfs1��
					return;//return
				}
				if(searchshort[w->vertex]==NULL){
				searchshort[w->vertex] = (short_pointer)malloc(sizeof(shortbfs));//�����Ҵ�
				searchshort[w->vertex]->left = NULL;//�ʱ�ȭ
				searchshort[w->vertex]->vertex = w->vertex;//vertex ���ϱ�
				}

				searchshort[w->vertex]->left = searchshort[v];//���������� ������
				addq(w->vertex);//ť�� ����
				visited[w->vertex] = 1;//�湮��
			}
			if (w->vertex == targetindex) {//��ǥ���� ã��
				while (front != NULL) {
					deletedata=deleteq();//ť ����
				}
				return ;
			}
		}
	}
	printf("error\n");//��ã������ �����޽���
	return;
}
//--------------------------------------------------------------

void ofApp::addq(int data) {//ť�� �����͸� �ִ� �Լ�
	temp = (node_pointer)malloc(sizeof(node));//�����Ҵ�
	temp->vertex = data;//temp�� data�ֱ�
	if (front == NULL) {//ť�� ���������
		front = temp;//front�� temp�� �ϱ�
		rear = temp;//rear�� temp�� �ϱ�
		front->link = NULL;//link�� NULL
	}
	else {//ť�� ������� ������
		temp->link = NULL;//link�� NULL
		rear->link = temp;//rear�� temp�� �����Ѵ�
		rear = temp;//rear�� temp
	}
}

//--------------------------------------------------------------

int ofApp::deleteq() {//ť�� ����� �����͸� pop�ϴ� �Լ�
	int data;//return�Ҷ� ���̴� ����,pop�� ����� �����͸� ������
	if (front == NULL) {//ť�� ���������
		return 0;//return
	}
	else {//ť�� ������� ������
		temp = front;//front�� pop�ؾ��Ѵ�
		front = front->link;//front�� �� ���� ���� ����
		data = temp->vertex;//temp->vertex�� return�ؾ��Ѵ�
		free(temp);//�����Ҵ� ����
		return data;//pop�� �����͸� return
	}
}
//--------------------------------------------------------------
void ofApp::freebfs1() {//bfs1���� �����Ҵ� �ߴ� searchshort�� free
	for (int i = 0; i < maze_row*maze_row; i++) {
		if (searchshort[i] != NULL) {
			free(searchshort[i]);//searchshort free
		}
	}
	free(searchshort);
}
//--------------------------------------------------------------
void ofApp::BFS2() {//target~������


	node_pointer w;
	searchshort2 = (short_pointer*)malloc(sizeof(short_pointer)*maze_row*maze_row);//�����Ҵ�
	for (int i = 0; i < maze_row*maze_row; i++) {//�̷��� ����*���θ�ŭ
		searchshort2[i] = NULL;//�ʱⰪ
	}
	int v,deletedata;//v: deleteq�Ҷ� ���ϰ��� ����
	//deletedata: �������� ã���� ť�� ��ﶧ �ӽ÷� ���
	front = rear = NULL;//�ʱⰪ
	for (int i = 0; i < maze_row*maze_row; i++) {
		visited[i] = 0;//�ʱ�ȭ
	}
	visited[targetindex] = 1;//targetindex���� �����Ѵ�.
	addq(targetindex);//ť�� �ִ´�
	searchshort2[targetindex] = (short_pointer)malloc(sizeof(shortbfs));//�����Ҵ�
	searchshort2[targetindex]->left = NULL;//�ʱⰪ
	searchshort2[targetindex]->vertex = targetindex;//vertex�� �ش� �ε����� �Ѵ�.
	while (front) {
		v = deleteq();//v�� queue���� pop�� ��
		for (w = graph[v]; w; w = w->link) {//�׷������� ����Ǿ��ִ� ������ link�� ���� ����.

			if (!visited[w->vertex]) {//�湮���� �ʾ�����
				if (searchshort2[w->vertex] == NULL) {
					searchshort2[w->vertex] = (short_pointer)malloc(sizeof(shortbfs));//�����Ҵ�
					searchshort2[w->vertex]->left = NULL;//�ʱⰪ
					searchshort2[w->vertex]->vertex = w->vertex;//vertex�� �ش� �ε����� �Ѵ�.
				}

				searchshort2[w->vertex]->left = searchshort2[v];//������ ����
				addq(w->vertex);//ť�� �ִ´�
				visited[w->vertex] = 1;//�湮ǥ��
			}
			if (w->vertex == maze_row * maze_row - 1) {//���������� ã����
				while (front != NULL) {//ť�� ������� ������
					deletedata=deleteq();//ť ����
				}
				return;
			}
		}
	}
	printf("error\n");//��ã���� �����޽��� ���
	return;
}
//--------------------------------------------------------------
void ofApp::freebfs2() {//bfs2���� ���Ȱ͵��� �����Ҵ� ����
	for (int i = 0; i < maze_row*maze_row; i++) {
		if(searchshort2[i]!=NULL)
			free(searchshort2[i]);//searchshort2 free
	}
	free(searchshort2);
}
//--------------------------------------------------------------
void ofApp::drawbfs() {//bfs1,2���� ���� �͵��� ȭ�鿡 ���
	
	short_pointer temp3;//������������ ������������ ��ũ�� Ÿ�� �ö󰥶� ���ȴ�.

	temp3 = searchshort[targetindex];//������ link�߱� ������ bfs1�� ������������ �����Ѵ�.
	ofSetColor(0, 0, 100);//�Ķ� �迭
	while (temp3->left != NULL) {//�ݺ������� �������� ���۱���(�ʱⰪ�������� NULL�� �߱⶧���� ���������� left�� NULL�̴�)
		ofDrawLine(temp3->vertex % maze_row * 40 + 20+100, temp3->vertex / maze_row * 40 + 20+50, temp3->left->vertex  % maze_row * 40 + 20+100, temp3->left->vertex / maze_row * 40 + 20+50);//���� ���
		temp3 = temp3->left;//��ũ�� Ÿ�� �̵�
	}//bfs1
	temp3 = searchshort2[maze_row*maze_row - 1];//��������
	ofSetColor(0, 100, 0);//�ʷ� �迭
	while (temp3->left != NULL) {//targetindex����
		ofDrawLine(temp3->vertex % maze_row * 40 + 20+100, temp3->vertex / maze_row * 40 + 20+50, temp3->left->vertex  % maze_row * 40 + 20+100, temp3->left->vertex / maze_row * 40 + 20+50);//���� ���
		temp3 = temp3->left;//��ũ�� Ÿ�� �̵�
	}//bfs2

}
//--------------------------------------------------------------
void ofApp::drawhint() {//h�� ���� �� 1�ʵ��ȸ� hint�� ǥ���ϵ���
	if ((clock() - lefthinttime) / CLOCKS_PER_SEC >= 1)//1�ʰ� �����ų� ������
	{
		ishint = 0;//ishint=0���� ��
		return;
	}
}

//--------------------------------------------------------------

void ofApp::showranking() {//��ü, �κ����,�˻� �˰��� ����
	ofDrawBitmapString("'q' :return to main page", 800, 100);//q������ �ʱ�ȭ������ �̵�
	if (bstree.tree == NULL) {//Ʈ���� ���������
		ofDrawBitmapString("No data",400,400);//�������� �ʷϻ����� �׸���
	}
	else {//������� ������
		
		if(rankstate==0){//�ʱ�ȭ��
			printnum = 0;//�ʱ�ȭ
			inorder(bstree.tree);//�ʱ⿡�� �� ����ϱ�
			
		
		}
		else if (rankstate == 1) {//�κ����
			printnum = 0;//�ʱ�ȭ
			if (x <= y&&y>0&&x<=bstree.totaldata) {//range�� �߸����� ������
				rangeSearch(bstree.tree, x, y);//rangesearch()ȣ��
			}
			else {//range�� �߸��Ǿ�������
				ofDrawBitmapString("range error", 100, 200);//�����޽��� ���
			}
		}
		else if(rankstate==2){//rankstate�� 2�϶�( �̸��˻�)
			printnum = 0;//�ʱ�ȭ
			findname(bstree.tree);//findname()ȣ��
			if(printnum==0)//�ϳ��� ã�� ��������
				ofDrawBitmapString("search failure", 100, 200);//���� �޽��� ���
		}
		else {//rankstate==3( ����)
			if ((deletestate==false&&deletenum > bstree.totaldata)|| (deletestate==true&&deletenum>bstree.totaldata+1)|| deletenum <= 0) {
				//�������� �ʾҴµ� �������� ��ũ�� ���� ��庸�� ũ�ų�, �����ߴµ� ��������(����)��ũ�� �������(�����ѳ��+1)���� ũ��,Ȥ�� ������ ��ũ�� 0���� ���ų� ������
				ofDrawBitmapString("delete failure", 100, 200);//���� �޽��� ���
			}
			else {//������ �� ������
				
				if (deletestate == false) {//deletestate�� key�� �������� false�� �ʱ�ȭ�ȴ�.
					bstree.deleterank(&(bstree.tree), deletenum);//node�� delete�Ѵ�.
					deletestate = true;//�ѹ��� delete�ϱ� �����̴�.
				}
				printnum = 0;//�ʱ�ȭ
				inorder(bstree.tree);//��带 ������ ������ Ʈ���� ���
			}
		}
		ofDrawBitmapString("1.list ranks from X to Y", 800, 200);//1������ �κа˻�
		ofDrawBitmapString("2.list ranks by a specific name", 800, 250);//2������ �̸��˻�
		ofDrawBitmapString("3.delete a specific rank", 800, 300);//3������ ����
	}

}
//--------------------------------------------------------------
void ofApp::inorder(treePtr ptr) {//������ȸ(��������)
	if (ptr) {//Ʈ���� ������� ������
		inorder(ptr->lchild);//��������� ����
		if (ptr->ranknum!=printnum+1)	//ranknum�� ���� ���ѰͰ� �ٸ���
			ptr->ranknum = printnum+1;//ranknum�� ����
		ofDrawBitmapString(ofToString(ptr->ranknum)+" Name: "+ofToString(ptr->name)+" Score: "+ofToString(ptr->data), 100, 200+20*printnum++);
		//rank,�̸�,������ ���, printnum�� ���ݱ��� ����� ���� �����̹Ƿ� 1����
		inorder(ptr->rchild);//��������� ����
	}

}
//--------------------------------------------------------------


void ofApp::rangeSearch(treePtr ptr, int p,int q) {//������ȸ�� �����Ͽ� ���� �˻�
	if (ptr == NULL) {
		return;//��尡 �������
	}
	
	rangeSearch(ptr->lchild, p,q);//����� ����
	
	if (ptr->ranknum>=p&&ptr->ranknum<=q)//������ �ش�Ǹ� 
		ofDrawBitmapString(ofToString(ptr->ranknum)+ " Name: " + ofToString(ptr->name) + " Score: " + ofToString(ptr->data), 100, 200 + 20 * printnum++);//��ũ,�̸�,������ ���
	//printnum�� ���ݱ��� print�Ѱ��� �����̹Ƿ� 1����
	rangeSearch(ptr->rchild, p,q);//����� ����

	
}
//--------------------------------------------------------------

void ofApp::findname(treePtr ptr) {//�̸� �˻�,������ȸ�� �����Ͽ� ������������
	if (ptr) {//������� ������
		findname(ptr->lchild);//����� ����
		if(strcmp(ptr->name,username)==0)//�̸��� ��ġ�ϸ�
			ofDrawBitmapString(ofToString(ptr->ranknum)+" Name: " + ofToString(ptr->name) + " Score: " + ofToString(ptr->data), 100, 200 + 20 * printnum++);
		//��ũ �̸� ���� ���,printnum 1 ����
		findname(ptr->rchild);//����� ����(������ȸ)
	}
}
//--------------------------------------------------------------
