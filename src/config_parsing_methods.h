// All functions related to parsing consfigs should be defined here
#pragma once
#include "config_structures.h"

#include <stdlib.h>

int validate_name_symbol(char symbol);
char* parse_node_name(char* starting_point, char* buff_end);
struct node* parse_config_from_buffer(char* buff, size_t buff_length);
