// In computer science, a binary tree is a tree data structure in which each node 
// has at most two children, referred to as the left child and the right child. 
// That is, it is a k-ary tree with k = 2. A recursive definition using set theory 
// is that a binary tree is a tuple (L, S, R), where L and R are binary trees or 
// the empty set and S is a singleton set containing the root.
//
// A rooted binary tree has a root node and every node has at most two children.
// A full binary tree (sometimes referred to as a proper, plane, or strict binary tree)
// is a tree in which every node has either 0 or 2 children. 
// Another way of defining a full binary tree is a recursive definition. 
// A full binary tree is either:
//      A single vertex (a single node as the root node).
//      A tree whose root node has two subtrees, both of which are full binary trees.
// A perfect binary tree is a binary tree in which all interior nodes have two children 
// and all leaves have the same depth or same level (the level of a node defined as the 
// number of edges or links from the root node to a node).

#include <iostream>
#include <stack>
#include <map>

struct Node {
    int data;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> left;
    Node(int i_data)
    {
        this->data = i_data;
    };
};

typedef std::shared_ptr<Node> NodePtr;

// For traversing a (non-empty) binary tree in an inorder fashion, 
// we must do these three things for every node n starting from the 
// tree’s root:
// (L) Recursively traverse its left subtree. When this step is finished, 
//      we are back at n again.
// (N) Process n itself.
// (R) Recursively traverse its right subtree. 
// When this step is finished, we are back at n again.

void inorderRecursive(NodePtr node) {
    if (!node) return;
    
    inorderRecursive(node->left);
    
    std::cout << node->data << " ";

    inorderRecursive(node->right);  
};

void inorderIterative(NodePtr node) {
    std::stack<NodePtr> stack;

    NodePtr curr = node;

    while(!stack.empty() || curr != nullptr)
    {
        if (!curr)
        {
            stack.push(curr);

            curr = curr->left;
        } else {
            curr = stack.top();
            stack.pop();
    
            std::cout << curr->data << " ";

            curr = curr->right;
        }
        
    }
};

// For traversing a (non-empty) binary tree in a preorder fashion,
// we must do these three things for every node n starting from the tree’s root:
// (N) Process n itself.
// (L) Recursively traverse its left subtree. When this step is finished, 
//      we are back at n again.
// (R) Recursively traverse its right subtree. 
// When this step is finished, we are back at n again.

void preorderRecursive(NodePtr node) {
    if (!node) return;

    std::cout << node->data << " ";
 
    preorderRecursive(node->left);
    

    preorderRecursive(node->right);
};

void preorderIterative(NodePtr node) {
    if (!node) return;
    std::stack<NodePtr> stack;
    stack.push(node);

    while(!stack.empty())
    {
        NodePtr curr = stack.top();
        stack.pop();
 
        std::cout << curr->data << " ";

        if (curr->right)
        {
            stack.push(curr->right);
        }
        if (curr->left) {
            stack.push(curr->left);
        }
        
    }
};

// For traversing a (non-empty) binary tree in a postorder fashion, 
// we must do these three things for every node n starting from the tree’s root:
// (L) Recursively traverse its left subtree. 
// When this step is finished, we are back at n again.
// (R) Recursively traverse its right subtree. 
// When this step is finished, we are back at n again.
// (N) Process n itself.

void postorderRecursive(NodePtr node) {
    if (node == nullptr) return;
    
    inorderRecursive(node->left);

    inorderRecursive(node->right);

    std::cout << node->data << " ";
};

void postorderIterative(NodePtr node) {
    if (!node) return;
    std::stack<NodePtr> stack;
    stack.push(node);

    std::stack<int> out;

    while(!stack.empty())
    {
        NodePtr curr = stack.top();
        stack.pop();

        out.push(curr->data);

        if (curr->left) {
            stack.push(curr->left);
        }

        if (curr->right) {
            stack.push(curr->right);
        }
    }

    while(!out.empty()) {
        std::cout << out.top() << " ";
        out.pop();
    }
};

// Two binary trees are identical if they have identical structure and their 
// contents are also the same.
int isIdentical(NodePtr x, NodePtr y) {
    if (!x && !y) return 1;
    
    return (x && y) && (x->data == y->data) 
      && isIdentical(x->left, y->left) && isIdentical(x->right, y->right);
}

