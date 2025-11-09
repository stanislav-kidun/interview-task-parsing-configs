#pragma once

struct StackNode {
    struct StackNode* previous;
    struct StackNode* next;
    void* data;
};

struct SimpleStack {
    struct StackNode* top_node;
};

int add_to_stack(struct SimpleStack* stack, void* data);
void* extract_top_from_stack(struct SimpleStack* stack);
void* get_top_from_stack(struct SimpleStack* stack);

void clear_stack(struct SimpleStack* stack);