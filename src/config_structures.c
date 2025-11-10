#include "config_structures.h"

#include <stdlib.h>

void free_node(struct node* node) {
    if (node) {
        free_attr(node->attr);
        free_node(node->child);
        free_node(node->next);
        if (node->name) {
            free(node->name);
        }
        free(node);
    }
}

void free_attr(struct attr* attr) {
    if (attr) {
        free_attr(attr->next);
        if (attr->name) {
            free(attr->name);
        }
        if (attr->value) {
            free(attr->value);
        }
        free(attr);
    }
}
