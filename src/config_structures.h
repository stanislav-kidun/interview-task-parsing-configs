// All config structures should be defined here
#pragma once

struct attr {
    char* name;
    char* value;
    struct attr* next;
};

struct node {
    char* name;
    struct attr* attr;
    struct node* next;
    struct node* child;
};

void free_config();
