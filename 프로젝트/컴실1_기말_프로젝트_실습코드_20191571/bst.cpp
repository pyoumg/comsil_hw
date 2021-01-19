#include "bst.h"
#include <iostream>
#include <cstdlib>
using namespace std;

bst::bst(int n) {//n�� �� ������ ����(�ʱⰪ�̹Ƿ� 0�̵���)
	treePtr tree = NULL;
	totaldata = n;
}
bst::~bst() {//�Ҹ���
	if (tree != NULL) {//Ʈ���� ������� ������
		freebst(tree);//�����Ҵ� ����
	}
}
void bst::freebst(treePtr ptr) {//����� �������� �����Ҵ��� ������
	if (ptr) {//NULL�� �ƴϸ�
		freebst(ptr->lchild);//����Ʈ���̹Ƿ�
		freebst(ptr->rchild);//����� ����
		free(ptr);//�����Ҵ�����
	}
}
void bst::insert(treePtr *ptr, int score, char* name) {
	//binary search�� �¿� ������: ������������ ����ؾ��ϹǷ�
	treePtr ans, temp;
	temp = modifiedSearch(*ptr, score);//�����ؾ��� ����� ��ġ�� ����

	if (temp || !(*ptr)) {//insert�� ��ġ�� ���߰ų� *ptr�� ���������

		ans = (treePtr)malloc(sizeof(struct treeNode));//�����Ҵ�
		ans->data = score;//����
		strcpy(ans->name, name);//�̸�
		ans->ranknum = 0;//�ʱⰪ,inorder�Ҷ� �ʱⰪ�̸� ���� ���� �־��ش�
		ans->lchild = ans->rchild = NULL;//�� �ʱ�ȭ
		if (*ptr) {//*ptr�� ������� ������(insert�� ��ġ�� ���� ��)
			if (score <= temp->data)//������ �θ��� �����ͺ��� �۰ų� ������
				temp->rchild = ans;//������ �ڽ�
			else//ũ��
				temp->lchild = ans;//���� �ڽ�
		}
		else//*ptr�� ���������
			*ptr = ans;

	}
}
//--------------------------------------------------------------

treePtr bst::modifiedSearch(treePtr ptr, int k) {//��带 �����ؾ��� ��ġ�� ����
	if (ptr == NULL) {//Ʈ���� ���������
		return NULL;//NULL�� return
	}
	while (ptr) {//�ݺ����� ����

		if (k <= ptr->data)//�ߺ� ������, �۰ų� ������
		{
			if (ptr->rchild == NULL)return ptr;//Ʈ���� ������ ������
			ptr = ptr->rchild;//������ ��尡 ������ ������
		}
		else {//ũ��
			if (ptr->lchild == NULL)return ptr;//Ʈ���� ������ ������
			ptr = ptr->lchild;//������ ��尡 ������ ������
		}
	}


}
void bst::deleterank(treePtr* ptr, int n) {//���� ������
	treePtr ans, targetnode;//ans:�ڽĳ�尡 2���ϋ� ����, targetnode: �����ؾ��� �ش���
	int a = 0, b = 0, c = -1;//�� �ʱ�ȭ
	targetparent = modifiedSearch2(*ptr, n, &targetnode);
	//target:�����ؾ��ϴ� ���,temp:target�� �θ���
	if (*ptr == NULL) {
		printf("NODE is NULL\n");//�ܼ�â�� ���
		return;
	}
	if (targetparent == NULL) {
		printf("delete error");//������ �޽��� ���
		return;
	}
	if (totaldata == 1) {//��Ʈ���ۿ� ������
		*ptr = NULL;
	}
	else if (targetnode->lchild == NULL && targetnode->rchild == NULL) {
		//�ڽ� ��尡 ������
		if (targetnode == targetparent->lchild) {//target�� �ش� �θ����� lchild��
			targetparent->lchild = NULL;//lchild�� NULL
		}
		else {
			targetparent->rchild = NULL;//rchild�� NULL
		}
	}
	else if (targetnode->lchild == NULL) {
		//�ڽ� ��尡 1���϶�(rchild)

		if (targetnode == targetparent->lchild) {//target�� �ش� �θ����� lchild��
			targetparent->lchild = targetnode->rchild;//target�� �ִ� �ڸ��� targetnode�� child�� �̵�
		}
		else {
			targetparent->rchild = targetnode->rchild;//target�� �ִ� �ڸ��� targetnode�� child�� �̵�
		}
		free(targetnode);//�����Ҵ� ����

	}
	else if (targetnode->rchild == NULL) {
		//�ڽ� ��尡 1���϶�
		if (targetnode == targetparent->lchild) {//target�� �ش� �θ����� lchild��
			targetparent->lchild = targetnode->lchild;//target�� �ִ� �ڸ��� targetnode�� child�� �̵�
		}
		else {
			targetparent->rchild = targetnode->lchild;//target�� �ִ� �ڸ��� targetnode�� child�� �̵�
		}
		free(targetnode);//�����Ҵ� ����
	}
	else {//�ڽ� ��尡 2���� ��

		ans = targetnode->lchild;//lchild
		targetparent = targetnode;//���⼭ temp�� ans�� �θ���� ����
		while (ans->rchild) {
			targetparent = ans;
			ans = ans->rchild;//���� subtree���� ���� ū ����

		}//���⼭ targetparent�� ans�� �θ���
		targetnode->data = ans->data;//targetnode�� �ִ� �ڸ��� ans�� �ٲ�
		strcpy(targetnode->name, ans->name);//�̸��� ���ڿ��迭�̹Ƿ� strcpy()�� ����Ѵ�.
		targetparent->rchild = NULL;//���� ans�� �����Ҵ��� ����

	}
	printf("delete success\n");//�ܼ�â�� ���
	totaldata--;//����⿡ �����Ѱ��̹Ƿ� totaldata�� ���δ�
}

//--------------------------------------------------------------
treePtr bst::modifiedSearch2(treePtr ptr, int k, treePtr* target) {//delete�� ���� search �Լ�, �������ϴ� �ش� ��带 return
	//�� bst�� ���������δ� �¿�������� Ʈ���� ����������, ������ ������ �ݴ��̱� ������
	//������ bst���� ����ϴ� ��İ� �����ϴ�.
	
	if (ptr == NULL) {
		return NULL;//��尡 �������
	}
	treePtr ans = ptr;//�ʱⰪ
	while (ptr) {
		if (k == ptr->ranknum) {//������ �ش� ��带 ã�� ��
			*target = ptr;//ptr�� �ش� ���
			return ans;//ans�� target�� �θ���

		}
		if (k < ptr->ranknum)//������
		{
			ans = ptr;//ans�� target�� �θ��尡 �ǵ����Ѵ�.
			ptr = ptr->lchild;//lchild�� �̵�
		}
		else {
			ans = ptr;//ans�� target�� �θ��尡 �ǵ����Ѵ�
			ptr = ptr->rchild;//rchild�� �̵�
		}
	}
	return NULL;//ã�� �������� NULL�� return
}