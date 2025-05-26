#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * TODO: Implement all the functions in tree.h here.
 *
 * Use as many helper functions as you need, just declare them to be static.
 *
 */
// Declare static helpers
static Tree* build_tree(FILE *fptr);
static void write_preorder(Tree *node, FILE *fptr);
//static Tree *alloc_node(int data);

 // invert a tree
Tree *invert_tree(Tree *root){
  if (root == NULL) {
    return NULL;  // Base case: if the tree is empty, return NULL
  }

  // Swap the left and right subtrees
  Tree *temp = root->left;
  root->left = root->right;
  root->right = temp;

  // Recursively invert the left and right subtrees
  invert_tree(root->left);
  invert_tree(root->right);

  return root;  // Return the root of the inverted tree
}

// read a tree from a file
Tree *read_from_file(char *filename){

  FILE *fptr = fopen(filename, "rb");
  if (!fptr) {
      return NULL;
  }

  // If EOF right away, return NULL
  int byte = fgetc(fptr);
  if (byte == EOF) {
      fclose(fptr);
      return NULL;
  }

  // Go back one byte so build_tree sees it
  ungetc(byte, fptr);
  Tree *root = build_tree(fptr);
  fclose(fptr);
  return root;
}

// print the tree
void preorder_print(Tree *root, char *filename) {
  FILE *fptr = fopen(filename, "wb");
  if (fptr == NULL) {
      return;
  }

  // call helper function
  write_preorder(root, fptr);

  fclose(fptr);
  return;
}

// free the tree
void free_tree(Tree *root){
  if (root == NULL) {
    return;
  }

  // Recursively free left and right subtrees
  free_tree(root->left);
  free_tree(root->right);

  // Free the current node
  free(root);
}

static Tree *alloc_node(int data) {
  Tree *ret = calloc(1, sizeof(Tree));
  if (ret == NULL) {
    return NULL;
  }

  ret->data = data;

  return ret;
}

// iterate through the binary file 
// the binary file is a preorder traversal
// data will be read in format <int key>/<unsigned char info>
  
// unsigned char 00000001 -> right child only
// unsigned char 00000010 -> left child only
// unsigned char 00000011 -> two children

// preorder representations are root, left node, right node
// size_t fread(void *ptr, size_t size, size_t count, FILE *stream);

// Recursive helper to build tree from preorder binary file
static Tree* build_tree(FILE *fptr) {
  int data;
  unsigned char info;

  // Try to read a node; if it fails, return NULL (end of file or error)
  if (fread(&data, sizeof(int), 1, fptr) != 1) return NULL;
  if (fread(&info, sizeof(unsigned char), 1, fptr) != 1) return NULL;

  // Allocate memory for the new node using alloc_node
  Tree *node = alloc_node(data);
  if (!node){
    return NULL;
  }

  // Recursively build children based on struct byte
  if (info & 0x02) {  // Has left child
      node->left = build_tree(fptr);
  }
  if (info & 0x01) {  // Has right child
      node->right = build_tree(fptr);
  }

  return node;
}

// helper to write tree to a binary file in preorder
static void write_preorder(Tree *node, FILE *fptr) {
  if (node == NULL){
    return;
  }

  // Write node's data
  fwrite(&node->data, sizeof(int), 1, fptr);

  // Construct structure byte
  unsigned char structure = 0;
  if (node->left)  structure |= 0x02; // Bit 1
  if (node->right) structure |= 0x01; // Bit 0

  // Write structure byte
  fwrite(&structure, sizeof(unsigned char), 1, fptr);

  // Recurse into left and right children
  write_preorder(node->left, fptr);
  write_preorder(node->right, fptr);
}
