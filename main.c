#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node{
    int value;
    struct node* prev;
    struct node* next;
}NODE;

struct linked_list{
    NODE* first_node;
    NODE* last_node;
    int list_size;
};


NODE* new_node(int value){
    NODE* node = malloc(sizeof(struct node));
    node->next = NULL;
    node->prev = NULL;
    node->value = value;
    return node;
}


void add_node(struct linked_list* list, NODE* node){
    if (!list->first_node){
        list->first_node = list->last_node = node;
    } else {
        list->last_node->next = node;
        node->prev = list->last_node;
        list->last_node = node;
    }
    list->list_size++;
}


void swap_nodes(struct linked_list* list, NODE* left, NODE* right){
    NODE* prev;
    NODE* next;
    /* swap their prevs and nexts*/

    int back_to_back = left->next == right;

    prev = right->prev;
    right->prev = left->prev;
    
    next = left->next;
    left->next = right->next;

    if (back_to_back){
        left->prev = right;
        right->next = left;
    } else{
        left->prev = prev;
        right->next = next;
    }
    

    /*  update preceding and following nodes, front and tail  */
    if(left->next){
        left->next->prev = left;
    } else{
        list->last_node = left;
    }

    if(right->next){
        right->next->prev = right;
    } else{
        list->last_node = right;
    }

    if(left->prev){
        left->prev->next = left;
    } else{
        list->first_node = left;
    }

    if(right->prev){
        right->prev->next = right;
    } else{
        list->first_node = right;
    }
}



void output_list(struct linked_list* list){
    NODE* node = list->first_node;
    while(node){
        printf("%d\n", node->value);
        node = node->next;
    }

}


void quick_sort_list(struct linked_list* list, NODE* start, NODE* end){
    if (start == end || end == NULL || start == NULL || end == start->prev){
        return;
    }
    NODE* left = start;
    NODE* right = end->prev;
    NODE* end_next = end->next;   /*  To determine the last element of the subarray   */
    int pivot = end->value;

    while (left != right && right != left->prev){
        if (left->value >= pivot && right->value >= pivot){
            /*  left will need do move, but right will stay */
            right = right->prev;
        } else if (left->value >= pivot){
            /*  They need to swap   */
            if (left == start){
                start = right;  /*  Do not lose the start   */
            }
            left = left->next;
            right = right->prev;
            swap_nodes(list, left->prev, right->next);
        } else if(left->value < pivot && right->value < pivot){
            /*  Left will stay and right needs to move  */
            left = left->next;
        } else{
            /*  They both need to move  */
            left = left->next;
            right = right->prev;
        }
    }

    /*  Put pivot to its place  */
    if (left->value >= pivot){
        swap_nodes(list, left, end);
        if (left == start){
            start = NULL;   /*  we don't want the left part to be processed in the next iteration   */
        }
    } else{
        swap_nodes(list, right->next, end);
    }

    /*  sort right and and left of the pivot    */
    quick_sort_list(list, start, end->prev);
    if (end_next){
        quick_sort_list(list, end->next, end_next->prev);
    } else{
        quick_sort_list(list, end->next, list->last_node);
    }

}



int main(int argc, char* args[]) {
    struct linked_list list;
    list.first_node = NULL;
    list.last_node = NULL;
    list.list_size = 0;

    add_node(&list, new_node(134));
    add_node(&list, new_node(3));
    add_node(&list, new_node(7));
    add_node(&list, new_node(8));
    add_node(&list, new_node(32));
    add_node(&list, new_node(8));
    add_node(&list, new_node(10));
    add_node(&list, new_node(126));
    add_node(&list, new_node(71));

    output_list(&list);
    printf("\nAfter sorting\n");
    quick_sort_list(&list, list.first_node, list.last_node);
    output_list(&list);

    return 0;
}