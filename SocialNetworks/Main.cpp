#include "utility.h"
#include "Graph.h"
#include "Instructor.h"


void interact(Graph &g) {
	instructor();
	while (true) {
		cout << "===========================================" << endl;
		cout << "Now please type in your request." << endl;
		
		string req, name1, name2, relation;
		int intimacy;
		while (req.empty()) cout << ">", getline(cin, req);
		if (req == "exit") {
			cout << "See you! :)" << endl;
			system("pause");
			break;
		}
		if (req == "show") {
			if (g.empty()) cout << "There isn't any person in the network yet." << endl;
			else g.print();
			continue;
		}
		if (req == "?" || req == "help") {
			instructor();
			continue;
		}
		int res = solve(req, name1, name2, relation, intimacy);
		if (!res) {
			cout << "Sorry, but there may be some typo in your request." << endl;
		}
		else {
			if (res == 1) {
				cout << name1 << " and " << name2 << " right?" << endl;
				cout << "Let me see..." << endl;
				vector<string> res = g.relative(name1, name2);
				string op;
				string rel = g.getRelation(name1, name2, op);
				if (res.empty()) {
					if (rel.empty()) cout << "They don't have any relations." << endl;
					else {
						if (op == rel) cout << name1 << " and " << name2 << " are " << rel << "s." << endl;
						else cout << name1 << " is " << name2 << "'s " << rel << (op.empty() ? "." : (" and "
							+ name2 + " is " + name1 + "'s " + op + ".")) << endl;
					}
				}
				else {
					cout << "There is not a direct relation between " << name1 << " and " << name2 << "." << endl;
					cout << "But you can contact " << name2 << " from " << name1 << " through this way:" << endl;
					cout << name1 << "->";
					for (int i = 0; i < res.size(); i ++) {
						cout << res[i] << "->";
					}
					cout << name2;
					cout << endl;
				}
			}
			else if(res == 2) {
				cout << name1 << " and " << name2 << " have the relationship of " << relation << " right?" << endl;
				cout << "Got it!" << endl;
				//cout << "intimacy:" << intimacy << endl;
				g.addEdge(Edge(name1, name2, relation, intimacy));
			}
			else {
				vector<string> res = g.spread(name1);
				cout << "These people may get the message:" << endl;
				for (int i = 1; i < res.size(); i ++) {
					cout << res[i] << (i == res.size() - 1 ? "\n" : ", ");
				}
			}
		}
	}
}

int main() {

	srand((unsigned)time(NULL));

	Graph g;
	interact(g);

	return 0;
}

/*
Ping is Xiang Ling's master.
Ping is Traveler's good friend.
Xiang Ling and Traveler are good friends.
Xiang Ling and Guoba are good friends.
Traveler is Xing Qiu's good friend.
Tighnari is Collei's teacher.
Tighnari and Cyno are friends.
Ayaka is Ayato's sibling.

What's the relationship between Ping and Traveler?
What's the relationship between Xiang Ling and Ping?
Is there any relationship between Tighnari and Collei?
Is there any relationship between Ayaka and Ayato?
*/