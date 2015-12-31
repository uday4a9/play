#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct {
    char name[20];
    int id;
} s, *sptr = &s; 

typedef struct node {
    int item;
    struct node *next;
} NODE;

NODE* insert_at_begin(NODE *tmp, int item)
{
    NODE *new;
    new = malloc(sizeof(NODE));
    if (new == NULL){
        puts("malloc failed");
        exit(1);
    }
    new->item = item;
    new->next = NULL;

    if(tmp == NULL)
        tmp = new;
    else {
        new->next = tmp;
        tmp = new;
    }
    return tmp;
}

NODE* delete_at_begin(NODE *root)
{
    NODE *tmp;
    if (root == NULL) {
        //puts("List empty Nothing to delete");
        return root;
    }
    else {
        tmp = root;
        root = root->next;

        tmp->next = NULL;
        free(tmp);
        tmp = NULL;
    }
    return root;
}

void display(NODE *front)
{
    NODE *tmp;

    tmp = front;
    while(tmp != NULL) {
        printf(" %d -> ", tmp->item);
        tmp = tmp->next;
    }
    puts("NULL");
}

NODE* insert_at_end_rec(NODE *root, int item)
{
    NODE *new;
    if (root == NULL){
        new = malloc(sizeof(NODE));
        if (new == NULL){
            puts("malloc failed");
            exit(1);
        }
        new->item = item;
        new->next = NULL;
        return new;
    }
    else {
        root->next = insert_at_end_rec(root->next, item);
        return root;
    }
}

NODE* delete_at_end_rec(NODE *root)
{
    NODE *new;
    if (root == NULL){
        return root;
    }
    else if(root->next == NULL) {
        free(root);
        root = NULL;
        return root;
    }
    else {
        root->next = delete_at_end_rec(root->next);
        return root;
    }
}

int main()
{
    NODE *front = NULL;
    int ch, item;

    while(1) {
        puts("0. exit");
        puts("1. Insert at beginning");
        puts("2. delete at beginning");
        puts("3. display");
        puts("4. Insert at end");
        puts("5. delete at end");

        printf("Enter one among abobve choices : ");
        scanf("%d", &ch);

        switch(ch) {
            case 0: 
                    puts("Bye.. Bye..");
                    exit(1);
            case 1: 
                    printf("Enter an item to insert in sll: ");
                    scanf("%d", &item);
                    front = insert_at_begin(front, item);
                    break;
            case 2: 
                    front = delete_at_begin(front);
                    display(front);
                    break;
            case 3:
                    display(front);
                    break;
            case 4: 
                    printf("Enter an item to insert in sll: ");
                    scanf("%d", &item);
                    front = insert_at_end_rec(front, item);
                    break;
            case 5: 
                    front = delete_at_end_rec(front);
                    display(front);
                    break;
        }
    }
    return 0;
}
