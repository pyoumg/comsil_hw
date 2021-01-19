#include <iostream>
#include <cstdlib>

using namespace std;
int main() {
	int n,m, **maz;
	int temp, num_cell = 0;
	cin >> n >> m;
	temp = n;
	n = m;
	m = temp;
	
	maz = (int**)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) {
		maz[i] = (int*)malloc(sizeof(int)*m);
	}
	FILE *fp = fopen("maze.maz", "w");
	for (int i = 0; i < m; i++) {
			fprintf(fp, "+");
			fprintf(fp, "-");
	}
	fprintf(fp, "+");
	fprintf(fp, "\n");
	for (int j = 0; j < m; j++) {
		maz[0][j] =j + 1;
	}//첫번째 번호를 초기화
	for (int i = 0; i < n - 1; i++) {
		fprintf(fp, "|");
		if (m == 1)
		{
				maz[i][0] = 1;
				maz[i + 1][0] = 1;
		}
		else {
			for (int j = 0; j < m - 1; j++) {
				fprintf(fp, " ");//방 프린트
				temp = rand() % 2;//0,1둘 중 랜덤
				if (temp == 1) {
					maz[i][j + 1] = maz[i][j];
					fprintf(fp, " ");//1이면 벽을 제거한다

					temp = rand() % 2;//새로 0,1 임의로 정한다.

					if (temp == 1 || num_cell == 0) {//바로 밑에있는 방을 연결한다.
						maz[i + 1][j] = maz[i][j];
						num_cell++;//연결된 방 개수

					}
					else {//연결하지 않는다.
						maz[i + 1][j] = (m)*(i + 1) + j;//기존과 겹치지 않는 숫자를 붙인다.
					
					}

				}
				else {
					fprintf(fp, "|");
					if (num_cell == 0) {//밑에 연결된 방이 없다면
						maz[i + 1][j] = maz[i][j];//수직 경로를 만든다.
						
					}
					else {
						temp = rand() % 2;
						if (temp == 1) {
							maz[i + 1][j] = maz[i][j];

						}
						else {
							maz[i + 1][j] = (m)*(i + 1) + j;
						}
						num_cell = 0;


					}
					if (j == m - 2) {
						temp = rand() % 2;
						if (temp == 1 || num_cell == 0) {
							maz[i + 1][j + 1] = maz[i][j + 1];
						}
						else {
							maz[i + 1][j + 1] = (m)*(i + 1) + j + 1;
						}
					}
				}
			}
		}
		num_cell = 0;
		fprintf(fp, " |");//방 테두리
		fprintf(fp, "\n");//한줄 다 만듬
		for (int j = 0; j < m; j++) {
			fprintf(fp, "+");
			if (maz[i][j] == maz[i + 1][j]) {
				fprintf(fp, " ");
			}
			else {
				fprintf(fp, "-");
			}
		}
		fprintf(fp, "+");//한줄 끝
		fprintf(fp, "\n");
		if (i == n - 2) {//마지막 줄
			for (int j = 0; j < m - 1; j++) {
				if (maz[i + 1][j] != maz[i + 1][j + 1]) {
					maz[i + 1][j + 1] = maz[i + 1][j];
				}
			}
			fprintf(fp, "|");
			for (int j = 0; j < m-1; j++) {
				fprintf(fp, " ");
				if (maz[i + 1][j] == maz[i + 1][j + 1]) {
					fprintf(fp, " ");
				}
				else {
					fprintf(fp, "|");
				}
			}
			fprintf(fp, " |");
			fprintf(fp, "\n");
		}
		
		
	}
	for (int i = 0; i < m; i++) {
		fprintf(fp, "+");
		fprintf(fp, "-");
	}
	fprintf(fp, "+");

	for (int i = 0; i < n; i++) {
		free(maz[i]);
	}
	free(maz);
	fclose(fp);
	return 0;
	
}