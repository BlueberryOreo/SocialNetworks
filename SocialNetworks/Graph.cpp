#include "Graph.h"

ostream& operator<<(ostream& out, const Node& n) {
	out << n.name << endl;
	out << "Relationship: ";
	for (int i = 0; i < n.to.size(); i++) {
		if (n.to[i].empty()) continue;
		out << n.to[i].to << "(" << n.to[i].relation << ") ";
	}
	return out;
}

void Graph::init()
{
	for (int i = 0; i < N; i++) visited[i] = 0;
	for (int i = 0; i < N; i++) level[i] = 0;
}

int Graph::getId(string n1, string n2, int& id1, int& id2)
{
	int cnt = 0;
	if (ids[n1]) id1 = ids[n1];
	else {
		size++;
		if (!emptySpace.empty()) id1 = emptySpace.top(), emptySpace.pop();
		else id1 = size, cnt++;
		ids[n1] = id1;
	}
	if (ids[n2]) id2 = ids[n2];
	else {
		size++;
		if (!emptySpace.empty()) id2 = emptySpace.top(), emptySpace.pop();
		else id2 = size, cnt++;
		ids[n2] = id2;
	}
	return cnt;
}

void Graph::importData()
{
	ifstream ifs;
	ifs.open("./relation.dat");
	if (!ifs) {
		cout << "Necessary file lost. Creating..." << endl;
		ofstream outf("./relation.dat");

		outf << "friend friend" << endl;
		outf << "classmate classmate" << endl;
		outf << "parent child" << endl;
		outf << "child parent" << endl;
		outf << "sibling sibling" << endl;
		outf << "ancestor descendant" << endl;
		outf << "descendant ancestor" << endl;
		outf << "boyfriend girlfriend" << endl;
		outf << "girlfriend boyfriend" << endl;
		outf << "wife husband" << endl;
		outf << "husband wife" << endl;
		outf << "employer employee" << endl;
		outf << "employee employer" << endl;

		ifs.open("./relation.dat");
		outf.close();
		system("cls");
	}
	string line;
	while (getline(ifs, line)) {
		string from, to;
		int i = 0;
		for (; line[i] != ' '; i ++) from.push_back(line[i]);
		for (i++; i < line.size(); i++) {
			if (line[i] == ' ') continue;
			to.push_back(line[i]);
		}
		relations[from] = to;
	}
	ifs.close();
}

void Graph::saveData()
{
	ofstream ofs;
	ofs.open("./relation.dat");
	map<string, string>::iterator it = relations.begin();
	for (; it != relations.end(); it ++) ofs << it->first << " " << it->second << endl, ofs.flush();
	ofs.close();
}

int Graph::bfs(int start, int target, bool flag)
{
	//cout << "start:" << start << endl;
	int ret = 0, layer = 0;
	queue<Node> q;
	q.push(graph[start]);
	visited[start] = 1;
	layer = q.size();
	while (!q.empty()) {
		Node now = q.front();
		if (target == 0) ret++;
		else {
			if (layer == 0) {
				layer = q.size();
				ret++;
			}
			level[ids[now.name]] = ret;
			if (ids[now.name] == target) {
				ret--;
				break;
			}
			//cout << layer << " " << ret << endl;
			layer--;
		}
		q.pop();
		if(flag) cout << now << endl;
		for (int i = 0; i < now.to.size(); i ++) {
			int nxtId = ids[now.to[i].to];
			//cout << "nxtId:" << nxtId << " visited[" << nxtId << "]=" << visited[nxtId] << endl;
			if (visited[nxtId]) continue;
			visited[nxtId] = 1;
			q.push(graph[nxtId]);
		}
	}
	return ret;
}

Graph::Graph()
{
	importData();
	size = 0;
	graph = new Node[N];
	visited = new bool[N];
	level = new int[N];
}

Graph::Graph(vector<Edge> e)
{
	importData();
	size = 0;
	graph = new Node[N];
	visited = new bool[N];
	level = new int[N];
	for (int i = 0; i < e.size(); i ++) {
		addEdge(e[i]);
	}
}

Graph::~Graph()
{
	delete[] graph;
	delete[] visited;
	delete[] level;
	saveData();
}

