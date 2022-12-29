#pragma once
#include <string>
#include <vector>
using namespace std;

struct Edge {
	string from, to; // ��������ӵ������ڵ�
	string relation; // ���ߵĹ�ϵ
	int p; // �ߵ�Ȩ�أ��ڴ�������ʱʹ��
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
	string name; // ����
	vector<Edge> to; // �ڽӱ�
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