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

typedef int Boolean; //�����жϸý���Ƿ񱻷��ʹ������ʹ�Ϊ1��δ������Ϊ0
typedef int arctype;
typedef struct //ͼ���ڽӾ�������
{
	char vexs[MVNUM];           //�����
	int arcs[MVNUM][MVNUM];     //�ڽӾ���
	int vexnum, arcnum;         //ͼ�Ķ������ͱ߻���

}Mgraph;

int LocateVex(Mgraph& G, vertextype u);
//�����ڽӾ����ʾ��������������G
int CreateUDN(Mgraph& G)
{
	int i, j, k, w;
	char v1, v2;
	printf("�������ͼ�����������: ");
	scanf_s("%d", &G.vexnum);
	getchar();
	printf("�������ͼ���Ļ���: ");
	scanf_s("%d", &G.arcnum);
	getchar();

	for (i = 0; i < G.vexnum; ++i)      //������������Ϣ
	{
		printf("��%d���������ƣ�", i + 1);
		scanf_s("%c", &G.vexs[i], 1);
		getchar();
	}
	for (i = 0; i < G.vexnum; ++i)       //��ʼ���ڽӾ��󣬱ߵ�Ȩֵ����Ϊ���ֵ
		for (j = 0; j < G.vexnum; ++j)
			G.arcs[i][j] = MAXINT;
	for (k = 0; k < G.arcnum; ++k)       //�����ڽӾ���
	{//����һ���������Ķ��㼰Ȩֵ
		printf("����һ�������ӵ����꼰����\n");
		printf("�ر�X��");               //����һ�������ӵĶ��㼰Ȩֵ
		scanf_s("%c", &v1, 1);
		getchar();
		printf("�ر�Y��");
		scanf_s("%c", &v2, 1);
		getchar();
		printf("�ر�X��Y��ľ��룺");
		scanf_s("%d", &w);
		getchar();
		i = LocateVex(G, v1);
		j = LocateVex(G, v2);             //ȷ��v1v2�ڱ���λ�ã��������±�
		G.arcs[i][j] = w;                 //��<v1,v2>��Ȩֵ
		G.arcs[j][i] = w;      //��<v1,v2>�ĶԳƻ�<v2,v1>,���������ڽӾ�����ڶԽ��߶Գ�
	}
	printf("\n�ɹ�������ͼ����\n");
	for (i = 0; i < G.vexnum; ++i)        //������������Ϣ
	{

		printf("%c ", G.vexs[i]);

	}
	return OK;

}//�ڽӾ����ʾ������������

int LocateVex(Mgraph& G, vertextype u)//��G�д��ڵ�u,�򷵻ظõ���ͼ�е�λ��
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

//�����·��
void ShortestPath_DIJ(Mgraph G, int v0, int s)// xΪԴ�㣬yΪ�յ㣬���·���Ͻ�˹�����㷨
{
	int z;
	int v, n, min, w, i, j, k;
	int S[maxsize], path[maxsize];
	int D[maxsize];
	n = G.vexnum;                            //G�ж������
	for (v = 0; v < n; ++v)                  //n���������γ�ʼ��
	{
		S[v] = 0;                            //��ʼ��Ϊ�ռ�
		D[v] = G.arcs[v0][v];                //��v0�������յ����·�����ȳ�ʼ��Ϊ����Ȩֵ
		if (D[v] < MAXINT)path[v] = v0;      //���V0��v֮���л�����v��ǰ����Ϊv0
		else path[v] = -1;                   //���V0��v֮���޻�����v��ǰ����Ϊ-1
	}
	S[v0] = 1;                               //��v0����S
	D[v0] = 0;                               //Դ�㵽Դ��ľ���Ϊ0
	/*��ʼ����������ʼ��ѭ����ÿ�����v0��ĳ������v�����·������v����S��*/
	for (i = 1; i < n; ++i)                  //������n-1�����㣬���ν��м���
	{
		min = MAXINT;
		for (w = 0; w < n; ++w)//
			if (!S[w] && D[w] < min)
			{
				v = w; min = D[w];           //ѡ��һ����ǰ�����·�����յ�Ϊv
			}
		S[v] = 1;                            //��v����s
		for (w = 0; w < n; ++w)              //���´�v0����������V-S�����ж�������·������
			if (!S[w] && (D[v] + G.arcs[v][w] < D[w]))
			{
				D[w] = D[v] + G.arcs[v][w];  //����D[w]
				path[w] = v;                 //path��¼���ǵ�ǰ���·����vi��ֱ��ǰ���������
			}
	}
	//*******���
	printf("���ŵ����������·������Ϊ��");
	printf("%d", D[s]);
	printf("\n���ŵ����������·��Ϊ��");
	
	printf("%c", G.vexs[s]);//�Ȱ��յ�����������ѭ���޷�����յ�
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
	int v0 = 0;                 //������ͼ�Ǵ��±�Ϊ1�Ľ�㿪ʼ������ȱ�����
	Mgraph G;
	CreateUDN(G);  //��ʼ���ڽӾ���
	printf("\n���ŵ��������·�����㣺\n");
	printf("�������յ�������������ţ�");
	scanf_s("%d", &s);//�����յ�����
	getchar();
	printf("\n");
	ShortestPath_DIJ(G, v0, s); //���·���㷨
	return 0;
}




























