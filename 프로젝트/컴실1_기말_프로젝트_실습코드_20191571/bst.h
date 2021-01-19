//�ѹ��� include�ǵ��� ifndef ���

#ifndef __bst__
#define __bst__

typedef struct treeNode* treePtr;//Ʈ�� ������
typedef struct treeNode//����ü
{
	treePtr lchild;//���� Ʈ��,left child
	int data;//����
	char name[50];//username
	treePtr rchild;//����Ʈ��,right child
	int ranknum;//������ ��Ÿ�� 

};
class bst {//Ŭ���� ����
public:
	bst(int);//������
	~bst();//�Ҹ���

	void insert(treePtr*, int, char*);//Ʈ���� ��带 �����ϴ� �Լ�
	treePtr modifiedSearch(treePtr, int);//insert()�����߿� �ʿ��� ��� ���� �ڸ��� ���ϴ� �Լ�
	treePtr targetparent;//targetnode�� �θ���
	treePtr tree,Ntree;//root, ���ο� �Է������������� �����Ҵ��� Ntree
	void deleterank(treePtr*, int);//��� ����
	treePtr modifiedSearch2(treePtr ptr, int k, treePtr* target);//������ ���� �� �θ��带 ã�� �Լ�
	int totaldata;//�� �ο���(=Ʈ���� �� ����)
	void freebst(treePtr);//�Ҹ��ڿ��� �ʿ���, Ʈ���� �����Ҵ��� �����ϴ� �Լ�(recursion���� ����)
};

#endif