#pragma once

#include <stdlib.h>
struct StackNode {
    struct StackNode* previous;
    struct StackNode* next;
    void* data;
};

struct SimpleStack {
    struct StackNode* top_node;
};

int add_to_stack(struct SimpleStack* stack, void* data) {
    if (!stack) {
        return -1;
    }

    struct StackNode* stack_node =
        (struct StackNode*)calloc(1, sizeof(struct StackNode));
    stack_node->data = data;
    if (stack->top_node) {
        stack->top_node->next = stack_node;
        stack_node->previous = stack->top_node;
    }
    stack->top_node = stack_node;

    return 0;
}

void* extract_top_from_stack(struct SimpleStack* stack) {
    if (stack) {
        if (stack->top_node) {
            struct node* extracted_data = stack->top_node->data;

            struct StackNode* new_top_node = stack->top_node->previous;
            free(stack->top_node);

            if (new_top_node) {
                new_top_node->next = NULL;
            }
            stack->top_node = new_top_node;
            return extracted_data;
        }
    }
    return NULL;
}

void* get_top_from_stack(struct SimpleStack* stack) {
    if (stack) {
        if (stack->top_node) {
            return stack->top_node->data;
        }
    }
}
