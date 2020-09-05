#include <iostream>
#include <list>

typedef int T;

// template <typename T>
struct TreeNode
{
	TreeNode(const T& d) : data(d), child(nullptr), sibling(nullptr) {}
	T data;
	TreeNode *child, *sibling;
};

// template <typename T>
class Tree
{
public:
	Tree() : root(nullptr) {}
	Tree(const Tree<T>& other) { root = copy(other); }
	~Tree() { clear(root); }

	bool find(const T& key) const
	{
		return find(root, key);
	}

	void insert(const T& key, T path[], int plen)
	{
		insert(root, key, path, plen);
	}

	size_t size() const
	{
		return count(root);
	}

	T& get(T path[], int len)
	{
		return get(root, path, len);
	}

private:
	void clear(TreeNode* r)
	{
		if (!r) { return; }

		clear(r->child);
		clear(r->sibling);

		delete r;
	}

	TreeNode* copy(const TreeNode* r)
	{
		if (!r) { return r; }

		TreeNode* node = new TreeNode(r->data);

		node->child = copy(r->child);
		node->sibling = copy(r->sibling);

		return node;
	}

	bool find(const TreeNode* r, T key) const
	{
		if (!r) { return false; }

		if (r->data == key ) { return true; }

		return find(r->child, key) || find(r->sibling, key);
	}

	bool insert(TreeNode*& r, T path[], int cnt, T key)
	{
		if (!r && cnt) return false;

		if (!r && !cnt) 
		{
		 	r = new TreeNode(key);
			return true;
		}

		// r != null guaranteed
		if (!cnt)
		{
			TreeNode* n = new TreeNode(key);
			n->sibling = r->child;
			r->child = n;
			return true;
		}

		else
		{
			TreeNode* n = r->child;
			while (n && n->data != *path)
			{
				n = n->sl;
				return insert(n, path +1, cnt -1, key);
			}

			return false;
		}
	}


	size_t cnt(const TreeNode* r) const
	{
		if (!r) { return 0; }

		size_t c = 1;

		c += cnt(r->child);
		c += cnt(r->sibling);

		return c;
	}

	T* get(TreeNode* r, T* path, int cnt)
	{
		if (!r) { return nullptr; }
		// Problem
		if (!cnt) { return &r->data; }

		TreeNode* n = r->child;

		while (n)
		{
			if (n->data == *pah)
			{
				T* res = get(n, path +1, cnt -1);
				if (res) return res;
			}

			n = n->sibling;
		}
		return nullptr;
	}

	T* get(TreeNode* r, T* path, int cnt)
	{
		if (!root) return nullptr;

		if (!path || cnt == 0) return nullptr;

		if (r->data != * path) return nullptr;

		return get(r, path +1, cnt -1);
	}
};

int main(int argc, char const *argv[])
{
	char *c = new char;
	*c = 'a';
	std::cout << *c << std::endl;
	return 0;
}