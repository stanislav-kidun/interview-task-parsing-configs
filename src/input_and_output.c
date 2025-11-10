#include "input_and_output.h"

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "config_parsing_methods.h"

//////// OUTPUT ////////

const size_t MAX_INDENT_SIZE = 100;

// indent_size and indent_step are calculated in number of spaces
const size_t INDENT_STEP = 4;
size_t indent_size = 0;

FILE* output_fd = NULL;

void set_output_fd(FILE* fd) { output_fd = fd; }

void print_with_indent(char* fmt, ...) {
    if (output_fd == NULL) {
        output_fd = stdout;
    }

    char indent[MAX_INDENT_SIZE];
    memset(indent, '\0', MAX_INDENT_SIZE * sizeof(char));

    va_list list;
    va_start(list, fmt);

    // printing indent
    memset(indent, ' ', indent_size * sizeof(char));
    fprintf(output_fd, "%s", indent);

    // printing everything passed to function
    vfprintf(output_fd, fmt, list);
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
        } else {
            print_with_indent("No value:\n");
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
            print_with_indent("Atributes:\n");
            print_attr(node->attr);
        }
        print_with_indent("\n");
        if (node->child) {
            print_with_indent("Children:\n");
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

//////// INPUT ////////

// If you need to create more ways to input configs, for example from argv, I
// suggest creating more functions here, preprocess all data into char[] buffer
// and pass it to parsers.

struct node* read_config(int argc, char* argv[]) {
    if (argc == 1) {
        errno = EINVAL;
        fprintf(stderr, "No arguments provided\n");
        return NULL;
    }

    return read_config_from_file(argv[1]);
}

struct node* read_config_from_file(char* file_name) {
    FILE* read_fd = fopen(file_name, "r");
    if (!read_fd) {
        fprintf(stderr, "Failed to open file: \"%s\"\n", file_name);
        return NULL;
    }

    struct stat read_file_status;
    if (fstat(fileno(read_fd), &read_file_status)) {
        fprintf(stderr, "Failed to access file info: \"%s\"\n", file_name);
        return NULL;
    }
    size_t file_size = read_file_status.st_size;

    if (file_size == 0) {
        errno = EINVAL;
        fprintf(stderr, "File is empty: \"%s\"\n", file_name);
        return NULL;
    }

    void* mapped_file =
        mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fileno(read_fd), 0);
    if (mapped_file == MAP_FAILED) {
        fprintf(stderr, "Failed to map file: \"%s\"\n", file_name);
        return NULL;
    }

    struct node* parsed_config =
        parse_config_from_buffer((char*)mapped_file, file_size);

    fclose(read_fd);
    munmap(mapped_file, file_size);
    return parsed_config;
}
