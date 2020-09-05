#include <iostream>

// TODO write it with minMax and memoization

struct Node
{
	int data;
	Node* left;
	Node* right;
};

bool allLt(int val, Node* r)
{
	if (!r) return true;

	return r->data <= val &&
		   allLt(val, r->left) &&
		   allLt(val, r->right);
}

bool allGt(int val, Node* r)
{
	if (!r) return true;

	return r->data >= val &&
		   allGt(val, r->left) &&
		   allGt(val, r->right);
}

// other repr
int getMin(Node* r)
{
	if (!r) return (1<<(sizeof(int)<<3)-1); // - inf

	int ml = getMin(r->left);
	int mr = getMin(r->right);

	return std::min(std::min(r->data, ml), mr);
}

bool isBST(const Node* r)
{
	if (!r) return true;

	return isBST(r->left) &&
		   isBST(r->right) &&
		   allLt(r->data, r->left) &&
		   allGt(r->data, r->right);
}


int main(int argc, char const *argv[])
{
	Node n1{1, nullptr, nullptr};
	Node n{2, &n1, nullptr};

	std::cout << std::boolalpha << isBST(&n) << std::endl;
	return 0;
}