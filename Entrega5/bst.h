#ifndef _BST_H
#define _BST_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>

using namespace std;

template <class T>
class BTreeNode 
{
private:
    T val;
    BTreeNode<T>* left;
    BTreeNode<T>* right;

public:
    ~BTreeNode<T>() {};
    BTreeNode<T>() {};
    BTreeNode<T>(T _val) {
        val = _val;
        left = NULL;
        right = NULL;
    };
    BTreeNode<T>(T _val, BTreeNode<T> *_left, BTreeNode<T> *_right) {
        val = _val;
        left = _left;
        right = _right;
    };

    T get_val() {return val;};
    BTreeNode<T>* get_left() {return left;};
    BTreeNode<T>* get_right() {return right;};

    void set_val(T _val) {val = _val;};
    void set_left(BTreeNode<T> * node) {left = node;};
    void set_right(BTreeNode<T> * node) {right = node;};
};

template <class T>
class BinarySearchTree
{
private:
    BTreeNode<T> *root;

public:
    ~BinarySearchTree() {};
    BinarySearchTree() { root = NULL;};


    BTreeNode<T>* find(T val)
    {
        BTreeNode<T> *ptr = root;
        while(ptr != NULL)
        {
            if (ptr->get_val() == val)
                return ptr;

            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }
        return NULL;
    };

    bool insert_node(T val)
    {
        BTreeNode<T> *ptr = root;
        BTreeNode<T> *pre = NULL;

        while(ptr != NULL)
        {
            if (ptr->get_val() == val)
                return false;
            pre = ptr;
            ptr = ptr->get_val() > val ? ptr->get_left() : ptr->get_right();
        }

        BTreeNode<T> *new_node = new BTreeNode<T>(val);

        if (pre == NULL)
            root = new_node;
        else
        {
            if (pre->get_val() < val)
                pre->set_right(new_node);
            else
                pre->set_left(new_node);            
        }
        return true;
    };

    BTreeNode<T>* insert_node_recursive(BTreeNode<T>* node, T val)
    {
        if (node == NULL)
            return new BTreeNode<T>(val);

        if (val.second < node->get_val().second)
            node->set_left(insert_node_recursive(node->get_left(), val));
        else
            node->set_right(insert_node_recursive(node->get_right(), val));

        return node;
    };

    bool insert_node_recursive(pair<string, int> val)
    {
        root = insert_node_recursive(root, val);
        return true;
    };

    BTreeNode<T>* sucessor(BTreeNode<T> *node)
    {
        BTreeNode<T> *ptr = node->get_right();
        while (ptr->get_left() != NULL)
        {
            ptr = ptr->get_left();
        }
        return ptr;        
    };

    BTreeNode<T>* delete_node(BTreeNode<T>* node, int key) 
    { 
        // caso base
        if (node == NULL) return node; 
    
        // si el valor a eliminar es menor que el valor del nodo
        // entonces está en el subarbol izquierdo
        if (key < node->get_val()) 
            node->set_left(delete_node(node->get_left(), key)); 
    
        // si el valor a eliminar es mayor que el valor del nodo
        // entonces está en el subarbol derecho
        else if (key > node->get_val()) 
            node->set_right(delete_node(node->get_right(), key)); 
    
        // si el valor a eliminar es igual que el valor del nodo
        // entonces este es el elemento que queremos eliminar
        else
        { 
            // nodos con solo un hijo o sin hijos
            if (node->get_left() == NULL) 
            { 
                BTreeNode<T> *temp = node->get_right(); 
                delete node; 
                return temp; 
            } 
            else if (node->get_right() == NULL) 
            { 
                BTreeNode<T> *temp = node->get_left(); 
                delete node;
                return temp; 
            } 
    
            // nodo con dos hijos, entonces obtener el sucesor
            BTreeNode<T> *temp = sucessor(node);
    
            // copiar el valor del sucesor al nodo que contiene el elemento a borrar
            node->set_val(temp->get_val()); 
    
            // borrar el sucesor
            node->set_right(delete_node(node->get_right(), temp->get_val()));
        } 
        return node; 
    };

    void delete_node(T val)
    {
        root = delete_node(root, val);
    };

    void print_preorder(BTreeNode<T> *node)
    {
        if (node != NULL)
        {
            cout << node->get_val().first << ": " << node->get_val().second << ", ";
            print_preorder(node->get_left());
            print_preorder(node->get_right());
        }
    };

    void print_preorder()
    {
        print_preorder(root);
        cout << endl;
    }

    void print_inorder_inv(BTreeNode<T> *node, vector<pair<string, int>> &topN)
    {
        if (node != NULL)
        {
            print_inorder_inv(node->get_right(), topN);
            topN.push_back(node->get_val());
            print_inorder_inv(node->get_left(), topN);
        }
        
    };

    void print_inorder_inv(int n, vector<pair<string, int>> &topN)
    {
        int count = 0;
        print_inorder_inv(root, topN);
        for (auto& i : topN)
        {
            if (count == n)
                break;

            cout << i.first << ": " << i.second << endl;
            count++;
        }
        cout << endl;
    }



    void recursive_variant_one(BTreeNode<T>* node, int level = 0, bool left = false, vector<bool> tabs = vector<bool>())
    {
        if (node == NULL)
            return;

        for (size_t i = 0; i < level; i++)
        {
            if (!tabs[i])
                cout << "\t";
            else
                cout << "|\t";
        }
        
        
        if (left)
            cout << "├────── " << node->get_val().first << ": " << node->get_val().second << endl;
        else
            cout << "└────── " << node->get_val().first << ": " << node->get_val().second << endl;
 
        tabs.push_back(left);
        recursive_variant_one(node->get_left(), level + 1, true, tabs);
        recursive_variant_one(node->get_right(), level + 1, false, tabs);
    }

    void recursive_variant_one()
    {
        recursive_variant_one(root);
        cout << endl;
    }
};

#endif