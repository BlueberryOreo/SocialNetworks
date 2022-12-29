#pragma once
#include <string>
#include <vector>
using namespace std;

struct Edge {
	string from, to; // 有向边连接的两个节点
	string relation; // 二者的关系
	int p; // 边的权重，在传播分析时使用
	Edge(string n1 = "", string n2 = "", string relation = "", int p=50) {
		from = n1;
		to = n2;
		this->relation = relation;
		this->p = p;
	}
	bool empty() const{
		return relation.empty();
	}
};

struct Node {
	string name; // 名称
	vector<Edge> to; // 邻接表
	Node(string name="") {
		this->name = name;
	}
	bool empty() {
		return name == "";
	}
	void clear() {
		name = "";
		to.clear();
	}
};