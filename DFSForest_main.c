#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "ALGraph.h"

int visited[MAX_VERTEX_NUM];
/***********孩子兄弟************/
#define ElementType int
typedef struct CSNode {
	ElementType		data;
	struct CSNode	*firstchild, *nextsibling;
}CSNode, *CSTree;

CSTree p = NULL;
CSTree q = NULL;

void DFSTree(ALGraph *G, int vex, CSTree T) {
	int first = 1;//标记是否为当前顶点的第一条弧
	ArcNode *arc = G->vertices[vex].firstarc;//当前顶点的第一条弧
	visited[vex] = 1;//标记当前顶点已被访问
	T->firstchild = NULL;
	T->nextsibling = NULL;
	while (arc) {//遍历当前顶点的所有弧
		if (!visited[arc->adjvex]) {//如果该弧的弧尾顶点未被访问
			p = (CSTree)malloc(sizeof(CSNode));//为新的结点分配空间
			p->data = G->vertices[arc->adjvex].data;//为结点赋值
			if (first) {//如果该顶点是顶点vex的第一条弧的弧头，则作为根的孩子结点
				T->firstchild = p;//p作为根的孩子结点
				first = 0;//失效标记
			}
			else {
				q->nextsibling = p;//否则是该顶点作为前一个弧头顶点的兄弟结点
			}
			q = p;
			DFSTree(G, arc->adjvex, q);//以当前顶点出发进行深度优先遍历图G，建立生成树q

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
Status PreOrderTraverse(CSTree T) {//先序遍历图的深度优先遍历生成树
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
	printf("先序遍历图的深度优先遍历生成树:");
	PreOrderTraverse(T);
	printf("\n");
	system("pause");
	return 1;
}