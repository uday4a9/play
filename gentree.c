#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
    This is the general tree program. In BST each node resticted to haven only two childs.
Here it can have many childs. So, It folow linked list kind of mechanism in each level.
            ______________________
           |first | info | next   |
           |node  |      | sibling|            <+++++++ ROOT NODE, It'll be not having any siblings
           ------------------------
            |
            |
            |
            ______________________
           |first | info | next   |
           |node  |      | sibling|            <+++++++ First level of tree or linked lists
           ------------------------

           This Hierarchial things all follows as mentioned above manne
*/

typedef struct node {
    struct node *first;
    int info;
    struct node *next;
}NODE;

NODE *create_node(int info)
{
    NODE *new;
    
    new = (NODE*) malloc(sizeof(NODE));
    assert(new != NULL);

    new->info = info;
    new->first = NULL;
    new->next = NULL;

    return new;
}

NODE *insert(NODE *root, int first, int sibl)
{
    if(root == NULL) {
        nn = create_node(first);
        root = nn;
        return root;
    }


}


int main(int argc, char **argv)
{
    NODE *nn;
    NODE *root = NULL;
    int choice;
    int created=0;
    int first, sibl = -999;

    while(1) {
        puts("0. exit");
        puts("1. insert")
        
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                    exit(0);
            case 1:
                    if(!created) {
                        printf("Enter root element to create a base tree : ");
                        scanf("%d", &first);
                        created = 1;
                    }
                    else {
                        puts("**** Enter <root> <sibling> node details ****");
                        printf("Enter root and sibling node details : ");
                        scanf("%d %d", &first, &sibl);
                    }
                    root = insert(root, first, sibl);
                    break;
        }
    }

    printf("%d", nn->info);

    return 0;
}
