#include "input_and_output.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

const unsigned int MAX_INDENT_SIZE = 100;
// indent_size and indent_step are calculated in number of spaces
const unsigned int INDENT_STEP = 4;
unsigned int indent_size = 0;

void print_with_indent(char* fmt, ...) {
    char indent[MAX_INDENT_SIZE];
    memset(indent, '\0', MAX_INDENT_SIZE * sizeof(char));

    va_list list;
    va_start(list, fmt);

    // printing indent
    memset(indent, ' ', indent_size * sizeof(char));
    printf("%s", indent);

    // printing everything passed to function
    vprintf(fmt, list);
    va_end(list);
}

void open_parentheses() {
    print_with_indent("{\n");
    indent_size += INDENT_STEP;
}

void close_parentheses() {
    if (indent_size > 0) {
        indent_size -= INDENT_STEP;
        print_with_indent("}\n");
    }
}

void print_attr_data(struct attr* attr) {
    if (attr) {
        print_with_indent("Attribute name: %s\n", attr->name);
        open_parentheses();
        if (attr->value) {
            print_with_indent("Attribute value: %s\n", attr->value);
        }
        close_parentheses();
    }
}

void print_attr(struct attr* attr) {
    if (attr) {
        print_attr_data(attr);
        if (attr->next) {
            print_attr(attr->next);
        }
    }
}

void print_node_data(struct node* node) {
    if (node) {
        print_with_indent("Node name: %s\n", node->name);
        open_parentheses();
        if (node->attr) {
            print_attr(node->attr);
        }
        if (node->child) {
            print_node(node->child);
        }
        close_parentheses();
    }
}

void print_node(struct node* node) {
    if (node) {
        print_node_data(node);
        if (node->next) {
            print_node(node->next);
        }
    }
}

void print_config(struct node* starting_node) {
    open_parentheses();
    print_node(starting_node);
    close_parentheses();
}