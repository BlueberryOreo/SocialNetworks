#pragma once
#include "utility.h"

class Graph
{
private:
	const int N = 10010;
	map<string, int> ids; // �������ŵ�ת��
	map<string, string> relations; // ���ܵĹ�ϵ��
	bool *visited; // �Ƿ���ʹ�
	Node *graph; // �ڽӱ�ͼ
	int *level; // ��Ӧ������ڵĲ�ţ������������ʱʹ��
	Stack<int> emptySpace; // ��λ��
	int size; // ͼ�Ĵ�С

	void init(); // ��ʼ��visited��level
	int getId(string n1, string n2, int &id1, int &id2); // ��ȡ��ţ���û���������

	void importData(); // �����ϵ����
	void saveData(); // ���浱ǰ��ϵ����
	int bfs(int start, int target=0, bool flag=true); // �����������

public:
	typedef Node node;
	typedef Edge edge;
	Graph();
	Graph(vector<Edge> e); // ͨ��vector��ͼ
	~Graph();

	void addEdge(Edge e); // �ӱ�
	int removeNode(string name); // ɾ��
	vector<string> relative(string n1, string n2); // ��ѯ������֮�����ϵ�����������ϵ·��
	string getRelation(string n1, string n2, string &op); // ��ȡ�����˵Ĺ�ϵ
	vector<string> spread(string name);
	bool empty(); // �ж�ͼ�Ƿ�Ϊ��
	void print(); // ��ӡ�罻����ͼ
};