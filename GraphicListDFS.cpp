#include<iostream>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 30

typedef int Status;
typedef int ElemType;
typedef int VrType;
typedef char VertexType;

typedef struct ArcNode
{
	int adjvex;
	ArcNode* nextarc;
}ArcNode;

typedef struct VNode
{
	VertexType data;
	ArcNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
	AdjList vertices;
	int vexnum, arcnum;	
}ALGraph;

bool visited[MAX_VERTEX_NUM];
Status (*VisitFunc) (int v);

void arcAdd(ALGraph& G, int m, int n)
{
	ArcNode* p, *h, *q;
	p = new ArcNode;
	p->adjvex = m;
	p->nextarc = NULL;
	h = q = G.vertices[n].firstarc;
	
	if(!q)
	{
		G.vertices[n].firstarc = p;
	}
	else
	{
		if((p->adjvex) > (q->adjvex))
		{
			p->nextarc = q;
			G.vertices[n].firstarc = p;
		}
		else
		{
			while(G.vertices[n].firstarc && q->nextarc && (p->adjvex < q->adjvex))
			{
				h = q;
				q = q->nextarc;
			}
			
			if(!q->nextarc && (p->adjvex < q->adjvex))
			{
				q->nextarc = p;
			}
			else
			{
				p->nextarc = q;
				h->nextarc = p;
			}
		}
	}
}

void createUDG(ALGraph& G)
{
	cout << "请输入顶点个数和边数：" << endl;
	cin >> G.vexnum >> G.arcnum;
	
	cout << "请输入顶点值: " << endl;
	
	for(int i = 1; i <= G.vexnum; i++)
	{
		char t;
		cin >> t;
		G.vertices[i].data = t;
		G.vertices[i].firstarc = NULL;
	}
	int m, n;
	
	for(int k = 1; k <= G.arcnum; k++)
	{
		cout << "请输入第" << k << "条边的两个顶点: " << endl;
		cin >> m >> n;
		if(m <= G.vexnum && n <= G.vexnum && m > 0 && n > 0)
		{
			arcAdd(G, m, n);
			arcAdd(G, n, m);
		}
		else
		{
			cout << "ERROR." << endl;
		}
	}
}

void printGraph(ALGraph G)
{
	cout << "无向图的创建完成，该图的邻接表表示为: " << endl;
	ArcNode* p = NULL;
	
	for(int i = 1; i <= G.vexnum; i++)
	{
		if(!G.vertices[i].firstarc)
		{
			cout << i << G.vertices[i].data << "--->NULL" << endl;
		}
		else
		{
			p = G.vertices[i].firstarc;
			cout << i << G.vertices[i].data << "-->";
			while(p->nextarc)
			{
				cout << p->adjvex << "-->";
				p = p->nextarc;
			}
			cout << p->adjvex << "--->NULL" << endl;
		}
	}
}

int firstAdjVex(ALGraph G, int v)
{
	if(G.vertices[v].firstarc)
	{
		return G.vertices[v].firstarc->adjvex;
	}
	return 0;
}

int nextAdjVex(ALGraph G, int v, int w)
{
	ArcNode* p = NULL;
	if(!G.vertices[v].firstarc)
	{
		return 0;
	}
	p = G.vertices[v].firstarc;
	while(p->adjvex != w)
	{
		p = p->nextarc;
	}
	
	if(!p->nextarc)
	{
		return 0;
	}
	return p->nextarc->adjvex;
}

void visitVex(ALGraph G, int v)
{
	cout << G.vertices[v].data << " ";
}

void DFS(ALGraph G, int v)
{
	visited[v] = true;
	visitVex(G, v);
	
	for(int w = firstAdjVex(G, v); w >= 1; w = nextAdjVex(G, v, w))
	{
		if(!visited[w])
		{
			DFS(G, w);
		}
	}
}

void DFSTraverse(ALGraph G)
{
	for(int v = 1; v <= G.vexnum; v++)
	{
		visited[v] = false;
	}
	
	for(int m = 1; m <= G.vexnum; m++)
	{
		if(!visited[m])
		{
			DFS(G, m);
		}
	}
}

int main()
{
	ALGraph G;
	createUDG(G);
	printGraph(G);
	DFSTraverse(G);
	
	getchar();
	getchar();
	getchar();
	return 0;
}
