#include "binary_tree.h"

// ***
// *** Modify this file
// ***

// The function `createNode` dynamically allocates memory for a new binary tree node and initializes its value.
// It returns a pointer to the newly created node.
TreeNode* createNode(int data) {
    // Allocate memory for a new TreeNode
    TreeNode* temp = malloc(sizeof(TreeNode));

    // Check if the allocation was successful
    if (temp == NULL){
        return NULL;
    }

    // Initialize the node's data and set its left and right children to NULL
    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;

    // Return the pointer to the new node
    return temp;
}

// This is a warmup exercise.
// In-order traversal visits the left subtree, then the current node, and finally the right subtree.
// The function `inorderTraversal` prints the data of each node in the tree in in-order.
void inorderTraversal(TreeNode* root) {
    // trap a null root
    if(root == NULL){
        return;
    }
    // move left
    if(root->left != NULL){
        inorderTraversal(root->left);
    }
    // visit the node
    printf("%d\n", root->data);
    // move right
    if(root->right != NULL){
        inorderTraversal(root->right);
    }
    return;
}

// This is a warmup exercise.
// Pre-order traversal visits the current node, then the left subtree, and finally the right subtree.
// The function `preorderTraversal` prints the data of each node in the tree in pre-order.
void preorderTraversal(TreeNode* root) {
    // trap a null root
    if(root == NULL){
        return;
    }
    // visit the node
    printf("%d\n", root->data);
    // move left
    if(root->left != NULL){
        preorderTraversal(root->left);
    }
    // move right
    if(root->right != NULL){
        preorderTraversal(root->right);
    }
    return;
}

// The function `freeTree` frees the memory allocated for the binary tree.
// It recursively frees the left and right subtrees and then frees the current node.
// Step 1: if the root is NULL, return.
// Step 2: recursively free the left and right subtrees.
// Step 3: free the current node.
void freeTree(TreeNode* root) {
    // backtrack at null nodes
    if(root == NULL){
        return;
    }

    // seek to left and right
    freeTree(root->left);
    freeTree(root->right);

    // free the node
    free(root);
}

// The function `createTree` creates a binary tree from an array representation.
// Hint: You can create a helper function to recursively build the tree.
TreeNode* buildTreeHelper(int* arr, int size, int index){
    if (index >= size || arr[index] == -1) {
        return NULL;
    }

    TreeNode* node = createNode(arr[index]);
    if (node == NULL) {
        return NULL;
    }

    node->left = buildTreeHelper(arr, size, 2 * index + 1);
    node->right = buildTreeHelper(arr, size, 2 * index + 2);

    return node;
}

// Step 1: base case, return NULL. What is the base case?
// Step 2: create a new node.
// Step 3: recursively create the left and right subtrees.
// Step 4: return the created node.
TreeNode* createTree(int* arr, int size) {
    return buildTreeHelper(arr, size, 0);
}

// trimTree function:
// Given a binary tree where each node contains a non-negative integer and two integers, `low` and `high`, 
// your task is to trim the tree such that every root-to-leaf path in the resulting tree has a sum within the inclusive range [low, high]. 
// Specifically, any *leaf* node whose path sum from the root to that leaf falls outside this range should be removed from the tree. 
// If removing a leaf node causes its parent to become a leaf and its new path sum also falls outside the valid range, that parent should be removed as well. 
// This process should continue recursively until all remaining root-to-leaf paths satisfy the constraint.
// The structure of the remaining nodes must be preserved, and the final tree must still be a valid binary tree. 
// Your function should return the root of the trimmed tree.
TreeNode* trimHelper(TreeNode* node, int sumSoFar, int low, int high){
    if (node == NULL) {
        return NULL;
    }

    int currentSum = sumSoFar + node->data;

    node->left = trimHelper(node->left, currentSum, low, high);
    node->right = trimHelper(node->right, currentSum, low, high);

    // Now a leaf (either always was or became one after trimming)
    if (node->left == NULL && node->right == NULL && (currentSum < low || currentSum > high)) {
        free(node);
        return NULL;
    }

    return node;
}

TreeNode* trimTree(TreeNode* root, int low, int high) {
    // Hint 1: You need to keep track of the sum of the path from the root to the current node. You can do this by creating a helper function.
    // Hint 2: In your helper function, check if the current node is a leaf node. If it is, check if the sum of the path from the root to this leaf node is within the range [low, high].
    // Hint 3: When you remove a node, do not forget to free the memory allocated for that node.
    return trimHelper(root, 0, low, high);
}

// The function `toBST` converts a binary tree into a binary search tree (BST) by pruning subtrees that violate BST properties. 
// The transformation must ensure that for every node:
// - All nodes in the left subtree have values less than the current node.
// - All nodes in the right subtree have values greater than the current node.
// **Restrictions**: The root node must remain unchanged. If a node's value violates BST properties relative to all its ancestors, its entire subtree is removed.
// Recursive helper to convert to BST
TreeNode* bstHelper(TreeNode* node, int minVal, int maxVal) {
    if (node == NULL) {
        return NULL;
    }

    if (node->data < minVal || node->data > maxVal) { 
        freeTree(node);  // free the entire invalid subtree
        return NULL;
    }

    node->left = bstHelper(node->left, minVal, node->data - 1);
    node->right = bstHelper(node->right, node->data + 1, maxVal);

    return node;
}

TreeNode* toBST(TreeNode* root) {
    // Hint1: You need to keep track of the minimum and maximum values allowed for each node in the tree. You can do this by creating a helper function.
    // Hint2: In your helper function, check if the current node's value is within the valid range. If it is not, remove the subtree rooted at this node.
    // Hint3: When you remove a node, do not forget to free the memory allocated for that subtree.
    if (root == NULL) {
        return NULL;
    }

    root->left = bstHelper(root->left, INT_MIN, root->data);
    root->right = bstHelper(root->right, root->data, INT_MAX);

    return root;
}