#include "tetris.h"

static struct sigaction act, oact;
int num = 0;//rank에 기록된 사람 수 
static struct sigaction act, oact;
typedef struct __NODE {
	struct __NODE *link;
	char name[NAMELEN];
	int score;

}NODE;
NODE* pPre, *head, *tail, *pNew;
int main() {
	int exit = 0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);
	createRankList();
	srand((unsigned int)time(NULL));

	while (!exit) {
		clear();
		switch (menu()) {
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank();  break;
		case MENU_EXIT: exit = 1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris() {
	int i, j;

	for (j = 0; j < HEIGHT; j++)
		for (i = 0; i < WIDTH; i++)
			field[j][i] = 0;

	nextBlock[0] = rand() % 7;
	nextBlock[1] = rand() % 7;
	nextBlock[2] = rand() % 7;
	blockRotate = 0;
	blockY = -1;
	blockX = WIDTH / 2 - 2;
	score = 0;
	gameOver = 0;
	timed_out = 0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline() {
	int i, j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0, 0, HEIGHT, WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2, WIDTH + 10);
	printw("NEXT BLOCK");
	DrawBox(3, WIDTH + 10, 4, 8);
	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(9, WIDTH + 10);
	DrawBox(9, WIDTH + 10, 4, 8);
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(15, WIDTH + 10);
	printw("SCORE");
	DrawBox(16, WIDTH + 10, 1, 8);
}

int GetCommand() {
	int command;
	command = wgetch(stdscr);
	switch (command) {
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command) {
	int ret = 1;
	int drawFlag = 0;
	switch (command) {
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if ((drawFlag = CheckToMove(field, nextBlock[0], (blockRotate + 1) % 4, blockY, blockX)))
			blockRotate = (blockRotate + 1) % 4;
		break;
	case KEY_DOWN:
		if ((drawFlag = CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if ((drawFlag = CheckToMove(field, nextBlock[0], blockRotate, blockY, blockX + 1)))
			blockX++;
		break;
	case KEY_LEFT:
		if ((drawFlag = CheckToMove(field, nextBlock[0], blockRotate, blockY, blockX - 1)))
			blockX--;
		break;
	default:
		break;
	}
	if (drawFlag) DrawChange(field, command, nextBlock[0], blockRotate, blockY, blockX);
	return ret;
}

void DrawField() {
	int i, j;
	for (j = 0; j < HEIGHT; j++) {
		move(j + 1, 1);
		for (i = 0; i < WIDTH; i++) {
			if (field[j][i] == 1) {
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score) {
	move(17, WIDTH + 11);
	printw("%8d", score);
}

void DrawNextBlock(int *nextBlock) {
	int i, j;
	for (i = 0; i < 4; i++) {
		move(4 + i, WIDTH + 13);
		for (j = 0; j < 4; j++) {
			if (block[nextBlock[1]][0][i][j] == 1) {
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for (i = 0; i < 4; i++) {
		move(10 + i, WIDTH + 13);
		for (j = 0; j < 4; j++) {
			if (block[nextBlock[2]][0][i][j] == 1) {
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID, int blockRotate, char tile) {
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++) {
			if (block[blockID][blockRotate][i][j] == 1 && i + y >= 0) {
				move(i + y + 1, j + x + 1);
				attron(A_REVERSE);
				printw("%c", tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT, WIDTH + 10);
}

void DrawBox(int y, int x, int height, int width) {
	int i, j;
	move(y, x);
	addch(ACS_ULCORNER);
	for (i = 0; i < width; i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for (j = 0; j < height; j++) {
		move(y + j + 1, x);
		addch(ACS_VLINE);
		move(y + j + 1, x + width + 1);
		addch(ACS_VLINE);
	}
	move(y + j + 1, x);
	addch(ACS_LLCORNER);
	for (i = 0; i < width; i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play() {
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM, &act, &oact);
	InitTetris();
	do {
		if (timed_out == 0) {
			alarm(1);
			timed_out = 1;
		}

		command = GetCommand();
		if (ProcessCommand(command) == QUIT) {
			alarm(0);
			DrawBox(HEIGHT / 2 - 1, WIDTH / 2 - 5, 1, 10);
			move(HEIGHT / 2, WIDTH / 2 - 4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	} while (!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT / 2 - 1, WIDTH / 2 - 5, 1, 10);
	move(HEIGHT / 2, WIDTH / 2 - 4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu() {
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH], int currentBlock, int blockRotate, int blockY, int blockX) {
	// user code
	int temp_i = 0, temp_j = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (block[currentBlock][blockRotate][i][j] == 1) {
					temp_i = i + blockY;
					temp_j = j + blockX;
					if (temp_i<0 || temp_j>=WIDTH || temp_j<0 || temp_i>=HEIGHT || f[temp_i][temp_j] == 1)
						return 0;

				}
			}
		}
		return 1;
	}

void DrawChange(char f[HEIGHT][WIDTH], int command, int currentBlock, int blockRotate, int blockY, int blockX) {
	// user code

	//1. 이전 블록 정보를 찾는다. ProcessCommand의 switch문을 참조할 것
	//2. 이전 블록 정보를 지운다. DrawBlock함수 참조할 것.
	//3. 새로운 블록 정보를 그린다. 
	int x = blockX, y = blockY,z=blockRotate,shadow_y=0;
	char tile = ' ';
	switch (command) {
	case KEY_RIGHT:
		x = blockX - 1, y = blockY;
		break;
	case KEY_LEFT:
		x = blockX + 1, y = blockY;
		break;
	case KEY_UP:
		z = (blockRotate +3) % 4;//이전 블록 정보라서
		break;
	case KEY_DOWN:
		x = blockX, y = blockY - 1;
		break;
	}
	shadow_y = y;
	while (CheckToMove(field, currentBlock, z, shadow_y+1, x) == 1 && shadow_y+1 < HEIGHT) {
		shadow_y++;
	}


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[currentBlock][z][i][j] == 1&&i+shadow_y>=0) {

				move(i + shadow_y + 1, j + x + 1);
				printw(".");

			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[currentBlock][z][i][j] == 1 && i + y >= 0) {

				move(i + y + 1, j + x + 1);
				printw(".");

			}
		}
	}

	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
	move(HEIGHT, WIDTH + 10);


}

void BlockDown(int sig) {
	// user code
	if (CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX) == 1) {
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else {
		if (blockY == -1) {
			gameOver = 1;
		}
		score+=AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		score = score + DeleteLine(field);
		nextBlock[0] = nextBlock[1];
		nextBlock[1] = nextBlock[2];
		nextBlock[2] = rand() % 7;
		DrawNextBlock(nextBlock);
		blockY = -1, blockX = WIDTH / 2 - 2, blockRotate = 0;
		PrintScore(score);
		DrawField();
		}
	
	timed_out = 0;
	//강의자료 p26-27의 플로우차트를 참고한다.



}

int AddBlockToField(char f[HEIGHT][WIDTH], int currentBlock, int blockRotate, int blockY, int blockX) {
	// user code
	int touched = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[currentBlock][blockRotate][i][j] == 1) {
				field[blockY + i][blockX + j] = 1;
				if (blockY + i == HEIGHT - 1)
					touched++;
				else if (field[blockY + i + 1][blockX + j] == 1)
					touched++;
			}
			
		}
	}
	return touched * 10;
	//Block이 추가된 영역의 필드값을 바꾼다.
}

int DeleteLine(char f[HEIGHT][WIDTH]) {
	// user code

	//1. 필드를 탐색하여, 꽉 찬 구간이 있는지 탐색한다.
	//2. 꽉 찬 구간이 있으면 해당 구간을 지운다. 즉, 해당 구간으로 필드값을 한칸씩 내린다.
	int flag = 0;
	int ans = 0;
	for (int i = 0; i < HEIGHT; i++) {
		flag = 0;
		for (int j = 0; j < WIDTH; j++) {
			if (f[i][j] == 1)
				flag++;
			if (flag==WIDTH) {
				ans++;
				for (int x = i - 1; x >= 1; x--) {
					for (int y = 0; y < WIDTH; y++) {
						field[x + 1][y] = field[x][y];
					}
				}
			}
		}
	}

	return ans * ans * 100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID, int blockRotate) {
	// user code
	while (CheckToMove(field, blockID, blockRotate, y, x) == 1&&y<HEIGHT) {
		y++;
	}
	y--;
	DrawBlock(y, x, blockID, blockRotate, '/');
}
void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate) {
	DrawBlock(y, x, blockID, blockRotate, ' ');
	DrawShadow(y, x, blockID, blockRotate);
}

void createRankList() {
	// user code
	FILE *fp = fopen("rank.txt", "r");

	char a[NAMELEN];
	int b = 0;
	if (fp == NULL) {
		return;
	}
	else {
		fscanf(fp, "%d", &num);
		for (int i = 0; i < num; i++) {
			fscanf(fp, "%s %d", a, &b);
			pNew = (NODE*)malloc(sizeof(NODE));
			strcpy(pNew->name, a);
			pNew->score = b;

			if (i == 0) {
				head = pNew;
				pNew->link = NULL;
			}

			else {
				NODE* p = head;

				if (head->score <= b) {
					pNew->link = head;
					head = pNew;

				}
				else {
					if (i == 1) {
						head->link = pNew;
						pNew->link = NULL;
					}
					else {
						for (int j = 0; j < i - 1; j++) {
							if (p->link->score <= b) {
								pNew->link = p->link;
								p->link = pNew;
								break;
							}
							else if (j == i - 2) {
								p->link->link = pNew;
								pNew->link = NULL;
								break;
							}
							else {
								p = p->link;
							}
						}
					}
				}

			}
		}

	}

	fclose(fp);
}

void rank() {
	// user code
	int x = 0, y = 0, count;
	clear();
	move(0, 0);
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	
	while (1) {
		char command = wgetch(stdscr);
		if (command == 'Q' || command == 'q') {
			break;
		}
		switch (command) {

		case '1':
			x = 0, y = 0;
			echo();
			printw("X: ");
			scanw("%d", &x);
			//printf("%d", x);
			printw("Y: ");
			scanw("%d", &y);
			//printw("%d", y);
			noecho();
			if (x == 0)
				x = 1;
			if (y == 0||y>num)
				y = num;
			printw("       name       |     score\n");
			printw("--------------------------------------------\n");
			if (x > y || x < 0 || y<0 || x>num||head==NULL) {
				printw("\nsearch failure: no rank in the list\n");
			}
			else {
				count = 1;
				NODE* p = head;
				for (count = 1; count <= y; count++) {
					if (count >= x) {
						printw(" %-17s|  %d\n", p->name, p->score);
					}
					p = p->link;
				}
			}
			break;
		default: break;
		}
	}
}

void writeRankFile() {
	// user code
	int temp_num = 0;
	FILE* fp = fopen("rank.txt", "r");
	if(fp==NULL){
	fp=fopen("rank.txt","w");
	fprintf(fp,"%d\n",num);
	NODE *p =head;
	for(int i=0;i<num;i++){
		fprintf(fp,"%s %d\n",p->name,p->score);
		p=p->link;
	}
	}
	
	else {
		if (fscanf(fp, "%d", &temp_num) == EOF) {
			fclose(fp);
			fp = fopen("rank.txt", "w");
			fprintf(fp, "%d\n", num);
			NODE *p = head;
			for (int i = 0; i < num; i++) {
				fprintf(fp, "%s %d\n", p->name, p->score);
				p = p->link;
			}
		}
		

		else if (num == temp_num) {
			fclose(fp);
			return;
		}

		else {
			fclose(fp);
			fp = fopen("rank.txt", "w");
			fprintf(fp, "%d\n", num);
			NODE* p = head;
			for (int i = 0; i < num; i++) {
				fprintf(fp, "%s %d\n", p->name, p->score);
				p = p->link;
			}
		}
	}
	
}

void newRank(int score) {
	// user code
	clear();
	
	move(0,0);
	char name[NAMELEN];
	printw("your name:");
	echo();
	scanw("%s", name);
	noecho();
	NODE*p = head;
	pNew = malloc(sizeof(NODE));
	pNew->score = score;
	strcpy(pNew->name, name);
	
	if(num==0)
		{
		 head=pNew;	
		 num++;
	}
	else{
		if(head->score<=score)
		{
			pNew->link = head;
			head = pNew;
		}
		else {
			if (num == 1) {
				head->link = pNew;
				pNew->link = NULL;
			}
			else {
				for (int i = 0; i < num - 1; i++) {
					if (p->link->score <= score) {
						pNew->link = p->link;
						p->link = pNew;
						if (i == 0)
							pNew = head;
						break;
					}
					else if (i == num - 2) {
						p->link->link = pNew;
						pNew->link = NULL;
						break;
					}
					else {
						p = p->link;
					}
				}
			}
		}
		num++;
	}
	
	writeRankFile();
}

void DrawRecommend(int y, int x, int blockID, int blockRotate) {
	// user code
}

int recommend(RecNode *root) {
	int max = 0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay() {
	// user code
}
