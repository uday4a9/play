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

NODE *reverse(NODE *root)
{
    NODE *cur, *nxt, *prv=NULL;

    cur = root;
    while(cur != NULL) {
        nxt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nxt;
    }
    return prv;
}

NODE *reversen_rec(NODE *root, NODE *prv)
{
    if(root->next == NULL) {
        // Here returning the root always always the entire function
        // returns the last element address.
        root->next = prv;
        return root;
    }
    else {
        NODE *tmp;
        tmp = reversen_rec(root->next, root);
        root->next = prv;
        return tmp;
    }
}

NODE *reverse_rec(NODE *root)
{
    if(root == NULL)
        return root;
    return reversen_rec(root, NULL);
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

NODE* delete_nth_elem_from_end(NODE *root, int n)
{
    NODE *last, *prv, *cur;
    int i=0;

    if(root == NULL) {
        puts("There are no elements in the list, Operation is not permissable");
        return root;
    }

    if( n <= 0) {
        puts("Deletion not possible, as n is -ve");
        return root;
    }

    last = root;
    while(i < n) {
        if(last == NULL) {
            printf("position %d is beyond the size of linked list\n", n);
            return root;
        }
        last = last->next; 
        i++;
    }

    cur = root;
    while(last != NULL) {
        prv = cur;
        cur = cur->next;
        last = last->next;
    }

    // If list contains only n no. of elements, It should treat as special case
    // as deleting the first element

    if(cur == root)
        root = root->next;
    else
        prv->next = cur->next;
    cur->next = NULL;
    free(cur);
    cur = NULL;

    return root;
}

int is_palindrome(NODE **front, NODE *last)
{
    if(last == NULL)
        return 1;

    int i = is_palindrome(front, last->next);

    int j = ((*front)->item == last->item);

    *front = (*front)->next;

    return j;
}

void check_cycle(NODE *root)
{
    NODE *slow, *fast;

    if(!root) {
        puts("List Empty, Nothing to perform");
        return;
    }

    slow = root;
    fast = slow->next;

    while(1) {
        if(!fast || !fast->next){
            puts("No cycles found");
            break;
        }
        else if(slow==fast || fast->next==slow){
            printf("Cycle found %d at %d\n", slow->item, fast->item);
            break;
        }
        else {
            slow = slow->next;
            fast = fast->next->next;
        }
    }
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
        puts("8. reversing list");
        puts("9. Is Palindrome");
        puts("10. delete nth element from end");
        puts("11. check cycles in list");

        printf("Enter one among abobve choices : ");
        scanf("%d", &ch);
        system("clear");

        switch(ch) {
            case 0: 
                    freelist(front);
                    puts("Freed the whole memory");
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
            case 6:
                    printf("Enter the element to be inserted: ");
                    scanf("%d", &item);
                    printf("Enter the position to insert:");
                    scanf("%d", &pos);
                    front = insert_at_any_pos(front, pos, item);
                    break;
            case 7:
                    printf("Enter the position to delete:");
                    scanf("%d", &pos);
                    front = delete_at_any_pos(front, pos);
                    break;
            case 8:
                    //front = reverse(front);
                    front = reverse_rec(front);
                    display(front);
                    break;
            case 9:
                    tmp = front;
                    is_palindrome(&front, front) ? puts("PALINDROME") : puts("NOT PALINDROME");
                    front = tmp;
                    display(front);
            case 10:
                    printf("Enter which position from end to be deleted:");
                    scanf("%d", &pos);
                    front = delete_nth_elem_from_end(front, pos);
                    display(front);
                    break;
            case 11:
                    // Establish the cycles
                    //front->next = front;
                    printf("Check whether given list is ciruclar or not ? : ");
                    scanf("%d", &pos);
                    if(pos)
                        check_cycle(front);
                    else
                        puts("Enter other than zero to perform this operation");
                    break;
        }
    }
    return 0;
}
