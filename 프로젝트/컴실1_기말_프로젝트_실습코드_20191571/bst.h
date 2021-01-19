//한번만 include되도록 ifndef 사용

#ifndef __bst__
#define __bst__

typedef struct treeNode* treePtr;//트리 포인터
typedef struct treeNode//구조체
{
	treePtr lchild;//이진 트리,left child
	int data;//점수
	char name[50];//username
	treePtr rchild;//이진트리,right child
	int ranknum;//순위를 나타냄 

};
class bst {//클래스 선언
public:
	bst(int);//생성자
	~bst();//소멸자

	void insert(treePtr*, int, char*);//트리에 노드를 삽입하는 함수
	treePtr modifiedSearch(treePtr, int);//insert()실행중에 필요한 노드 삽입 자리를 구하는 함수
	treePtr targetparent;//targetnode의 부모노드
	treePtr tree,Ntree;//root, 새로운 입력을받을때마다 동적할당할 Ntree
	void deleterank(treePtr*, int);//노드 삭제
	treePtr modifiedSearch2(treePtr ptr, int k, treePtr* target);//삭제할 노드와 그 부모노드를 찾는 함수
	int totaldata;//총 인원수(=트리의 총 노드수)
	void freebst(treePtr);//소멸자에서 필요한, 트리의 동적할당을 해제하는 함수(recursion으로 구현)
};

#endif