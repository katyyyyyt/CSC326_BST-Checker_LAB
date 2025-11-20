#ifndef BSTCHECKER_H
#define BSTCHECKER_H

// TODO: Include any needed header files
#include "BSTNode.h"



class BSTChecker {
public:
   // TODO: Add any desired utility functions

    static BSTNode* FindDuplicate(BSTNode* node, int key, BSTNode* skip) {
        if (node == nullptr) {
            return nullptr;
        }

        // Found duplicate (but not the same node we're checking)
        if (node->key == key && node != skip) {
            return node;
        }

        // Search left subtree
        BSTNode* leftDup = FindDuplicate(node->left, key, skip);
        if (leftDup != nullptr) {
            return leftDup;
        }

        // Search right subtree
        return FindDuplicate(node->right, key, skip);
    }

    static BSTNode* IsValid(BSTNode* node, int* min, int* max, BSTNode* root) {
        if (node == nullptr) {
            return nullptr;
        }

        // Check min constraint
        if (min != nullptr && node->key <= *min) {
            return node;
        }

        // Check max constraint
        if (max != nullptr && node->key >= *max) {
            return node;
        }
        // Check for duplicates in entire tree
        if (FindDuplicate(root, node->key, node) != nullptr) {
            return node;
        }

        // Check left subtree (preorder)
        BSTNode* leftViolation = IsValid(node->left, min, &node->key, root);
        if (leftViolation != nullptr) {
            return leftViolation;
        }

        // Check right subtree
        BSTNode* rightViolation = IsValid(node->right, &node->key, max, root);
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
      // TODO: Type your code here (remove placeholer line below)

       //Base case:
       if (rootNode == nullptr)
       {
           return nullptr;
       }
       
       return IsValid(rootNode, nullptr, nullptr, rootNode);

   }
};

#endif
