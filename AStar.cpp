#include<iostream>

using namespace std;

#define STARTNODE 1
#define ENDNODE 2
#define BARRIER 3

typedef struct AStarNode
{
	int s_x;
	int s_y;
	int s_g;
	int s_h;
	int s_style;
	struct AStarNode* s_parent;
	bool isInCloseTable;
	bool isInOpenTable; 
}AStarNode, *pAStarNode;

AStarNode map_maze[10][10];
pAStarNode open_table[100];
pAStarNode close_table[100];
int open_node_count;
int close_node_count;
int top = -1;
pAStarNode path_stack[100];

void swapTest(int idx1, int idx2)
{
	pAStarNode tmp = open_table[idx1];
	open_table[idx1] = open_table[idx2];
	open_table[idx2] = tmp;
}

void adjust_heap(int index)
{
	int curr = index;
	int child = curr * 2 + 1;
	int parent = (curr - 1) / 2;
	
	if(index < 0 || index >= open_node_count)
	{
		return;
	}
	
	while(child < open_node_count)
	{
		if(child + 1 < open_node_count && 
			open_table[child]->s_g + open_table[child]->s_h > open_table[child + 1]->s_g + open_table[child + 1]->s_h)
		{
			++child;
		}
		
		if(open_table[curr]->s_g + open_table[curr]->s_h <= open_table[child]->s_g + open_table[child]->s_h)
		{
			break;
		}
		else
		{
			swapTest(child, curr);
			curr = child;
			child = curr * 2 + 1;
		}
	}
	if(curr != index)
	{
		return;
	}
	
	while(curr)
	{
		if(open_table[curr]->s_g + open_table[curr]->s_h >= open_table[parent]->s_g + open_table[parent]->s_h)
		{
			break;
		}
		else
		{
			swapTest(curr, parent);
			curr = parent;
			parent = (curr - 1) / 2;
		}
	}
}

void insert_to_openTable(int x, int y, pAStarNode currNode, pAStarNode endNode, int w)
{
	int i; 
	
	if(map_maze[x][y].s_style != BARRIER)
	{
		if(!map_maze[x][y].isInCloseTable)
		{
			if(map_maze[x][y].isInOpenTable)
			{
				if(map_maze[x][y].s_g > currNode->s_g + w)
				{
					map_maze[x][y].s_g = currNode->s_g + w;
					map_maze[x][y].s_parent = currNode;
					
					for(i = 0; i < open_node_count; i++)
					{
						if(open_table[i]->s_x == map_maze[x][y].s_x && 
							open_table[i]->s_y == map_maze[x][y].s_y)
							{
								break;
							}
					}
					adjust_heap(i);
				}
			}
			else
			{
				map_maze[x][y].s_g = currNode->s_g + w;
				map_maze[x][y].s_h = abs(endNode->s_x - x) + abs(endNode->s_y - y);
				map_maze[x][y].s_parent = currNode;
				map_maze[x][y].isInOpenTable = true;
				open_table[open_node_count++] = &(map_maze[x][y]);
			}
		}
	}
}

