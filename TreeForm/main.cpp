#include <iostream>
#include <iomanip>
#include <string>
#include <stack>

using namespace std;

struct bintree {
	char data;
	bintree* left;
	bintree* right;
	bintree(char val) : data(val), left(nullptr), right(nullptr) {}
};

void show(bintree* t, int n) {
	if (t != nullptr) {
		show(t->left, n + 1);
		cout << setw(n * 3) << t->data << endl;
		show(t->right, n + 1);
	}
}


int main() {
	string expr;
	string postfix_notation;
	getline(cin, expr);
	stack<char> x, y;
	for (int i = 0; i < expr.size(); ++i) {
		if (isalnum(expr[i])) x.push(expr[i]);
		else if (expr[i] == '(') y.push(expr[i]);
		else if (expr[i] == ')') {
			while (y.top() != '(') x.push(y.top()), y.pop();
			y.pop();
		}
		else {
			if (y.size() == 0 || expr[i] == '*' && y.top() == '+' || y.top() == '(' || expr[i] == '!') {
				y.push(expr[i]);
			}
			else {
				x.push(y.top());
				y.pop();
				y.push(expr[i]);
			}
		}
	}
	while (y.size()) {
		x.push(y.top());
		y.pop();
	}
	while (x.size()) {
		postfix_notation.push_back(x.top());
		x.pop();
	}
	std::reverse(postfix_notation.begin(), postfix_notation.end());

	stack<bintree*> st;
	for (int i = 0; i < postfix_notation.size(); ++i) {
		if (isalnum(postfix_notation[i])) {
			bintree* tmp = new bintree(postfix_notation[i]);
			st.push(tmp);
		}
		else {
			if (postfix_notation[i] == '+' || postfix_notation[i] == '*') {
				bintree* tmp1, *tmp2;
				tmp1 = st.top(), st.pop();
				tmp2 = st.top(), st.pop();
				bintree* newtree = new bintree(postfix_notation[i]);
				newtree->left = tmp1;
				newtree->right = tmp2;
				st.push(newtree);
			}
			else {
				bintree* tmp = st.top();
				st.pop();
				bintree* newtree = new bintree(postfix_notation[i]);
				newtree->left = tmp;
				st.push(newtree);
			}
		}
	}
	auto ans = st.top();

	show(ans, 1);

	stack<int> q;

	for (int i = 0; i < postfix_notation.size(); ++i) {
		if (isalnum(postfix_notation[i]))
			q.push(postfix_notation[i] - '0');
		else {
			if (postfix_notation[i] == '+') {
				int tmp1, tmp2;
				tmp1 = q.top();
				q.pop();
				tmp2 = q.top();
				q.pop();
				q.push(tmp1 | tmp2);
			}
			else if (postfix_notation[i] == '*') {
				int tmp1, tmp2;
				tmp1 = q.top();
				q.pop();
				tmp2 = q.top();
				q.pop();
				q.push(tmp1 & tmp2);
			}
			else {
				int tmp1;
				tmp1 = q.top();
				q.pop();
				q.push(!tmp1);
			}
		}
	}
	system("pause");
	cout << "Answer: " << q.top() << endl;
	system("pause");
	return 0;
}