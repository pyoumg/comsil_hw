#include "bst.h"
#include <iostream>
#include <cstdlib>
using namespace std;

bst::bst(int n) {//n은 총 데이터 개수(초기값이므로 0이들어옴)
	treePtr tree = NULL;
	totaldata = n;
}
bst::~bst() {//소멸자
	if (tree != NULL) {//트리가 비어있지 않으면
		freebst(tree);//동적할당 해제
	}
}
void bst::freebst(treePtr ptr) {//재귀적 구현으로 동적할당을 해제함
	if (ptr) {//NULL이 아니면
		freebst(ptr->lchild);//이진트리이므로
		freebst(ptr->rchild);//재귀적 구현
		free(ptr);//동적할당해제
	}
}
void bst::insert(treePtr *ptr, int score, char* name) {
	//binary search를 좌우 반전함: 내림차순으로 출력해야하므로
	treePtr ans, temp;
	temp = modifiedSearch(*ptr, score);//삽입해야할 노드의 위치를 구함

	if (temp || !(*ptr)) {//insert할 위치를 구했거나 *ptr이 비어있으면

		ans = (treePtr)malloc(sizeof(struct treeNode));//동적할당
		ans->data = score;//점수
		strcpy(ans->name, name);//이름
		ans->ranknum = 0;//초기값,inorder할때 초기값이면 새로 값을 넣어준다
		ans->lchild = ans->rchild = NULL;//값 초기화
		if (*ptr) {//*ptr이 비어있지 않으면(insert할 위치를 구한 것)
			if (score <= temp->data)//점수가 부모노드 데이터보다 작거나 같으면
				temp->rchild = ans;//오른쪽 자식
			else//크면
				temp->lchild = ans;//왼쪽 자식
		}
		else//*ptr이 비어있으면
			*ptr = ans;

	}
}
//--------------------------------------------------------------

treePtr bst::modifiedSearch(treePtr ptr, int k) {//노드를 삽입해야할 위치를 구함
	if (ptr == NULL) {//트리가 비어있으면
		return NULL;//NULL을 return
	}
	while (ptr) {//반복으로 구현

		if (k <= ptr->data)//중복 포함함, 작거나 같으면
		{
			if (ptr->rchild == NULL)return ptr;//트리를 끝까지 내려감
			ptr = ptr->rchild;//내려갈 노드가 있으면 내려감
		}
		else {//크면
			if (ptr->lchild == NULL)return ptr;//트리를 끝까지 내려감
			ptr = ptr->lchild;//내려갈 노드가 있으면 내려감
		}
	}


}
void bst::deleterank(treePtr* ptr, int n) {//삭제 구현함
	treePtr ans, targetnode;//ans:자식노드가 2개일떄 사용됨, targetnode: 삭제해야할 해당노드
	int a = 0, b = 0, c = -1;//값 초기화
	targetparent = modifiedSearch2(*ptr, n, &targetnode);
	//target:삭제해아하는 노드,temp:target의 부모노드
	if (*ptr == NULL) {
		printf("NODE is NULL\n");//콘솔창에 출력
		return;
	}
	if (targetparent == NULL) {
		printf("delete error");//적절한 메시지 출력
		return;
	}
	if (totaldata == 1) {//루트노드밖에 없을때
		*ptr = NULL;
	}
	else if (targetnode->lchild == NULL && targetnode->rchild == NULL) {
		//자식 노드가 없을떄
		if (targetnode == targetparent->lchild) {//target이 해당 부모노드의 lchild면
			targetparent->lchild = NULL;//lchild를 NULL
		}
		else {
			targetparent->rchild = NULL;//rchild를 NULL
		}
	}
	else if (targetnode->lchild == NULL) {
		//자식 노드가 1개일때(rchild)

		if (targetnode == targetparent->lchild) {//target이 해당 부모노드의 lchild면
			targetparent->lchild = targetnode->rchild;//target이 있던 자리에 targetnode의 child를 이동
		}
		else {
			targetparent->rchild = targetnode->rchild;//target이 있던 자리에 targetnode의 child를 이동
		}
		free(targetnode);//동적할당 해제

	}
	else if (targetnode->rchild == NULL) {
		//자식 노드가 1개일때
		if (targetnode == targetparent->lchild) {//target이 해당 부모노드의 lchild면
			targetparent->lchild = targetnode->lchild;//target이 있던 자리에 targetnode의 child를 이동
		}
		else {
			targetparent->rchild = targetnode->lchild;//target이 있던 자리에 targetnode의 child를 이동
		}
		free(targetnode);//동적할당 해제
	}
	else {//자식 노드가 2개일 때

		ans = targetnode->lchild;//lchild
		targetparent = targetnode;//여기서 temp는 ans의 부모노드로 쓰임
		while (ans->rchild) {
			targetparent = ans;
			ans = ans->rchild;//왼쪽 subtree에서 가장 큰 원소

		}//여기서 targetparent는 ans의 부모노드
		targetnode->data = ans->data;//targetnode가 있던 자리를 ans로 바꿈
		strcpy(targetnode->name, ans->name);//이름은 문자열배열이므로 strcpy()를 사용한다.
		targetparent->rchild = NULL;//기존 ans의 동적할당을 해제

	}
	printf("delete success\n");//콘솔창에 출력
	totaldata--;//지우기에 성공한것이므로 totaldata를 줄인다
}

//--------------------------------------------------------------
treePtr bst::modifiedSearch2(treePtr ptr, int k, treePtr* target) {//delete를 위한 search 함수, 지워야하는 해당 노드를 return
	//이 bst는 점수순으로는 좌우반전으로 트리를 구성했지만, 순위는 점수의 반대이기 때문에
	//기존의 bst에서 사용하던 방식과 동일하다.
	
	if (ptr == NULL) {
		return NULL;//노드가 비어있음
	}
	treePtr ans = ptr;//초기값
	while (ptr) {
		if (k == ptr->ranknum) {//같으면 해당 노드를 찾은 것
			*target = ptr;//ptr이 해당 노드
			return ans;//ans는 target의 부모노드

		}
		if (k < ptr->ranknum)//작으면
		{
			ans = ptr;//ans는 target의 부모노드가 되도록한다.
			ptr = ptr->lchild;//lchild로 이동
		}
		else {
			ans = ptr;//ans는 target의 부모노드가 되도록한다
			ptr = ptr->rchild;//rchild로 이동
		}
	}
	return NULL;//찾지 못했으면 NULL을 return
}