// All input-processing methods and utilities for parsing preporation as well as
// all output methods should be defined here. If there will be too much methods,
// files can be splitted.
#pragma once

#include <stdio.h>

#include "configs_structure.h"

void print_with_indent(char* fmt, ...);

void open_parentheses();
void close_parentheses();

void print_attr_data(struct attr* attr);
void print_attr(struct attr* attr);
void print_node_data(struct node* node);
void print_node(struct node* node);
void print_config(struct node* starting_node);