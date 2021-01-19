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
	}//ù��° ��ȣ�� �ʱ�ȭ
	for (int i = 0; i < n - 1; i++) {
		fprintf(fp, "|");
		if (m == 1)
		{
				maz[i][0] = 1;
				maz[i + 1][0] = 1;
		}
		else {
			for (int j = 0; j < m - 1; j++) {
				fprintf(fp, " ");//�� ����Ʈ
				temp = rand() % 2;//0,1�� �� ����
				if (temp == 1) {
					maz[i][j + 1] = maz[i][j];
					fprintf(fp, " ");//1�̸� ���� �����Ѵ�

					temp = rand() % 2;//���� 0,1 ���Ƿ� ���Ѵ�.

					if (temp == 1 || num_cell == 0) {//�ٷ� �ؿ��ִ� ���� �����Ѵ�.
						maz[i + 1][j] = maz[i][j];
						num_cell++;//����� �� ����

					}
					else {//�������� �ʴ´�.
						maz[i + 1][j] = (m)*(i + 1) + j;//������ ��ġ�� �ʴ� ���ڸ� ���δ�.
					
					}

				}
				else {
					fprintf(fp, "|");
					if (num_cell == 0) {//�ؿ� ����� ���� ���ٸ�
						maz[i + 1][j] = maz[i][j];//���� ��θ� �����.
						
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
		fprintf(fp, " |");//�� �׵θ�
		fprintf(fp, "\n");//���� �� ����
		for (int j = 0; j < m; j++) {
			fprintf(fp, "+");
			if (maz[i][j] == maz[i + 1][j]) {
				fprintf(fp, " ");
			}
			else {
				fprintf(fp, "-");
			}
		}
		fprintf(fp, "+");//���� ��
		fprintf(fp, "\n");
		if (i == n - 2) {//������ ��
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