// All config structures should be defined here

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