void Graph::addEdge(Edge e)
{
	string name1, name2;
	name1 = e.from, name2 = e.to;
	int id1, id2;
	getId(name1, name2, id1, id2);
	for (int i = 0; i < graph[id1].to.size(); i++) {
		if (graph[id1].to[i].to == name2 && !graph[id1].to[i].empty()) {
			return;
		}
	}
	graph[id1].name = name1;
	graph[id2].name = name2;
	graph[id1].to.push_back(e);
	//cout << id1 << " " << graph[id1].name << " "
	//	 << id2 << " " << graph[id2].name << " "
	//	 << e.from << " " << e.to << endl;

	Edge _2to1;
	_2to1.p = e.p;
	//cout << _2to1.empty() << endl;
	for (int i = 0; i < graph[id2].to.size(); i ++) {
		if (graph[id2].to[i].to == name1) {
			_2to1 = graph[id2].to[i];
		}
	}
	if (_2to1.empty()) {
		string opRelation = relations[e.relation];
		_2to1.from = name2;
		_2to1.to = name1;
		_2to1.relation = opRelation;
		graph[id2].to.push_back(_2to1);
	}
	else {
		relations[_2to1.relation] = e.relation;
		relations[e.relation] = _2to1.relation;
		//cout << _2to1.relation << " " << e.relation << endl;
	}
	//cout << _2to1.from << " " << _2to1.to << " " << _2to1.relation << endl;
}

int Graph::removeNode(string name)
{
	int id = ids[name];
	if (!id) return 0;
	emptySpace.push(id);
	size--;
	ids.erase(ids.find(name));
	// 删除指向要删的节点的边
	for (int i = 0; i < graph[id].to.size(); i ++) {
		int nhbId = ids[graph[id].to[i].to];
		vector<Edge>::iterator it = graph[nhbId].to.begin();
		for (; it != graph[nhbId].to.end(); it ++) {
			if (it->to == name) {
				graph[nhbId].to.erase(it);
				break;
			}
		}
	}
	graph[id].clear();
	return 1;
}

vector<string> Graph::relative(string n1, string n2)
{
	int id1, id2;
	getId(n1, n2, id1, id2);
	init();
	vector<string> path;
	int ret = bfs(id1, id2, false);
	//for (int i = 0; i < 15; i++) cout << i << " " << level[i] << endl;
	int tmp = id2;
	while (level[tmp] > 0) {
		for (int i = 0; i < graph[tmp].to.size(); i ++) {
			int toId = ids[graph[tmp].to[i].to];
			if (level[toId] == level[tmp] - 1) {
				path.push_back(graph[tmp].name);
				tmp = toId;
				break;
			}
		}
	}
	
	int i = 0, j = path.size() - 1;
	while (i < j) swap(path[i], path[j]), i ++, j --;
	if(!path.empty()) path.pop_back();
	return path;
}

string Graph::getRelation(string n1, string n2, string &op)
{
	int id1, id2;
	getId(n1, n2, id1, id2);
	for (int i = 0; i < graph[id1].to.size(); i ++) {
		if (graph[id1].to[i].to == n2) {
			string relation = graph[id1].to[i].relation;
			op = relations[relation];
			return relation;
		}
	}
	return "";
}

vector<string> Graph::spread(string name)
{
	vector<string> ret;
	int id = ids[name];
	if (id == 0) return ret;

	init();
	queue <Node> q;
	q.push(graph[id]);
	visited[id] = 1;
	while (!q.empty()) {
		Node now = q.front();
		q.pop();
		ret.push_back(now.name);
		for (int i = 0; i < now.to.size(); i ++) {
			int nxtId = ids[now.to[i].to];
			if (visited[nxtId]) continue;
			int tmp = rnd();
			if (tmp <= now.to[i].p) {
				visited[nxtId] = 1;
				q.push(graph[nxtId]);
			}
		}
	}
	return ret;
}

bool Graph::empty()
{
	return size == 0;
}

void Graph::print()
{
	/*for (int i = 1; i <= size; i ++) {
		cout << graph[i].name << ":";
		for (int j = 0; j < graph[i].to.size(); j ++) {
			cout << graph[i].to[j].to << " ";
		}
		cout << endl;
	}*/
	init();
	int cnt = 0;
	int i = 0;
	while (cnt < size) {
		i++;
		if (visited[i]) continue;
		cnt += bfs(i);
	}
}
