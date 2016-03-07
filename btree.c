#include <stdio.h>
#include <assert.h>
#include <stdlib.h> 

#define MAX(a, b) (a > b ? a : b)
#define SLIMIT 100

struct node {
    struct node *left;
    int info;
    struct node *right;
};

typedef struct node NODE;

// Need to create a stack and do perform operations on that
NODE *stack[SLIMIT];
int top=-1; // stack top value

void push(NODE *tmp)
{
    if(top == SLIMIT - 1) {
        puts("Stack OVERFLOW");
        return;
    }
    stack[++top] = tmp;
}

NODE *pop()
{
    if(top == -1){
        puts("Stack UNDERFLOW");
        return NULL;
    }

    return stack[top--];
}

void display()
{
    int i=0;

    if(top == -1) {
        puts("Stack empty");
        return;
    }

    printf("Stack : ");
    for(i=0; i<=top; i++)
        printf(" %4d |", stack[i]->info);
    puts("");
}

int isempty()
{
    return top == -1;
}

int isfull()
{
    return top == SLIMIT-1;
}

NODE* peek()
{
    return stack[top];
}

NODE* create_node(int info)
{
    NODE *new;
    new = malloc(sizeof(NODE));

    if(new == NULL) {
        puts("malloc failed");
        exit(1);
    }
    new->right = NULL;
    new->info = info;
    new->right = NULL;

    return new;
}

NODE* insert(NODE *root, int info)
{
    NODE *nn;
    if(root == NULL)
        root = create_node(info);
    else if(info < root->info)
        root->left = insert(root->left, info);
    else
        root->right = insert(root->right, info);
    return root;
}

void inorder(NODE *root)
{
    if(root != NULL) {
        inorder(root->left);
        printf("%3d", root->info);
        inorder(root->right);
    }
}

void inorder_nrec(NODE *root)
{
    // L N R - way of accessing
    NODE *tmp, *cur;

    cur = root;
    if(cur == NULL) {
        puts("Empty tree, Nothing to print");
        return;
    }

    printf("Inorder non- recursive : ");
    while(1)
    {
        // Need to insert the all left side nodes.
        if(cur != NULL) {
            push(cur);
            cur = cur->left;
        }
        else{
            if(!isempty()) {
                // If there is any right node exist, again put all left nodes in stack
                tmp = pop();
                printf("%4d", tmp->info);
                cur = (tmp->right != NULL) ? tmp->right : NULL;
            }
            else
                break;
        }
    }
    puts("");
}

void preorder(NODE *root)
{
    if(root != NULL) {
        printf("%3d", root->info);
        preorder(root->left);
        preorder(root->right);
    }
}

void preorder_nrec(NODE *root)
{
    NODE *tmp, *cur;

    if(root == NULL) {
        puts("Tree empty, Nothing to print");
        return;
    }

    cur = root;
    push(cur);

    printf("pre order non-recursive : ");
    while(!isempty()) {
        tmp = pop();
        printf("%4d", tmp->info);
        if(tmp->right != NULL)
            push(tmp->right);
        if(tmp->left != NULL)
            push(tmp->left);
    }
    puts("");
}

void postorder(NODE *root)
{
    if(root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%3d", root->info);
    }
}

void postorder_nrec(NODE *root)
{
    NODE *cur, *tmp;

    if(root == NULL) {
        puts("Tree empty, nothing to print");
        return;
    }

    printf("post order non-recursive : ");
    cur = root;
    do {
        while(cur) {
            if(cur->right)
                push(cur->right);
            push(cur);
            cur = cur->left;
        }

        tmp = pop();

        if(tmp->right && tmp->right == peek()) {
            cur = pop();
            //printf("%4d", cur->info);
            push(tmp);
            cur = tmp->right;
        }
        else {
            printf("%4d", tmp->info);
            cur = NULL;
        }
    } while(!isempty());

}

NODE* free_tree(NODE *root)
{
    if(root == NULL)
        return root;

    root->left = free_tree(root->left);
    root->right = free_tree(root->right);
    free(root);
    root = NULL;
    return root;
}

void max(NODE *root)
{
    NODE *tmp;
    
    if(root == NULL) {
        puts("Emtpy tree, Max can't findout");
        return;
    }

    tmp = root;
    while(tmp->right != NULL)
        tmp = tmp->right;
    printf("Max element in given BST is : %d\n", tmp->info);
}

void min(NODE *root)
{
    NODE *tmp;
    
    if(root == NULL) {
        puts("Emtpy tree, Min can't findout");
        return;
    }

    tmp = root;
    while(tmp->left != NULL)
        tmp = tmp->left;
    printf("Min element in given BST is : %d\n", tmp->info);
}

int height(NODE *root)
{
    if(root == NULL)
        return 0;
    return 1 + MAX(height(root->left), height(root->right));
}

int total(NODE *root)
{
    if(root == NULL)
        return 0;
    return 1 + total(root->left) + total(root->right);
}

int main(int argc, char **argv)
{
    NODE *root=NULL;
    int choice, element;

    while(1) {
        puts("0.exit");
        puts("1.insert");
        puts("2.inorder");
        puts("3.preorder");
        puts("4.postorder");
        puts("5.tree free");
        puts("6.max element");
        puts("7.min element");
        puts("8.height");
        puts("9.total");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        system("clear");
        switch(choice){
            case 0: 
                    root = free_tree(root);
                    puts("Exiting from the program");
                    exit(0);
//                    break;
            case 1:
                    printf("Enter an element to insert in tree : ");
                    scanf("%d", &element);
                    root = insert(root, element);
                    break;
            case 2:
                    printf("inorder :");
                    inorder(root);
                    puts("");
                    inorder_nrec(root);
                    puts("");
                    break;
            case 3:
                    printf("preorder :");
                    preorder(root);
                    puts("");
                    preorder_nrec(root);
                    break;
            case 4:
                    printf("postorder :");
                    postorder(root);
                    puts("");
                    postorder_nrec(root);
                    puts("");
                    break;
            case 5:
                    puts("Clearing the list");
                    root = free_tree(root);
                    exit(0);
                    //break;
           case 6:
                    max(root);
                    break;
           case 7:
                    min(root);
                    break;
           case 8:
                    printf("Height : %d \n",height(root));
                    break;
           case 9:
                    printf("Total elements in tree : %d \n", total(root));
                    break;
        }
    }

    return 0;
}
