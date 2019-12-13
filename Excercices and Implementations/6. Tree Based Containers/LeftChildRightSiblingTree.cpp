#include<iostream>
#include<iomanip>

template <typename T>
struct Node 
{ 
	explicit Node(const T& val) : data(val), sibling(nullptr), child(nullptr) {}
	Node(const Node<T>& other) : data(other.data), sibling(other.sibling), child(other.child) {}
	T data; 
	struct Node *sibling; 
	struct Node *child; 
}; 

template <typename T>
class Tree
{
public:
	Tree() : root(nullptr) {}

	Tree(const Tree<T>& other)
	{
	    copy(root, other.root);
	}

	Tree<T>& operator=(const Tree<T>& other)
	{
	    if (this != &other)
	    {
		del(root);
		copy(root, other.root);
	    }
	}

    ~Tree() { del(root); }

	void insert(const T& key, T path[], int plen)
	{
		insert(root, key, path, plen);
	}

	bool find(const T& key)
	{
		return find(root, key);
	}

	size_t size() const
	{
		return count(root);
	}

	T* get(T path[], int len)
	{
		return get(root, path, len);
	}

	void print() const
	{
        print(root, 0);
	}

private:
	Node<T> *root;

	void print(const Node<T>* node, int level) const
	{
		if(!node) return;

		std::cout << "Node: "<< node->data;

        	std::cout << " | Sibling " << (node->sibling ? node->sibling->data : 0);

		std::cout <<  "| Child " << (node->child ? node->child->data : 0);

		std::cout <<"| level "<< level << std::endl;

		print(node->sibling, level);
		print(node->child, level +1);
	}

	void insert(Node<T>*& r, const T& key, T path[], size_t plen)
	{
		if (!r)
		{
			if (plen) return;

			r = new Node<T>(key);
            		return;
		}

		if (plen == 1)
		{
			Node<T>* n = new Node<T>(key);
			n->sibling = r->child;
			r->child = n;
		  	return;
		}

        	Node<T>* n = r;
		while (n)
		{
			if (n->data == path[0])
			{
                		return insert(n->child, key, path +1, plen -1);
			}
			
			n = n->sibling;
		}
	}


	T* get(Node<T>*& r, T path[], size_t len)
	{
		if (!r || !path) return nullptr;

		if(!len) return &r->data;

		return get(r->child, path, len -1);
	}

	size_t count(const Node<T>* r) const
	{
		if (!r) return 0;

		size_t c = 1;

		c += count(r->sibling);
		c += count(r->child);

		return c;
	}

	void copy(Node<T>*& rt, const Node<T>* cp)
	{
	    if (!cp) return;

	    rt = new Node<T>(cp->data);
	    rt->sibling = cp->sibling;
	    rt->child = cp->child;

	    copy(rt->child, cp->child);
	    copy(rt->sibling, cp->sibling);
	}

    void del(Node<T>* r)
    {
	    if(!r) return;
	    del(r->sibling);
	    del(r->child);
	    delete [] r;
    }
};

int main(int argc, char const *argv[])
{
    Tree<int> tree;


    int p2[] = {1, 2, 3, 4};
    tree.insert(1, p2, 0);
    tree.insert(2, p2, 1);
    tree.insert(3, p2, 2);
    tree.insert(4, p2, 3);
    tree.insert(5, p2, 3);
    tree.insert(99, p2, 4);

    Tree<int> t2(tree);

    t2.print();
    t2.insert(15, p2, 4);

    tree = t2;
    std::cout << *tree.get(p2, 3) << std::endl;

    tree.print();

    std::cout << tree.size() << std::endl;

	return 0;
}
