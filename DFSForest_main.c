#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"

int visited[MAX_VERTEX_NUM];
/***********�����ֵ�************/
#define ElementType int
typedef struct CSNode {
	ElementType		data;
	struct CSNode	*firstchild, *nextsibling;
}CSNode, *CSTree;

CSTree p = NULL;
CSTree q = NULL;

void DFSTree(ALGraph *G, int vex, CSTree T) {
	int first = 1;//����Ƿ�Ϊ��ǰ����ĵ�һ����
	ArcNode *arc = G->vertices[vex].firstarc;//��ǰ����ĵ�һ����
	visited[vex] = 1;//��ǵ�ǰ�����ѱ�����
	T->firstchild = NULL;
	T->nextsibling = NULL;
	while (arc) {//������ǰ��������л�
		if (!visited[arc->adjvex]) {//����û��Ļ�β����δ������
			p = (CSTree)malloc(sizeof(CSNode));//Ϊ�µĽ�����ռ�
			p->data = G->vertices[arc->adjvex].data;//Ϊ��㸳ֵ
			if (first) {//����ö����Ƕ���vex�ĵ�һ�����Ļ�ͷ������Ϊ���ĺ��ӽ��
				T->firstchild = p;//p��Ϊ���ĺ��ӽ��
				first = 0;//ʧЧ���
			}
			else {
				q->nextsibling = p;//�����Ǹö�����Ϊǰһ����ͷ������ֵܽ��
			}
			q = p;
			DFSTree(G, arc->adjvex, q);//�Ե�ǰ�����������������ȱ���ͼG������������q

		}			
		arc = arc->nextarc;
	}
}
CSTree DFSForest(ALGraph *G) {
	int i;
	CSTree T = NULL;
	for (i = 0; i < G->vexnum; ++i) {
		visited[i] = 0;
	}
	for (i = 0; i < G->vexnum; ++i) {
		if (!visited[i]) {
			p = (CSTree)malloc(sizeof(CSNode));
			p->data = G->vertices[i].data;
			if (!T) 
				T = p;
			else q->nextsibling = p;
			q = p;
			DFSTree(G, i, p);
		}
	}
	return T;
}



void visitTree(CSTree T) {
	printf("%c ", T->data);
}
Status PreOrderTraverse(CSTree T) {//�������ͼ��������ȱ���������
	if (T) {
		visitTree(T);
		if(T->firstchild) 
			PreOrderTraverse(T->firstchild);
		if(T->nextsibling) 
			PreOrderTraverse(T->nextsibling);
	}
	return 1;
}

int main(int argc, char *argv[]) {
	
	ALGraph G;
	CSTree T=NULL;
	CreateGraph(&G);
	print(G);
	T=DFSForest(&G);
	printf("�������ͼ��������ȱ���������:");
	PreOrderTraverse(T);
	printf("\n");
	system("pause");
	return 1;
}