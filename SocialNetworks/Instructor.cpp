#include "Instructor.h"

void instructor() {
	cout << "Welcome to the social networks simulation." << endl;
	cout << "You can tell me some people and their relationship, then I will add them to the social networks." << endl;
	cout << "You can also ask me how to contact B from A if they are in the network.\n"
		<< "You should note that all the name you type in MUST be in ENGLISH.\n"
		<< "* For example, if A and B are friends and you want to add them to the network, you can say 'A and B are friends.'\n"
		<< "* Or if A is B's parent, then you can tell me 'A is B's parent.' or 'B is A's child.'\n"
		<< "* If you want to know how to contact B from A, you can ask me 'Is there any relations between A and B?' or 'What's the relationship between A and B?'\n"
		<< "* If they do have some relations, I will show you the shortest path to contact B from A. Otherwise, I will say 'No, they don't have any relations.'" << endl;
	cout << "* You can add some adjectives to show the relationship between A and B." << endl;
	cout << "* If you want to show the whole network, you can type in 'show'" << endl;
	cout << "* You can type in '?' or 'help' to show the instructions." << endl;
	cout << "* You can type in 'A gets a message.' and see how many people may get the message too." << endl;
	cout << "* You can type in 'exit' to exit the process." << endl;
}

int solve(string req, string& name1, string& name2, string& relation, int &intimacy) {
	// Error 0, question 1, add relation 2, message 3
	bool question = req[req.size() - 1] == '?';
	intimacy = 50;
	req.push_back(' ');
	bool flag = false;
	string word;
	vector<string> tmp;
	for (int i = 0; i < req.size(); i++) {
		if (req[i] == ' ') {
			tmp.push_back(word);
			word.clear();
		}
		else {
			word.push_back(req[i]);
		}
	}
	if (tmp[0] == "What's" || tmp[0] == "Is") question = true;
	char last = tmp[tmp.size() - 1][tmp[tmp.size() - 1].size() - 1];
	while (!(
		('a' <= last && last <= 'z') || ('A' <= last && last <= 'Z')
		)) tmp[tmp.size() - 1].pop_back(), last = tmp[tmp.size() - 1][tmp[tmp.size() - 1].size() - 1];;

	int i = 0;
	if (question) {
		while (i < tmp.size() && tmp[i] != "between") i++;
		if (i == tmp.size()) return 0;
		name1.append(tmp[++i]);
		for (i++; i < tmp.size() && tmp[i] != "and"; i++) name1.append(" " + tmp[i]);
		if (i == tmp.size()) return 0;
		name2.append(tmp[++i]);
		for (i++; i < tmp.size(); i++) name2.append(" " + tmp[i]);
		relation = "";
		return 1;
	}
	else {
		if (positive.find(tmp[tmp.size() - 2]) != positive.end()) {
			intimacy = 80;
		}
		else if (negative.find(tmp[tmp.size() - 2]) != negative.end()) {
			intimacy = 20;
		}
		bool is = false;
		name1.append(tmp[i++]);
		for (; i < tmp.size(); i++) {
			if (tmp[i] == "is") {
				is = true;
				break;
			}
			if (tmp[i] == "and" || tmp[i] == "gets") break;
			name1.append(" " + tmp[i]);
		}
		if (tmp[tmp.size() - 1] == "message") return 3;
		if (i == tmp.size()) return 0;
		name2.append(tmp[++i]);
		if (is) {
			for (i++; i < tmp.size() - 1 && 'A' <= tmp[i][0] && tmp[i][0] <= 'Z'; i++) name2.append(" " + tmp[i]);
			name2.pop_back();
			name2.pop_back();
			relation = tmp[tmp.size() - 1];
		}
		else {
			for (i++; i < tmp.size() - 2 && 'A' <= tmp[i][0] && tmp[i][0] <= 'Z'; i++) name2.append(" " + tmp[i]);
			relation = tmp[tmp.size() - 1];
			if (relation[relation.size() - 1] == 's') relation.pop_back();
		}
		return 2;
	}
}