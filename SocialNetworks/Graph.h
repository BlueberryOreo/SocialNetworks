#pragma once
#include "utility.h"

class Graph
{
private:
	const int N = 10010;
	map<string, int> ids; // 姓名与编号的转换
	map<string, string> relations; // 可能的关系表
	bool *visited; // 是否访问过
	Node *graph; // 邻接表建图
	int *level; // 对应编号所在的层号，广度优先搜索时使用
	Stack<int> emptySpace; // 空位置
	int size; // 图的大小

	void init(); // 初始化visited、level
	int getId(string n1, string n2, int &id1, int &id2); // 获取编号，若没有则给予编号

	void importData(); // 导入关系数据
	void saveData(); // 保存当前关系数据
	int bfs(int start, int target=0, bool flag=true); // 广度优先搜索

public:
	typedef Node node;
	typedef Edge edge;
	Graph();
	Graph(vector<Edge> e); // 通过vector建图
	~Graph();

	void addEdge(Edge e); // 加边
	int removeNode(string name); // 删点
	vector<string> relative(string n1, string n2); // 查询两个人之间的联系，返回最短联系路径
	string getRelation(string n1, string n2, string &op); // 获取两个人的关系
	vector<string> spread(string name);
	bool empty(); // 判断图是否为空
	void print(); // 打印社交网络图
};