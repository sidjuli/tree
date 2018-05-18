#include <iostream>

using namespace std;

class Container
{
public:
    virtual void insert(int value) = 0;
    virtual void exists(int value) = 0;
    virtual void remove(int value) = 0;
    virtual void print() = 0;
    
    virtual ~Container(){}
}

typedef struct tree_element
{
    int value;
    struct tree_element* left;
    struct tree_element* right;
} tree_element;

class SimpleTree: public Container
{
public:
    SimpleTree();
    ~SimpleTree();
    void insert(int value) override;
    bool exists(int value) override;
    void remove(int value) override;
    void print() override;
    
protected:
    void Burn_this_tree(tree_element* root);
    tree_element* insert_into_tree(tree_element* root, tree_element* elem);
    tree_element* create_tree_element(int i);
    tree_element* search_by_value(tree_element* root, int value);
    tree_element* delete_from_tree(tree_element* root, tree_element* elem);
    tree_element* Umka(tree_element* root, tree_element* elem);
    void print_tree(tree_element* cur);
    
    tree_element* root;
}

SimpleTree::SimpleTree()
{
    this->root = NULL;
}

void SimpleTree::Burn_this_tree(tree_element* root)
{
    if ((root->left == NULL) && (root->right == NULL))
    free(root);
    else
    {
        if(root->left != NULL)
        {
            Burn_this_tree(root->left);
        }
        if (root->right != NULL)
        {
            Burn_this_tree(root->right);
        }
        
        free(root);
    }
}

SimpleTree::~SimpleTree()
{
    Burn_this_tree(this->root);
}

tree_element* SimpleTree::create_tree_element(int i)
{
    tree_element* p =(tree_element*) malloc(sizeof(tree_element));
    p->value = i;
    p->left = NULL;
    p->right = NULL;
    return p;
}

tree_element* SimpleTree::search_by_value(tree_element* root, int value)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    if (root->value == value)
    {
        return root;
    }
    
    if (value < root->value)
    {
        root = search_by_value(root->left, value);
    }
    
    if (value > root->value)
    {
        root = search_by_value(root->right, value);
    }
    return root;
}

tree_element* SimpleTree::insert_into_tree(tree_element* root, tree_element* elem)
{
    if (root == NULL)
    {
        root = elem;
        return root;
    }
    
    if (elem == NULL)
    {
        return root;
    }
    
    if (elem->value < root->value)
    {
        root->left = insert_into_tree(root->left, elem);
    }
    else
    {
        root->left = insert_into_tree(root->left, elem);
    }
    
    return root;
}

void SimpleTree::insert(int value)
{
    tree_element* elem = this->create_tree_element(value);
    
    this->root = insert_into_tree(this->root, elem);
}

void SimpleTree::print_tree(tree_element* cur)
{
    if (cur == NULL)
    {
        //printf("i can`t print toor = NULL");
    }
    else
    {
        if (cur->left != NULL)
        {
            print_tree(cur->left);
        }
        cout << cur->value << endl;
        if (cur->right != NULL)
        {
            print_tree(cur->right);
        }
    }
}

void SimpleTree::print()
{
    print_tree(this->root);
}

bool SimpleTree::exists(int value)
{
    if (search_by_value(this->root, value) != NULL)
        return 1;
    else 
        return 0;
}

tree_element* SimpleTree:Umka (tree_element* root, tree_element* elem)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    if (elem == NULL)
    {
        return NULL;
    }
    
    if ((root->left == elem) | (root->right == elem))
    {
        return root;
    }
    
    if (elem == root)
    {
        return NULL;
    }
    
    if (elem->value < root->value)
    {
        root = Umka(root->left, elem);
    }
    if (elem->value < root->value)
    {
        root = Umka(root->left, elem);
    }
    if (elem->value > root->value)
    {
        root = Umka(root->right, elem);
    }
    return root;
}

tree_element* SimpleTree::delete_from_tree(tree_element* root, tree_element* elem)
{
    if ((root == NULL) | (elem == NULL))
    {
        return root;
    }
    
    tree_element* parent = Umka(root, elem);
    if (parent == NULL)
    {
        root->right = insert_into_tree(root->right, root->left);
        tree_element* Newroot = root->right;
        
        free(root);
        return Newroot;
    }
    
    if ((elem->left == NULL) && (elem->right == NULL))
    {
        if (elem->value < parent->value)
        parent->left = NULL;
        else
        parent->right = NULL;
        
        free(elem);
        return root;
    }
    
    if (elem->value < parent->value)
    parent->left = elem->right;
    elseparent->right = elem->right;
    
    insert_into_tree(parent, elem->left);
    
    free(elem);
    return root;
    
}

void SimpleTree::remove(int value)
{
    this->root = SimpleTree::delete_from_tree(this->root, SimpleTree::search_by_value(this->root, value));
}
