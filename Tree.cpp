#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

class Tree
{
public:

	Tree() {}

	Tree(int value){
	    val = value;
        h = 1;
        left = NULL;
        right = NULL;
	}

	~Tree()
	{
	    if (this ->left)
            delete this->left;

	    if (this ->right)
            delete this->right;
	}

    void insert (int value)
    {
        Tree *a = this;
        a = this -> insert_private(value);
    }

	void* remove (int value)
	{
        Tree** q, *z;

        z=this;
        q=&z;

        while(1)
            {
                if(z == NULL) return 0;
                else if(value == z->val) break;
                else if(value > z->val)
                {
                    q = &z->right;
                    z = z->right;
                }
                else
                {
                    q = &z->left;
                    z = z->left;
                }
            }

            if(z->right == NULL)
            {
                *q = z->left;
                z->~Tree();
            }
            else
            {
                Tree* y = z->right;
                if(y->left == NULL)
                {
                    y->left = z->left;
                    y->set_h();
                    *q = y;
                    z->~Tree();
                }
                else
                {
                    Tree* x = y->left;
                    while(x->left != NULL)
                    {
                        y = x;
                        x = y->left;
                    }
                    y->left = x->right;
                    x->left = z->left;
                    x->right = z->right;
                    x->set_h();
                    *q = x;
                    z->~Tree();
                }
            }
    }

	bool exists(int value)
    {
        if (!this || !this->val)
        {
            return false;
        }
        else
        {
            if (this->val == value)
                return true;
            else
            {
                if (this->val > value)
                {
                    Tree* a = this->left;
                    return a -> exists(value);
                }
                else
                {
                    Tree* b = this->right;
                    return b -> exists(value);
                }
            }
        }
    }

	void print_tree()
	{
        if (!this == 0)
            {
                this -> set_h();
                this -> left -> print_tree();
                cout << this -> val << " (" << this->h << "); ";
                this -> right -> print_tree ();
            }
    }

private:
    Tree* left_rotation()
    {
        if (!this)
            return NULL;
        Tree* pl = this -> left;
        this -> left = NULL;
        Tree* q = this -> right;
        int vp = this -> val, vq;
        if (q)
            vq = q -> val;
        else
            return this;
        Tree* qr = q -> right;
        q -> right = NULL;
        Tree* ql = q -> left;
        q -> left = NULL;
        this -> right = NULL;
        this -> val = vq; // полное очищение дерева

        this -> insert(vp);
        this -> left -> right = ql;
        this -> left -> left = pl;
        this -> right = qr; // сборка его обратно
        this->set_h();
        return this;
    }

	int bfactor()
	{
	    return this->right->set_h() - this->left->set_h();
	}

	Tree* right_rotation()
        {
        if (!this)
            return NULL;
        Tree* pr = this -> right;
        this -> right = NULL;
        Tree* q = this -> left;
        int vp = this -> val, vq;
        if (q)
            vq = q -> val;
        else
            return this;
        Tree* qr = q -> right;
        q -> right = NULL;
        Tree* ql = q -> left;
        q -> left = NULL;
        this -> left = NULL;
        this -> val = vq;

        this -> insert(vp);
        this -> right -> left = qr;
        this -> right -> right = pr;
        this -> left = ql;
        this -> set_h();
        return this;
    }

    int set_h()
    {
        if (!this)
            return 0;
        this->h = max(this->left->set_h(), this->right->set_h()) + 1;
        return this->h;
    }

    int val, h;
	Tree* left;
	Tree* right;

	Tree* insert_private(int value)
    {
        Tree *node;
        if (!this)
        {
            node = new Tree;
            node->val = value;
            node->left = NULL;
            node->right = NULL;
            node->h = 1;
            return node;
        }
        if (value < this->val)
        {
            node = this->left->insert_private(value);
            if (!this->left)
                this->left = node;
            return node;
        }
        else
        {
            node = this->right->insert_private(value);
            if (!this->right)
                this->right = node;
            return node;
        }
    }
};
