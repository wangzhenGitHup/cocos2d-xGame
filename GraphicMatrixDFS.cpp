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

typedef struct ArcCell
{
	VrType adj;
	ArcCell* info;
}ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{
	VertexType vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum, arcnum;
}MGraph;

bool visited[MAX_VERTEX_NUM];
Status(*VisitFunc) (int v);

int locateVex(MGraph G, VertexType v)
{
	for(int i = 0; i < G.vexnum; i++)
	{
		if(G.vexs[i] == v)
		{
			return i;
		}
	}
	return -1;
}

int firstAdjVex(MGraph G, int v)
{
	int i;
	
	for(i = 0; i < G.vexnum; i++)
	{
		if(G.arcs[v][i].adj)
		{
			return i;
		}
	}
	
	if(i == (G.vexnum - 1))
	{
		return -1;
	}
	
	return -1;
}

int nextAdjVex(MGraph G, int v, int w)
{
	int i;
	
	for(i = w + 1; i < G.vexnum; i++)
	{
		if(G.arcs[v][i].adj)
		{
			return i;
		}
	}
	
	if(i == (G.vexnum - 1))
	{
		return -1;
	}
	return -1;
}

void createUDG(MGraph& G)
{
	cout << "创建邻接矩阵的无向图: " << endl;
	int i, j, k, w;
	
	G.arcnum = 8;
	G.vexnum = 9;
	
	for(i = 0; i < G.vexnum; i++)
	{
		for(j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	
		G.vexs[0] = '1';
		G.vexs[1] = '2';
		G.vexs[2] = '3';
		G.vexs[3] = '4';
		G.vexs[4] = '5';
		G.vexs[5] = '6';
		G.vexs[6] = '7';
		G.vexs[7] = '8';
		
		G.arcs[0][1].adj = 1;
		G.arcs[0][1].info = NULL;
		
		G.arcs[1][0].adj = 1;
		G.arcs[1][0].info = NULL;
		
		G.arcs[1][3].adj = 1;
		G.arcs[1][3].info = NULL;
		
		G.arcs[3][1].adj = 1;
		G.arcs[3][1].info = NULL;
		
		G.arcs[3][7].adj = 1;
		G.arcs[3][7].info = NULL;
		
		G.arcs[7][3].adj = 1;
		G.arcs[7][3].info = NULL;
		
		G.arcs[7][4].adj = 1;
		G.arcs[7][4].info = NULL;
		
		G.arcs[4][7].adj = 1;
		G.arcs[4][7].info = NULL;
		
		G.arcs[4][1].adj = 1;
		G.arcs[4][1].info = NULL;
		
		G.arcs[1][4].adj = 1;
		G.arcs[1][4].info = NULL;
		
		G.arcs[0][2].adj = 1;
		G.arcs[0][2].info = NULL;
		
		G.arcs[2][0].adj = 1;
		G.arcs[2][0].info = NULL;
		
		G.arcs[2][5].adj = 1;
		G.arcs[2][5].info = NULL;
		
		G.arcs[5][2].adj = 1;
		G.arcs[5][2].info = NULL;
		
		G.arcs[5][6].adj = 1;
		G.arcs[5][6].info = NULL;
		
		G.arcs[6][5].adj = 1;
		G.arcs[6][5].info = NULL;
		
		G.arcs[6][2].adj = 1;
		G.arcs[6][2].info = NULL;
		
		G.arcs[2][6].adj = 1;
		G.arcs[2][6].info = NULL;
	
	return;
}

void createDG(MGraph& G)
{
	int i, j, k, w;
	char v1, v2;
	G.arcnum = 8;
	G.vexnum = 9;
	
	cout << "请输入有向图顶点个数和边数: ";
	cin >> G.vexnum >> G.arcnum;
	cout << "请输入" << G.vexnum << "个顶点的值: " << endl;
	
	for(i = 0; i < G.vexnum; i++)
	{
		cin >> G.vexs[i];
	}
	
	for(i = 0; i < G.vexnum; i++)
	{
		for(j = 0; j < G.vexnum; j++)
		{
			G.arcs[i][j].adj = 0;
			G.arcs[i][j].info = NULL;
		}
	}
	
	for(k = 1; k <= G.arcnum; k++)
	{
		cout << "请输入第" << k << "条边的两个顶点值和它们的权重: " << endl;
		cin >> v1 >> v2 >> w;
		i = locateVex(G, v1);
		j = locateVex(G, v2);
		G.arcs[i][j].adj = w;
	}
}

void visitVex(MGraph G, int v)
{
	cout << G.vexs[v] << " ";
}

void DFS(MGraph G, int v)
{
	visited[v] = true;
	visitVex(G, v);
	
	for(int w = firstAdjVex(G, v); w >= 0; w = nextAdjVex(G, v, w))
	{
		if(!visited[w])
		{
			DFS(G, w);
		}
	}
}

void DFSTraverse(MGraph G)
{
	int v;
	for(v = 0; v < G.vexnum; v++)
	{
		visited[v] = false;
	}
	
	for(v = 0; v < G.vexnum;)
	{
		if(!visited[v])
		{
			DFS(G, v);
		}
		++v;
	}
}

void printMGraph(MGraph G)
{
	cout << "邻接矩阵已经创建，邻接矩阵为: " << endl;
	
	for(int i = 0; i < G.vexnum; i++)
	{
		for(int j = 0; j < G.vexnum; j++)
		{
			cout << G.arcs[i][j].adj << " ";
		}
		cout << endl;
	}
}

int main()
{
	MGraph G;
	
	createUDG(G);
	
	printMGraph(G);
	cout << "无向邻接矩阵的深度遍历结果: " << endl;
	DFSTraverse(G);
	
	getchar();
	return 0;
}
