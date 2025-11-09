#include "config_parsing_methods.h"

#include <stdlib.h>
#include <string.h>

#include "config_structures.h"

int validate_name_symbol(char symbol) {
    return (symbol >= '0' && symbol <= '9') ||
           (symbol >= 'a' && symbol <= 'z') ||
           (symbol >= 'A' && symbol <= 'Z') || symbol == '_';
}

char* parse_name(char* starting_point, char* buff_end) {
    size_t name_size = 0;
    for (; starting_point + name_size != buff_end &&
           validate_name_symbol(*(starting_point + name_size));
         ++name_size);

    char* name = (char*)calloc(name_size + 1, sizeof(char));
    memcpy(name, starting_point, name_size);
    return name;
}

// value parsing could be done in one function, but i decided to split it in two
// so the condition will not become really heavy and hard to read

char* parse_value_with_spaces(char* starting_point, char* buff_end) {
    size_t value_size = 0;
    int is_protected_symbol = 0;
    for (; starting_point + value_size != buff_end &&
           !(*(starting_point + value_size) == '\'' ||
             *(starting_point + value_size) == '\"' && !is_protected_symbol);
         ++value_size) {

        if (*(starting_point + value_size) == '\\') {
            is_protected_symbol = 1;
        } else {
            is_protected_symbol = 0;
        }
    }

    char* value = (char*)calloc(value_size + 1, sizeof(char));
    memcpy(value, starting_point, value_size);
    return value;
}

char* parse_value_without_spaces(char* starting_point, char* buff_end) {
    size_t value_size = 0;
    for (; starting_point + value_size != buff_end &&
           *(starting_point + value_size) != ' ';
         ++value_size);

    char* value = (char*)calloc(value_size + 1, sizeof(char));
    memcpy(value, starting_point, value_size);
    return value;
}

struct node* parse_config_from_buffer(char* buff, size_t buff_length) {
    if (!buff) {
        return NULL;
    }
    char* buff_end = buff + buff_length;

    // start_node is reterning node. It indicates start of the chain
    // TODO: process situations when no nodes passed in config, so no memory
    // must be initialised, errno setted and error writed to stderr
    struct node* start_node = NULL;

    struct node* current_node = NULL;
    struct node* previous_node = NULL;

    struct attr* current_attr = NULL;
    struct attr* previous_attr = NULL;

    int is_opened_node = 0;

    char* pointer = buff;
    while (pointer != buff_end) {
        switch (*pointer) {
            case '[':
                current_node = (struct node*)calloc(1, sizeof(struct node));
                if (start_node == NULL) {
                    start_node = current_node;
                    previous_node = current_node;
                } else {
                    // TODO: if there are opened nodes, make this one child,
                    // else make this one next
                }

                ++pointer;
                current_node->name = parse_name(pointer, buff_end);
                pointer += strlen(current_node->name);
                break;
            case ']':
                // TODO: need to make parent node current. The easy way is to
                // add parent field in node structure. The hard one is to
                // create stack with nodes
                break;
            case 'a':
                // we have found attribute and start parsing it
                current_attr = (struct attr*)calloc(1, sizeof(struct attr));

                if (!current_node->attr) {
                    current_node->attr = current_attr;
                    previous_attr = current_attr;
                } else {
                    previous_attr->next = current_attr;
                    previous_attr = current_attr;
                }
                current_attr->name = parse_name(pointer, buff_end);
                pointer += strlen(current_attr->name);

                // its possible for attributes to have no value, so we need to
                // check if there '=' symbol
                if (*pointer == '=') {
                    ++pointer;
                    if ((*pointer == '\'') || (*pointer == '\"')) {
                        ++pointer;
                        current_attr->value =
                            parse_value_with_spaces(pointer, buff_end);
                    } else {
                        current_attr->value =
                            parse_value_without_spaces(pointer, buff_end);
                    }
                    pointer += strlen(current_attr->value);
                }
                break;
            default:
                // skipping spaces and unknow symbols
                ++pointer;
                break;
        }
    }

    return start_node;
}