void getNeighbors(pAStarNode currNode, pAStarNode endNode)
{
	int x = currNode->s_x;
	int y = currNode->s_y;
	
	if((x + 1) >= 0 && (x + 1) < 10 && y >= 0 && y < 10)
	{
		insert_to_openTable(x + 1, y, currNode, endNode, 10);
	}
	
	if((x - 1) >= 0 && (x - 1) < 10 && y >=0 && y < 10)
	{
		insert_to_openTable(x - 1, y, currNode, endNode, 10);
	}
	
	if(x >= 0 && x < 10 && (y + 1) >= 0 && (y + 1) < 10)
	{
		insert_to_openTable(x, y + 1, currNode, endNode, 10);
	}
	
	if(x >= 0 && x < 10 && (y - 1) >= 0 && (y - 1) < 10)
	{
		insert_to_openTable(x, y - 1, currNode, endNode, 10);
	}
	
	if((x + 1) >= 0 && (x + 1) < 10 && (y + 1) >= 0 && (y + 1) < 10)
	{
		insert_to_openTable(x + 1, y + 1, currNode, endNode, 14);
	}
	
	if((x + 1) >= 0 && (x + 1) < 10 && (y - 1) >= 0 && (y - 1) < 10)
	{
		insert_to_openTable(x + 1, y - 1, currNode, endNode, 14);
	}
	
	if((x - 1) >= 0 && (x - 1) < 10 && (y + 1) >= 0 && (y + 1) < 10)
	{
		insert_to_openTable(x - 1, y + 1, currNode, endNode, 14);
	}
	
	if((x - 1) >= 0 && (x - 1) < 10 && (y - 1) >= 0 && (y - 1) < 10)
	{
		insert_to_openTable(x - 1, y - 1, currNode, endNode, 14);	
	}
}


int main()
{
	AStarNode* start_node;
	AStarNode* end_node;
	AStarNode* curr_node;
	bool isFound = false;
	
	int maze[][10] = 
	{
		{1, 0, 0, 3, 0, 3, 0, 0, 0, 0},
		{0, 0, 3, 0, 0, 3, 0, 3, 0, 3},
		{3, 0, 0, 0, 0, 3, 3, 3, 0, 3},
		{3, 0, 3, 0, 0, 0, 0, 0, 0, 3},
		{3, 0, 0, 0, 0, 3, 0, 0, 0, 3},
		{3, 0, 0, 3, 0, 0, 0, 3, 0, 3},
		{3, 0, 0, 0, 0, 3, 3, 0, 0, 0},
		{0, 0, 3, 0, 0, 2, 0, 0, 0, 0},
		{3, 3, 3, 0, 0, 3, 0, 3, 0, 3},
		{3, 0, 0, 0, 0, 3, 3, 3, 0 ,3}
	};
	
	int i, j, x;
	
	for(i = 0; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			map_maze[i][j].s_g = 0;
			map_maze[i][j].s_h = 0;
			map_maze[i][j].isInCloseTable = false;
			map_maze[i][j].isInOpenTable = false;
			map_maze[i][j].s_style = maze[i][j];
			map_maze[i][j].s_x = i;
			map_maze[i][j].s_y = j;
			map_maze[i][j].s_parent = NULL;
			
			if(map_maze[i][j].s_style == STARTNODE)
			{
				start_node = &(map_maze[i][j]);
			}
			else if(map_maze[i][j].s_style == ENDNODE)
			{
				end_node = &(map_maze[i][j]);
			}
			cout << maze[i][j] << "   ";
		}
		cout << endl << endl;
	}
	
	
	open_table[open_node_count++] = start_node;
	start_node->isInOpenTable = true;
	start_node->s_g = 0;
	start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
	start_node->s_parent = NULL;
	
	if(start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y)
	{
		cout << "find!" << endl;
		
		getchar();
		return 0;
	}
	
	while(true)
	{
		curr_node = open_table[0];
		open_table[0] = open_table[--open_node_count];
		adjust_heap(0);
		
		close_table[close_node_count++] = curr_node;
		curr_node->isInCloseTable = true;
		
		if(curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y)
		{
			isFound = true;
			break;
		}
		
		getNeighbors(curr_node, end_node);
		
		if(open_node_count == 0)
		{
			isFound = false;
			break;
		}
	}
	
	if(isFound)
	{
		curr_node = end_node;
		
		while(curr_node)
		{
			path_stack[++top] = curr_node;
			curr_node = curr_node->s_parent;
		}
		
		while(top >= 0)
		{
			cout << "(" << path_stack[top]->s_x << "," << path_stack[top]->s_y << ")-->";
			top--;
		}
	}
	else
	{
		cout << "没有找到路径" << endl;
	}
	
	getchar();
	return 0;
}
