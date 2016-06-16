template<class K,class V>
struct BSTreeNode
{
	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;

	BSTreeNode(const K&key, const V&value)
		:_key(key)
		, _value(value)
		, _left(NULL)
		, _right(NULL)
	{}
};
template<class K,class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	BSTree()
		:_root(NULL)
	{}
	~BSTree()
	{
		_Destroy(_root);
	}
public:
	bool Insert(const K&key, const V&value)//插入节点
	{
		if (_root == NULL)
		{
			_root = new Node(key, value);
			return true;
		}
		Node*parent = NULL;
		Node*cur = _root;
		while (cur)
		{
			if (cur->_value<value)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_value>value)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
			
		}
		if (value > parent->_value)
			parent->_right = new Node(key, value);
		else
			parent->_left = new Node(key, value);
		return true;
	}
	
	bool Insert_R(const K&key, const V&value)//递归控制
	{
		return _Insert_R(_root,key,value);
	}
	
	Node*Find_R(const V&value)//递归
	{
		return _Find_R(_root, value);
	}
	Node*Find(const V&value)//寻找结点
	{
		Node*cur = _root;
		while (cur)
		{
			if (cur->_value > value)
				cur = cur->_right;
			else if (cur->_value < value)
				cur = cur->_right;
			else//cur->_value = value
				return cur;
		}
		return NULL;//未找到
	}
	bool Remove(const V&value)//删除结点，删除成功返回true，若不存在value则返回false
	{
		//1.删除结点左或右为空(或左右均为空)，左为空则父节点直接指向右，删除这个结点，若右为空则父节点直接指向左
		//2.删除的左右结点均不为空，则找到这个结点左树的最右节点或右树的最左节点替换
		Node*cur = _root;
		Node*parent = NULL;
		while (cur)
		{
			if (cur->_value > value)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_value < value)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
				break;
		}
		if (cur == NULL)
			return false;
		Node*del;
		//情况1
		if (cur->_left == NULL)
		{
			del = cur;
			if (parent == NULL)//根结点
			{
				_root = cur->_right;
			}
			else
			{
				if (parent->_left == cur)
					parent->_left = cur->_right;
				else
					parent->_right = cur->_right;

			}			
		}
		else if (cur->_right == NULL)
		{
			del = cur;
			if (parent == NULL)
			{
				_root = cur->_left;
			}
			else
			{
				if (parent->_left = cur)
					parent->_left = cur->_left;
				else
					parent->_right = cur->_left;
			}
		}
		else//情况2
		{
			parent = cur;
			Node*firstLeft = cur->_right;//找这个结点右节点的最左结点
			while (firstLeft->_left)
			{
				parent = firstLeft;
				firstLeft = firstLeft->_left;
			}
			del = firstLeft;
			cur->_key = firstLeft->_key;
			cur->_value = firstLeft->_value;
			if (parent->_left == firstLeft)
			{
				parent->_left = firstLeft->_right;
			}
			else
				parent->_right = firstLeft->_right;
		}
		delete del;
		return true;
	}
	bool Remove_R(const V&value)
	{
		return _Remove_R(_root, value);
	}
	void InOrder()//中序遍历，即二叉树败絮
	{
		_InOrder(_root);
		cout << endl;
	}
private:
	void _Destroy(Node*root)
	{
		if (root == NULL)
			return;
		_Destroy(root->_left);
		_Destroy(root->_right);

		delete root;
	}
	void _InOrder(Node*root)
	{
		if (root == NULL)
			return;
		_InOrder(root->_left);
		cout << root->_value<<" ";
		_InOrder(root->_right);
	}
	bool _Insert_R(Node*&root,const K&key,const V&value)
	{
		if (root == NULL)
		{
			root = new Node(key, value);
			return true;
		}
		if (value > root->_value)
			return _Insert_R(root->_right, key, value);//递归右树
		else if (value<root->_value)
			return _Insert_R(root->_left,key,value);//递归左树
		return false;
	}
	Node*_Find_R(Node*root, const V&value)
	{
		if (root->_value == value)
			return root;
		if (value>root->_value)
			return _Find_R(root->_right, value);
		else if (value < root->_value)
			return _Find_R(root->_left, value);
		else
			return NULL;//根为空或者未找到
	}
	bool _Remove_R(Node*&root, const V&value)
	{
		if (root == NULL)
			return false;
		if (root->_value>value)
			return _Remove_R(root->_left, value);
		else if (root->_value < value)
			return _Remove_R(root->_right, value);
		else//root->_value == value
		{
			Node*del = root;
			if (root->_left == NULL)
				root = root->_right;
			else if (root->_right == NULL)
				root = root->_left;
			else//左右均不为空
			{
				Node*parent = root;
				Node*cur = root->_left;
				while (cur->_left)
				{
					parent = cur;
					cur = cur->_left;
				}
				swap(cur->_value, root->_value);
				swap(cur->_key, root->_key);
				del = cur;
				parent->_left = cur->_right;
			}
			delete del;
		}
		return true;
	}
private:
	Node*_root;
};
