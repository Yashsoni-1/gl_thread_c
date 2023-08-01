#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gl_thread.h"

#define offset_of(struct_name, field_name) \
    (uintptr_t)(&(((struct_name*)0)->field_name))

typedef struct emp_ {
    char name[30];
    unsigned int salary;
    char designation [30];
    unsigned int emp_id;
    glthread_node_t glnode;
} emp_t;

void print_emp_data(emp_t * emp)
{
    printf("Name: %s, Salary: %u, Desg: %s, emp_id: %u\n",
           emp->name, emp->salary, emp->designation, emp->emp_id);
}





int main(int argc, const char * argv[]) {
    
    emp_t *e1 = calloc(1, sizeof(emp_t));
    strcpy(e1->name, "Mercury");
    e1->salary = 1000;
    strcpy(e1->designation, "First");
    e1->emp_id = 1;
    glthread_node_init((&e1->glnode));
    
    emp_t *e2 = calloc(1, sizeof(emp_t));
    strcpy(e2->name, "Venus");
    e2->salary = 2000;
    strcpy(e2->designation, "Second");
    e2->emp_id = 2;
    glthread_node_init((&e2->glnode));
    
    emp_t *e3 = calloc(1, sizeof(emp_t));
    strcpy(e3->name, "Earth");
    e3->salary = 3000;
    strcpy(e3->designation, "Third");
    e3->emp_id = 3;
    glthread_node_init((&e3->glnode));
    
    glthread_t *emp_list = calloc(1, sizeof(glthread_t));
    init_glthread(emp_list, offset_of(emp_t, glnode));
    
    glthread_add(emp_list, &e1->glnode);
    glthread_add(emp_list, &e2->glnode);
    glthread_add(emp_list, &e3->glnode);
    
    emp_t *ptr = NULL;
    ITERATE_GL_THREADS_BEGIN(emp_list, emp_t, ptr) {
        print_emp_data(ptr);
    }ITERATE_GL_THREADS_END;
    
    
    ITERATE_GL_THREADS_BEGIN(emp_list, emp_t, ptr) {
        glthread_remove(emp_list, &ptr->glnode);
        free(ptr);
    }ITERATE_GL_THREADS_END;

    free(emp_list);
    
    
    return 0;
}
