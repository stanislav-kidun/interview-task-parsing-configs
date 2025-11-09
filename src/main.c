#include <malloc.h>

#include "input_and_output.h"

void test_print_with_indent() {
    open_parentheses();
    print_with_indent("%s", "mama myla ramu\n");
    close_parentheses();
}

void test_print_node_with_single_attr() {
    struct node node;
    node.name = "Node1";
    node.attr = NULL;
    node.next = NULL;
    node.child = NULL;

    struct attr attr;
    attr.name = "Attr1";
    attr.value = "Value1";
    attr.next = NULL;

    node.attr = &attr;

    print_config(&node);
}

int main(int argc, char* argv[]) {
    // tests
    // test_print_with_indent();
    // test_print_node_with_single_attr();

    struct node* config = read_config(argc, argv);
    // struct node* config = read_config_from_file("../text.txt");
    if (config) {
        print_config(config);
    }
    free_config(config);

    return 0;
}