void printBottom(NodePtr node, int dist, int level, std::map<int, std::pair<int, int>>& map)
{
    if (!node) return;

    if (level >= map[dist].second)
    {
       map[dist] = { node->data, level}; 
    }
    
    printBottom(node->left, dist - 1, level + 1, map);

    printBottom(node->right, dist + 1, level + 1, map);
    
}

void printBottom(NodePtr root) 
{
    // create an empty map where
    // key —> relative horizontal distance of the node from the root node, and
    // value —> pair containing the node's value and its level
    
    std::map<int, std::pair<int, int>> map;

    // perform preorder traversal on the tree and fill the map
    printBottom(root, 0, 0, map);
 
    // traverse the map and print the bottom view
    for (auto it: map) {
        std::cout << it.second.first << " ";
    }
}

void printTop(NodePtr node, int dist, int level, std::map<int, std::pair<int, int>>& map)
{
    if (!node) return;

    if (map.find(dist) == map.end() || level < map[dist].second)
    {
        map[dist] = { node->data, level};
    }

    printTop(node->left, dist - 1, level + 1, map);
    printTop(node->right, dist + 1, level + 1, map);
}

void printTop(NodePtr root)
{
    std::map<int, std::pair<int, int>> map;
    
    printTop(root, 0, 0, map);
 
    for (auto it: map) {
        std::cout << it.second.first << " ";
    } 
}

int sumPostorder(NodePtr node) {
    if (!node) return 0;
    int leftSum = sumPostorder(node->left);
    int rightSum = sumPostorder(node->right);
    int prevData = node->data;
    node->data = leftSum + rightSum;
    return node->data + prevData; 
};

// - Determine whether the given binary tree nodes are cousins of each other



// - Print cousins of a given node in a binary tree
// - Check if a binary tree is a sum tree or not
// - Given a set of single-digit positive numbers, find all possible combinations
// of words formed by replacing the continuous digits with corresponding 
// character in the English alphabet, i.e., subset {1} can be replaced by A, 
// {2} can be replaced by B, {1, 0} can be replaced by J, 
// {2, 1} can be replaced by U, etc.
// - Find the diameter of a binary tree
// - Check if a binary tree is symmetric or not
// - Convert a binary tree to its mirror
// - Find the Lowest Common Ancestor (LCA) of two nodes in a binary tree
// - Print all paths from the root to leaf nodes of a binary tree
// - Find distance between given pairs of nodes in a binary tree
// - Find the diagonal sum of a binary tree
// - Truncate a binary tree to remove nodes that lie on a path having a sum less than `k`
// - Convert a binary tree into a doubly-linked list in spiral order
// - Invert Binary Tree
// - Depth-First Search (DFS) vs Breadth-First Search (BFS)
// - Find the minimum depth of a binary tree
// - Compute the maximum number of nodes at any level in a binary tree
// - Store words in a binary tree
//
int main()
{
    std::printf("Test binaryTree\n");

    /* Construct the following tree
               1
             /   \
            /     \
           2       3
          /      /   \
         /      /     \
        4      5       6
              / \
             /   \
            7     8
    */

    auto root = std::make_shared<Node>(1);
    root->left = std::make_shared<Node>(2);
    root->right = std::make_shared<Node>(3);
    root->left->left = std::make_shared<Node>(4);
    root->right->left = std::make_shared<Node>(5);
    root->right->right = std::make_shared<Node>(6);
    root->right->left->left = std::make_shared<Node>(7);
    root->right->left->right = std::make_shared<Node>(8);

    inorderRecursive(root); //4, 2, 1, 7, 5, 8, 3, 6
    // inorderIterative(root);
    // preorderRecursive(root); //1, 2, 4, 3, 5, 7, 8, 6
    // preorderIterative(root);
    // postorderRecursive(root); //4, 2, 7, 5, 8, 3, 6, 1
    // postorderIterative(root);
    // if (isIdentical(root, root)) {
    //     std::cout << "The given binary trees are identical";
    // }
    // else {
    //     std::cout << "The given binary trees are not identical";
    // }
    // printBottom(root); // 4 7 5 8 6
    // printTop(root); // 4 2 1 3 6
    // std::cout << "\n" << sumPostorder(root) << " \n"; // 0 4 35 0 15 0 26 0
    // inorderRecursive(root);

    return 0;
}
