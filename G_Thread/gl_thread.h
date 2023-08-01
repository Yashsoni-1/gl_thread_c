#ifndef gl_thread_h
#define gl_thread_h

#include <stdio.h>

typedef struct glthread_node_ {
    struct glthread_node_ *left;
    struct glthread_node_ *right;
}glthread_node_t;

typedef struct glthread_ {
    struct glthread_node_ *head;
    unsigned int offset;
}glthread_t;

void glthread_add(glthread_t *lst, glthread_node_t *glnode);
void glthread_remove(glthread_t *lst, glthread_node_t *glnode);

#define ITERATE_GL_THREADS_BEGIN(lstptr, struct_type, ptr) \
{ \
    glthread_node_t *_glnode = NULL, *_next = NULL; \
    for(_glnode = lstptr->head; _glnode; _glnode = _next) { \
    _next = _glnode->right; \
    ptr = (struct_type *) ((char *)_glnode - lstptr->offset);
#define ITERATE_GL_THREADS_END }}

#define glthread_node_init(glnode) \
glnode->right = NULL; \
glnode->left = NULL;


void init_glthread(glthread_t *glthread, unsigned int offset);


#endif /* gl_thread_h */
