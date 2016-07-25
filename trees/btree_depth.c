#include <stdlib.h>
#include "tree.h"

int btree_depth(BTree *tree) 
{
   if (tree==NULL) 
       return -1;
   else
   {
       /* compute the depth of each subtree */
       int left_depth = btree_depth(tree->left);
       int right_depth = btree_depth(tree->right);
 
       /* use the larger one */
       if (left_depth > right_depth) 
           return(left_depth+1);
       else return(right_depth+1);
   }
} 
