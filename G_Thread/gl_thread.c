//
//  gl_thread.c
//  G_Thread
//
//  Created by Yash soni on 01/08/23.
//

#include "gl_thread.h"
#include <stdio.h>
#include <stdlib.h>


static void _glthread_add_next(glthread_node_t *curr_node, glthread_node_t *new_node)
{
    if(!curr_node->right) {
        curr_node->right = new_node;
        new_node->left = curr_node;
        return;
    }
    
    glthread_node_t *temp = curr_node->right;
    curr_node->right = new_node;
    new_node->left = curr_node;
    new_node->right = temp;
    temp->left = new_node;
}

void glthread_add(glthread_t *lst, glthread_node_t *glnode)
{
    glnode->left = NULL;
    glnode->right = NULL;
    
    if(!lst->head) {
        lst->head = glnode;
        return;
    }
    
    glthread_node_t *head = lst->head;
    _glthread_add_next(glnode, head);
    lst->head = glnode;
}

void _remove_glthread_node(glthread_node_t *glnode)
{
    if(!glnode) return;
    
    if(!glnode->left) {
        if(glnode->right) {
            glnode->right->left = NULL;
            glnode->right = NULL;
            return;
        }
        
        return;
    }
    
    if(!glnode->right) {
        glnode->left->right = NULL;
        glnode->left = NULL;
        return;
    }
    
    
    glnode->left->right = glnode->right;
    glnode->right->left = glnode->left;
    glnode->left = NULL;
    glnode->right = NULL;
}


void glthread_remove(glthread_t *lst, glthread_node_t *glnode)
{
    glthread_node_t *head = lst->head;
    
    if(head == glnode) {
        lst->head = head->right;
    }
    
    _remove_glthread_node(glnode);
}

void init_glthread(glthread_t *glthread, unsigned int offset)
{
    glthread->head = NULL;
    glthread->offset = offset;
}





