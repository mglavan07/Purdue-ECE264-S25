#include "hw14.h"
#include <stdio.h>
#include <stdlib.h>

// Recursive helper to layout a single node and its subtree
static void layout_node(struct DOMNode *node, float x, float y, float width, float height, FILE *target) {
  
  // Print this node's box
  fprintf(target, "%d %.2f %.2f %.2f %.2f\n", node->id, x, y, x + width, y + height);

  // Count children
  int count = 0;
  for (struct DOMNodeList *c = node->children; c; c = c->next) {
    count++;
  }

  if (count == 0) {
    return;
  }

  // Compute margins in pixels
  float margin_x = node->margin * width;
  float margin_y = node->margin * height;

  // Inner region for children
  float inner_x = x + margin_x / 2.0f;
  float inner_y = y + margin_y / 2.0f;
  float inner_w = width - margin_x;
  float inner_h = height - margin_y;

  // Determine child size and positions
  if (node->layout_direction == LAYOUT_HORIZ) {
    float child_w = inner_w / count;
    float child_h = inner_h;
    float cx = inner_x;
    for (struct DOMNodeList *c = node->children; c; c = c->next) {
      layout_node(c->node, cx, inner_y, child_w, child_h, target);
      cx += child_w;
    }
  }
  else if (node->layout_direction == LAYOUT_VERT) {
    float child_w = inner_w;
    float child_h = inner_h / count;
    float cy = inner_y;
    for (struct DOMNodeList *c = node->children; c; c = c->next) {
      layout_node(c->node, inner_x, cy, child_w, child_h, target);
      cy += child_h;
    }
  }
  else { // LAYOUT_NONE
    for (struct DOMNodeList *c = node->children; c; c = c->next) {
      layout_node(c->node, inner_x, inner_y, inner_w, inner_h, target);
    }
  }
}

void layout(struct DOMNode *root, float width, float height, FILE *target) {
  
  // First line: window dimensions
  fprintf(target, "%.2f %.2f\n", width, height);
  // Recursively layout all nodes
  layout_node(root, 0.0f, 0.0f, width, height, target);
}

void free_DOMTree(struct DOMNode *root) {
  if (!root) return;
  // Recursively free children
  struct DOMNodeList *c = root->children;
  while (c) {
    struct DOMNodeList *next = c->next;
    free_DOMTree(c->node);
    free(c);
    c = next;
  }
  free(root);
}