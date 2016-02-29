#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
    int item;
    struct node *next;
} NODE;

NODE* create_node(int item)
{
    NODE *new;

    new = (NODE*) malloc(sizeof(NODE));

    if(new == NULL) {
        puts("malloc failed");
        exit(1);
    }
    new->item = item;
    new->next = NULL;

    return new;
}

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

NODE* insert_at_end(NODE *root, int info)
{
    NODE *nn, *tmp;

    nn = create_node(info);

    if(root == NULL)
	return nn;

    tmp = root;
    // traverse till end of the list
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = nn;
    return root;
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

NODE* delete_at_end(NODE *root)
{
    NODE *cur, *prv=NULL;

    if(root == NULL) {
        puts("List empty, Nothing to delete");
	return root;
    }

    if(root->next == NULL) {
        free(root);  
	root = NULL; 
	return root;
    }

    cur = root;
    while(cur->next != NULL) {
        prv = cur;
	cur = cur->next;
    }
    prv->next = NULL;  

    free(cur);
    cur = NULL;

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


NODE* insert_at_any_pos(NODE *root, int pos, int item)
{
    int i = 1;
    NODE *new, *nxt, *prv;

    if(pos < 0) {
        puts("Invalid -ve position");
        return root;
    }

    new = create_node(item);

    if(pos==1 && root==NULL) {
        root = new;
        return root;
    }

    if(pos==1) {
        new->next = root;
        root = new;
        return root;
    }

    nxt = root;
    while(i < pos) {
        prv = nxt;
        if(prv == NULL) {
            puts("Invalid postion, Beyond the size");
            free(new);
            new = NULL;
            return root;
        }
        nxt = prv->next;
        i += 1;
    }
    prv->next = new;
    new->next = nxt;

    return root;
}

NODE* delete_at_any_pos(NODE *root, int pos)
{
    int i=1;
    NODE *prv, *tmp, *cur;
    if(pos < 0) {
        puts("Invalid -ve position");
        return root;
    }

    if(root == NULL) {
        puts("List empty, Nothing to delete");
        return root;
    }

    if(pos==1 && root->next==NULL){
        free(root);
        root = NULL;
        return root;
    }

    if(pos==1){
        tmp = root;
        root = root->next;
        free(tmp);
        tmp = NULL;
        return root;
    }

    cur = root;
    while(i < pos) {
        prv = cur;
        cur = cur->next;
        if(cur == NULL) {
            puts("Deletion not possibe, Beyond position");
            return root;
        }
        i += 1;
    }
    prv->next = cur->next;
    cur->next = NULL;
    free(cur);
    cur = NULL;

    return root;
}

void freelist(NODE *root)
{
    NODE *tmp;

    if(root == NULL)
        return;
    while(root != NULL) {
        tmp = root;
        root = root->next;

        free(tmp);
        tmp = NULL;
    }
}

int maxloc(NODE *root, int element)
{
    NODE *tmp;
    int index=0, maxindex=-1;

    if(root == NULL) {
        puts("List empty, max elemnt can't be determined");
        return;
    }

    tmp = root;
    while(tmp != NULL) {
        index += 1;

        if(tmp->item == element)
            maxindex = index;

        tmp = tmp->next;
    }

    return maxindex;
}

int main()
{
    NODE *front = NULL, *tmp;
    int ch, item, pos, ret;

    while(1) {
        puts("0. exit");
        puts("1. Insert at beginning");
        puts("2. delete at beginning");
        puts("3. display");
        puts("4. Insert at end");
        puts("5. delete at end");
        puts("6. insert at any position");
        puts("7. delete at any position");
        puts("8. maxloc of an element");

        printf("Enter one among abobve choices : ");
        scanf("%d", &ch);

        switch(ch) {
            case 0: 
                    freelist(front);
                    puts("Freed the whole memory");
                    exit(1);
            case 1: 
                    printf("Enter an item to insert in sll: ");
                    scanf("%d", &item);
                    front = insert_at_begin(front, item);
                    display(front);
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
                    front = insert_at_end(front, item);
                    display(front);
                    break;
            case 5: 
                    front = delete_at_end(front);
                    display(front);
                    break;
            case 6:
                    printf("Enter the element to be inserted: ");
                    scanf("%d", &item);
                    printf("Enter the position to insert:");
                    scanf("%d", &pos);
                    front = insert_at_any_pos(front, pos, item);
                    display(front);
                    break;
            case 7:
                    printf("Enter the position to delete:");
                    scanf("%d", &pos);
                    front = delete_at_any_pos(front, pos);
                    display(front);
                    break;
            case 8:
                    printf("Element needs to be searched in list : ");
                    scanf("%d", &item);
                    pos = maxloc(front, item);
                    if(pos == -1)
                        puts("Given element is not available in list");
                    else
                        printf("Element %d max location is : %d\n", item, pos);
                    break;
        }
    }
    return 0;
}
