#ifndef BSTCHECKER_H
#define BSTCHECKER_H
// TODO: Include any needed header files
#include "BSTNode.h"

class BSTChecker {
public:
   // TODO: Add any desired utility functions
   
   static bool HasBeenVisited(BSTNode** visited, int count, BSTNode* node) {
      for (int i = 0; i < count; i++) {
         if (visited[i] == node) {
            return true;
         }
      }
      return false;
   }
   
   static bool KeyExists(BSTNode** visited, int count, int key, BSTNode* skipNode) {
      for (int i = 0; i < count; i++) {
         if (visited[i] != skipNode && visited[i]->key == key) {
            return true;
         }
      }
      return false;
   }
   
   static BSTNode* IsValid(BSTNode* node, int* min, int* max, 
                           BSTNode** visited, int* visitCount) {
      if (node == nullptr) {
         return nullptr;
      }
      
      // Check if this node has been visited before (structural problem)
      if (HasBeenVisited(visited, *visitCount, node)) {
         return node;
      }
      
      // Check if this key already exists (duplicate key problem)
      if (KeyExists(visited, *visitCount, node->key, node)) {
         return node;
      }
      
      // Check min constraint: all nodes in right subtree must be > parent
      // So if we have a min, this node must be > min
      if (min != nullptr && node->key <= *min) {
         return node;
      }
      
      // Check max constraint: all nodes in left subtree must be < parent
      // So if we have a max, this node must be < max
      if (max != nullptr && node->key >= *max) {
         return node;
      }
      
      // Mark node as visited AFTER all checks on current node
      visited[*visitCount] = node;
      (*visitCount)++;
      
      // Preorder traversal: check left subtree first
      // Left children must be less than current node
      BSTNode* leftViolation = IsValid(node->left, min, &node->key, visited, visitCount);
      if (leftViolation != nullptr) {
         return leftViolation;
      }
      
      // Then check right subtree
      // Right children must be greater than current node
      BSTNode* rightViolation = IsValid(node->right, &node->key, max, visited, visitCount);
      if (rightViolation != nullptr) {
         return rightViolation;
      }
      
      return nullptr;
   }
   
   // CheckBSTValidty() determines if the tree is a valid BST. If so, nullptr
   // is returned. If not, the first (in preorder traversal) node in violation
   // of BST requirements is returned. Such a node will be one of the following:
   // - A node in the left subtree of an ancestor with a lesser or equal key
   // - A node in the right subtree of an ancestor with a greater or equal key
   // - A node that is encountered more than once during traversal
   static BSTNode* CheckBSTValidity(BSTNode* rootNode) {
      if (rootNode == nullptr) {
         return nullptr;
      }
      
      // Array to track visited nodes (assuming max 100000 nodes)
      BSTNode* visited[100000];
      int visitCount = 0;
      
      return IsValid(rootNode, nullptr, nullptr, visited, &visitCount);
   }
};
#endif

