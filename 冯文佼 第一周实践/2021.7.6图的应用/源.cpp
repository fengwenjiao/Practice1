#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <iostream>
#include "io.h"  
#include "math.h"  
#include "time.h"
using namespace std;
#define maxsize 70

#define OK 1
#define MAXINT 32769
#define MVNUM 60
#define vertextype char

typedef int Boolean; //用来判断该结点是否被访问过，访问过为1，未访问则为0
typedef int arctype;
typedef struct //图的邻接矩阵类型
{
	char vexs[MVNUM];           //顶点表
	int arcs[MVNUM][MVNUM];     //邻接矩阵
	int vexnum, arcnum;         //图的顶点数和边或弧数

}Mgraph;

int LocateVex(Mgraph& G, vertextype u);
//采用邻接矩阵表示法，构造无向网G
int CreateUDN(Mgraph& G)
{
	int i, j, k, w;
	char v1, v2;
	printf("请输入地图网的坐标个数: ");
	scanf_s("%d", &G.vexnum);
	getchar();
	printf("请输入地图网的弧数: ");
	scanf_s("%d", &G.arcnum);
	getchar();

	for (i = 0; i < G.vexnum; ++i)      //依次输入点的信息
	{
		printf("第%d个坐标名称：", i + 1);
		scanf_s("%c", &G.vexs[i], 1);
		getchar();
	}
	for (i = 0; i < G.vexnum; ++i)       //初始化邻接矩阵，边的权值都设为最大值
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MAXINT;
	for (k = 0; k < G.arcnum; ++k)       //构造邻接矩阵
	{//输入一条边依附的顶点及权值
		printf("输入一条弧连接的坐标及距离\n");
		printf("地标X：");               //输入一条弧连接的顶点及权值
		scanf_s("%c", &v1, 1);
		getchar();
		printf("地标Y：");
		scanf_s("%c", &v2, 1);
		getchar();
		printf("地标X与Y间的距离：");
		scanf_s("%d", &w);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);             //确定v1v2在表中位置，即数组下标
		G.arcs[i][j] = w;                 //弧<v1,v2>的权值
		G.arcs[j][i] = w;      //置<v1,v2>的对称弧<v2,v1>,无向网的邻接矩阵关于对角线对称
	}
	printf("\n成功建立地图网！\n");
	for (i = 0; i < G.vexnum; ++i)        //依次输出点的信息
	{

		printf("%c ", G.vexs[i]);

	}
	return OK;

}//邻接矩阵表示法创建无向网

int LocateVex(Mgraph& G, vertextype u)//若G中存在点u,则返回该点在图中的位置
{
	int loc;
	for (loc = 0; loc < G.vexnum; loc++)
	{
		if (G.vexs[loc] == u)
		{
			return loc;
		}
	}
	return -1;
}

//求最短路径
void ShortestPath_DIJ(Mgraph G, int v0, int s)// x为源点，y为终点，最短路径迪杰斯特拉算法
{
	int z;
	int v, n, min, w, i, j, k;
	int S[maxsize], path[maxsize];
	int D[maxsize];
	n = G.vexnum;                            //G中顶点个数
	for (v = 0; v < n; ++v)                  //n个顶点依次初始化
	{
		S[v] = 0;                            //初始化为空集
		D[v] = G.arcs[v0][v];                //将v0到各个终点最短路径长度初始化为弧上权值
		if (D[v] < MAXINT)path[v] = v0;      //如果V0和v之间有弧，则将v的前驱置为v0
		else path[v] = -1;                   //如果V0和v之间无弧，则将v的前驱置为-1
	}
	S[v0] = 1;                               //将v0加入S
	D[v0] = 0;                               //源点到源点的距离为0
	/*初始化结束，开始主循环，每次求得v0到某个顶点v的最短路径，将v加入S集*/
	for (i = 1; i < n; ++i)                  //对其余n-1个顶点，依次进行计算
	{
		min = MAXINT;
		for (w = 0; w < n; ++w)//
			if (!S[w] && D[w] < min)
			{
				v = w; min = D[w];           //选择一条当前的最短路径，终点为v
			}
		S[v] = 1;                            //将v加入s
		for (w = 0; w < n; ++w)              //更新从v0出发到集合V-S上所有顶点的最短路径长度
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];  //更新D[w]
				path[w] = v;                 //path记录的是当前最短路径上vi的直接前驱顶点序号
			}
	}
	//*******输出
	printf("西门到香樟的最短路径长度为：");
	printf("%d", D[s]);
	printf("\n西门到香樟的最短路径为：");
	
	printf("%c", G.vexs[s]);//先把终点输出，下面的循环无法输出终点
	while (s)
	{
		z = path[s];
		printf("%c", G.vexs[z]);
		s = z;
	}
}
int main()
{
	int s;
	int v0 = 0;                 //表明该图是从下标为1的结点开始深度优先遍历的
	Mgraph G;
	CreateUDN(G);  //初始化邻接矩阵
	printf("\n西门到香樟最短路径计算：\n");
	printf("请输入终点香樟的坐标序号：");
	scanf_s("%d", &s);//输入终点的序号
	getchar();
	printf("\n");
	ShortestPath_DIJ(G, v0, s); //最短路径算法
	return 0;
}




























