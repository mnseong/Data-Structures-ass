#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node {
	public:
		string name;
		int depth;
		Node* left;
		Node* right;
		Node* parent = nullptr;
		Node(const string& name, const int& cnt) : name(name), depth(cnt) {}
		
		friend ostream& operator << (ostream &out, Node* &node) {
			out << node->name;
			return out;
		}
};

class BinarySearchTree {
	public:
		void insert(const string& name) {
			Node* par;
			Node* track = root;
			int cnt = 0;
			if (!this->root) {
				this->root = new Node(name, 0);
				return;
			}
			while (track) {
				par = track;
				cnt++;
				if (name.compare(par->name) < 0) {
					track = track->left;
				} else {
					track = track->right;
				}
			}
			if (name.compare(par->name) < 0) {
				par->left = new Node(name, cnt);
				par->left->parent = par;
			} else if (name.compare(par->name) > 0) {
				par->right = new Node(name, cnt);
				par->right->parent = par;
			} else {
				return;
			}
		}
		
		Node* query(Node* node, const string& name) {
			Node* track = node;
			if (!node) 
				return nullptr;
			if (name == track->name)
				return track;
			else {
				if (name.compare(track->name) < 0)
					return query(track->left, name);
				else
					return query(track->right, name);
			}
		}
		Node* root;
};

vector<Node*> result;

int main() {
	string firstPerson = "";
	string secondPerson = "";
	string tmp = "";
	int n = 0;
	BinarySearchTree* bst = new BinarySearchTree();
	
	getline(cin, firstPerson);
	getline(cin, secondPerson);
	cin >> n;
	cin.ignore();
	
	for (int i = 0; i < n; i++) {
		getline(cin, tmp);
		bst->insert(tmp);
	}
	
	Node* firstPersonNode = bst->query(bst->root, firstPerson);
	Node* secondPersonNode = bst->query(bst->root, secondPerson);
	Node* track;
	
	while (firstPersonNode->depth > secondPersonNode->depth)
		firstPersonNode = firstPersonNode->parent;
	
	while (firstPersonNode->depth < secondPersonNode->depth)
		secondPersonNode = secondPersonNode->parent;
	
	if (firstPersonNode == secondPersonNode) {
		track = firstPersonNode;
	} else {
		while (firstPersonNode->parent != secondPersonNode->parent) {
			firstPersonNode = firstPersonNode->parent;
			secondPersonNode = secondPersonNode->parent;
		}
		track = firstPersonNode->parent;
	}
	
	while (track) {
		result.push_back(track);
		track = track->parent;
	}
	for (int i = result.size(); i > 0; i--) {
		cout << result[i-1] << endl;
	}

	
	return 0;
}