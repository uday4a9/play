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

// Creating QUEUE 
NODE *queue[SLIMIT];
int front=-1, rear=-1;

void insertq(NODE *tmp)
{
    if(rear == SLIMIT - 1) {
        puts("Queue full, INsertion not possible");
        return;
    }

    if(front == -1)
        front = 0;
    queue[++rear] = tmp;
}

NODE * deleteq()
{
    if(rear == -1 || front == rear+1) {
        puts("Queue empty, Nothing to remove from queue");
        return NULL;
    }
    return queue[front++];
}

int isQempty()
{
    if((front == -1 && rear == -1) || front == rear + 1)
        return 1;
    return 0;
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

int sum(NODE *root)
{
    if (root == NULL)
        return 0;
    return root->info + sum(root->left) + sum(root->right);
}

int same(NODE *root1, NODE *root2)
{
    if(root1 == NULL || root2 == NULL)
        return 0;

    return ((root1->info == root2->info) && 
           same(root1->left, root2->left) && 
           same(root1->right, root2->right));
}

int issame(NODE *root1, NODE *root2)
{
    if(root1 == NULL && root2 == NULL)
        return 999;
    if(root1 == root2) {
        puts("Both trees are same referenced");
        return 1;
    }
    return same(root1, root2);
}

int ismirror(NODE *root1, NODE *root2)
{
    if(root1 == NULL || root2 == NULL)
        return 0;
    return ((root1->info == root2->info) &&
            ismirror(root1->left, root1->right)  &&
            ismirror(root1->right, root1->left));
}

void mirror_image(NODE *root)
{
    NODE *tmp;
    if(root != NULL){
        mirror_image(root->left);
        mirror_image(root->right);
        tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    }
}

int is_sum_tree(NODE *root)
{
    //if(root == NULL)
    //    return 0;

    if ((root->info == (sum(root->left) + sum(root->right))) &&
           is_sum_tree(root->left) &&
           is_sum_tree(root->right))
        return 1;
    return 0;
}

int create_sum_tree(NODE *root)
{
    if(root == NULL)
        return 0;
    return (root->info += (create_sum_tree(root->left) + create_sum_tree(root->right)));
}

int countLeaves(NODE *root)
{
    if(root == NULL)
        return 0;
    if(root->left == NULL && root->right==NULL)
        return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

void search(NODE *root, int key)
{
    NODE *tmp;

    if(root == NULL) {
        puts("Tree empty, Nothing to search");
        return;
    } 

    tmp = root;
    while(tmp) {
        if(key < tmp->info)
            tmp = tmp->left;
        else if(key > tmp->info)
            tmp = tmp->right;
        else if(key == tmp->info) {
            puts("Element found");
            break;
        }
    }
    if(tmp == NULL)
        puts("Element not found in tree");
}

void level_order(NODE *root)
{
    NODE *tmp; 

    if(root == NULL) {
        puts("Tree empty, Nothing to print");
        return;
    }

    printf("Level order : ");
    insertq(root);
    while(!isQempty()){
        tmp = deleteq();
        printf("%4d", tmp->info);
        if(tmp->left)
            insertq(tmp->left);
        if(tmp->right)
            insertq(tmp->right);
    }
    puts("");
}

void left_view(NODE *root, int level, int *clevel)
{
    if(root == NULL)
        return;
    if(*clevel < level) {
        printf("%4d", root->info);
        *clevel += 1;
    }
    left_view(root->left, level + 1, clevel);
    left_view(root->right, level + 1, clevel);
}

void right_view(NODE *root, int level, int *clevel)
{
    if(root == NULL)
        return;
    if(*clevel < level) {
        printf("%4d", root->info);
        *clevel += 1;
    }
    right_view(root->right, level + 1, clevel);
    right_view(root->left, level + 1, clevel);
}

int freenode(NODE *root)
{
    int size;
    size = 2 * sizeof(root->left) + sizeof(int);
    free(root);
    root = NULL;
    return size;
}

int freetreesize(NODE *root)
{
    static int size = 0;

    if(root == NULL)
        return 0;

    freetreesize(root->left);
    freetreesize(root->right);
    size += freenode(root);
    return size;
}

void treeleafs(NODE *root)
{
    if(root != NULL) {
        treeleafs(root->left);
        treeleafs(root->right);
        if(!root->left && !root->right)
            printf("%4d", root->info);
    }
}

int isbst(NODE *root)
{
    static NODE *prev = NULL;
    if(root != NULL) {
        if(!isbst(root->left))
            return 0;

        if(prev != NULL && root->info < prev->info)
            return 0;

        prev = root;
        return isbst(root->right);
    }
    return 1;
}

void printarray(int *array, int index, int num)
{
    int i;
    printf("path%d : ", num);
    for(i = 0; i<index; i++)
        printf("%4d", array[i]);
    puts("");

}

void printpaths(NODE *root, int *arr, int index)
{
    static int num=0;
    if(root != NULL) {
        arr[index++] = root->info;

        printpaths(root->left, arr, index);
        printpaths(root->right, arr, index);

        if(!root->left && !root->right) {
            ++num;
            printarray(arr, index, num);
        }
    }
}

void print_element_distance(NODE *root, int dist)
{
    if(root == NULL)
        return;

    if(dist == 0)
        printf("%4d", root->info);

    print_element_distance(root->left, dist - 1);
    print_element_distance(root->right, dist - 1);
}

void levelnline(NODE *root)
{
    int maxheight, i;

    maxheight = height(root);

    for(i = 0; i < maxheight; i++) {
        printf("level %d : ", i);
        print_element_distance(root, i);
        puts("");
    }
}

int getLevel(NODE *root, int info, int level)
{
    if(root == NULL)
        return 0;

    if(root->info == info)
        return level;

    return getLevel(root->left, info, level + 1) | \
           getLevel(root->right, info, level + 1);
}

void print_tree_in_range(NODE *root, int from, int to)
{
    if(root != NULL)
    {
        print_tree_in_range(root->left, from, to);
        if(root->info >= from && root->info <= to)
            printf("%4d", root->info);
        print_tree_in_range(root->right, from, to);
    }
}

int get_level_diff(NODE *root)
{
    if(root == NULL)
        return 0;
    return root->info - get_level_diff(root->left)\
                      - get_level_diff(root->right);
}

int diameter(NODE *root)
{
    int lh, rh, ld, rd;

    if(root == NULL)
        return 0;

    lh = height(root->left);
    rh = height(root->right);

    ld = diameter(root->left);
    rd = diameter(root->right);

    return MAX(lh + rh + 1, MAX(ld, rd));
}

NODE *minvaluenode(NODE *root)
{
    while(root->left)
        root = root->left;
    return root;
}

NODE* delete_node_from_tree(NODE *root, int key)
{
    NODE *tmp;

    if(root == NULL)
        return root;

    if(key < root->info)
        root->left = delete_node_from_tree(root->left, key);
    else if(key > root->info)
        root->right = delete_node_from_tree(root->right, key);
    else {
        if(root->left && root->right) {
            // findout min v alue in given right tree to it
            tmp = minvaluenode(root->right);
            // swap the value with current
            root->info = tmp->info;
            // delte the swapped value from tree
            root->right = delete_node_from_tree(root->right, key);
        }
        else {
            tmp = root;
            if(root->left)
                root = root->left;
            else if(root->right)
                root = root->right;
            else
                root = NULL;
            free(tmp);
            tmp = NULL;
        }
    }
    return root;
}

int main(int argc, char **argv)
{
    NODE *root=NULL;
    int choice, element, rc, maxv, arr[20], dist;
    int from, to;

    while(1) {
        puts(" 0.exit");
        puts(" 1.insert");
        puts(" 2.inorder");
        puts(" 3.preorder");
        puts(" 4.postorder");
        puts(" 5.tree free");
        puts(" 6.max element");
        puts(" 7.min element");
        puts(" 8.height");
        puts(" 9.total elements in tree");
        puts("10.sum of tree");
        puts("11.same tree ?");
        puts("12.Is mirror image");
        puts("13.mirror image of a tree");
        puts("14.is sum tree");
        puts("15.count leaves");
        puts("16.Search for given element");
        puts("17.Level order traversal");
        puts("18.Views of tree");
        puts("19.free tree size");
        puts("20.Tree leafs");
        puts("21.is BST");
        puts("22.print paths to binary tree");
        puts("23.print elements in certain distance");
        puts("24.level n line");
        puts("25.get level for given element");
        puts("26.print elements in given range");
        puts("27.Get level diff");
        puts("28.diameter of given tree");
        puts("29.delete a node from tree");
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
           case 10:
                    printf("Tree sum : %d\n", sum(root));
                    break;
           case 11:
                    rc = issame(root, root->left);
                    if(rc == 1)
                        puts("Both are same");
                    else if(rc == 0)
                        puts("Both are not same");
                    else
                        puts("Both trees are empty");
           case 12:
                    rc = ismirror(root, root->left);
                    if(rc == 0)
                        puts("Not a mirror image tree");
                    else
                        puts("It's mirror image tree");
                    break;
           case 13:
                    inorder(root);
                    puts("");
                    mirror_image(root);
                    inorder(root);
                    puts("");
                    break;
           case 14:
                    inorder(root);
                    puts("");
                    create_sum_tree(root);
                    inorder(root);
                    puts("");
                    if(is_sum_tree(root) == 1)
                        puts("It's a sum tree");
                    else
                        puts("It's not a sum tree");
                    break;
           case 15:
                    printf("Count of leaves : %d\n", countLeaves(root));
                    break;
           case 16:
                    printf("Enter an element to insert in tree : ");
                    scanf("%d", &element);
                    search(root, element);
                    break;
           case 17:
                    level_order(root);
                    break;
           case 18:
                    maxv = 0;
                    printf("Left view of binary tree : ");
                    left_view(root, 1, &maxv);
                    puts("");
                    maxv = 0;
                    printf("Right view of binary tree : ");
                    right_view(root, 1, &maxv);
                    puts("");
                    break;
          case 19:
                    printf("Total free size : %d \n", freetreesize(root));
                    root = NULL;
                    break;
          case 20:
                    treeleafs(root);
                    puts("");
                    break;
          case 21:
//                    root->left->info = root->info+13;
                    if(isbst(root))
                        puts("It's BST");
                    else
                        puts("It's not BST");
                    break;
          case 22:
                    printpaths(root, arr, 0);
                    break;
          case 23:
                    printf("Enter the distance : ");
                    scanf("%d", &dist);
                    print_element_distance(root, dist);
                    puts("");
                    break;
          case 24:
                    levelnline(root);
                    break;
          case 25:
                    printf("Enter an element to get the level : ");
                    scanf("%d", &element);
                    dist = getLevel(root, element, 1);
                    if(dist > 0)
                        printf("Element %d occurs at level %d\n", element, dist);
                    else
                        puts("Element not available in the list");
                    break;
          case 26:
                    printf("Enter two elements range : ");
                    scanf("%d%d", &from, &to);
                    print_tree_in_range(root, from, to);
                    puts("");
                    break;
          case 27:
                    rc = get_level_diff(root);
                    printf("Diff is : %d \n", rc);
                    break;
          case 28:
                    dist = diameter(root);
                    printf("Diameter of given tree : %d\n", dist);
                    break;
          case 29:
                    printf("Enter an element to be deleted from tree : ");
                    scanf("%d", &element);
                    root = delete_node_from_tree(root, element);
                    inorder(root);
                    break;
        }
    }

    return 0;
}
