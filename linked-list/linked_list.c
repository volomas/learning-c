#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  // TODO generics? or how to support multiple types
  //  "void *"
  int data;
  Node *next;
};

typedef struct LinkedList LinkedList;
struct LinkedList {
  int size;
  Node *root;
};

LinkedList *create_linked_list() {
  return (LinkedList *)malloc(sizeof(LinkedList));
}

void append(LinkedList *list, int data) {
  Node* newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  printf("append node %p - %d\n", newNode, data);
  if (NULL == list->root) {
    list->root = newNode;
  } else {
    Node *last = list->root;
    while (NULL != last->next) {
      last = last->next;
    }
    last->next = newNode;
  }
  list->size++;
}

void prepend(LinkedList *list, int data) {
  Node *newRoot = (Node *)malloc(sizeof(Node));
  newRoot->data = data;
  printf("prepend node %p - %d\n", newRoot, data);
  newRoot->next = list->root;
  list->root = newRoot;
  list->size++;
}

int first(LinkedList *list) { 
  if (list->root == NULL) {
    return -1;
  }
  return list->root->data; }

int last(LinkedList *list) {
  Node *last = list->root;
  while (NULL != last->next) {
    last = last->next;
  }
  return last->data;
}

int get(LinkedList *list, int idx) {
  if (idx >= list->size) {
    return -1;
  }
  int count = 0;

  Node *last = list->root;
  while (count != idx) {
    last = last->next;
    count++;
  }
  return last->data;
}

int size(LinkedList *list) { return list->size; }

int removeAt(LinkedList *list, int idx) {
  if (idx >= list->size) {
    return -1;
  }

  Node *node = list->root;
  // use pointer to pointer to track prev. next pointer 
  // https://grisha.org/blog/2013/04/02/linus-on-understanding-pointers/
  Node **pp = &list->root;
  for (int i = 0; i < idx; i++) {
    pp = &node->next;
    node = node->next;
  }

  int removedItem = node->data;
  printf("remove node %p - %d\n", node, removedItem);
  *pp = node->next;
  
  list->size--;
  free(node);
  return removedItem;
}

void freeList(LinkedList *list) {
  Node* node = list->root;
  while (NULL != node) {
    Node* tmp = node;
    node = node->next;
    printf("free %p - %d\n", tmp, tmp->data);
    tmp->next = NULL;
    free(tmp);
  }
  free(list);
}

int main(int argc, char *argv[]) {
  printf("Creating new linked list\n");
  LinkedList *list = create_linked_list();
  printf("empty ll length: %d\n", size(list));
  assert(size(list) == 0);
  assert(first(list) == -1);
  assert(get(list, 0) == -1);

  append(list, 9);
  assert(size(list) == 1);

  append(list, 5);
  assert(last(list) == 5);

  append(list, 3);
  assert(size(list) == 3);
  assert(last(list) == 3);

  prepend(list, 1);
  assert(size(list) == 4);
  assert(first(list) == 1);
  assert(get(list, 0) == 1);
  assert(get(list, 1) == 9);
  assert(get(list, 3) == last(list));
  assert(get(list, 100) == -1);

  freeList(list);
  list = NULL;

  printf("test removing\n");
  LinkedList *list2 = create_linked_list();
  append(list2, 1);
  append(list2, 2);
  append(list2, 3);
  assert(size(list2) == 3);

  assert(removeAt(list2, 1) == 2);

  assert(size(list2) == 2);
  assert(get(list2, 0) == 1);
  assert(get(list2, 1) == 3);

  assert(removeAt(list2, 1) == 3);
  assert(size(list2) == 1);

  assert(removeAt(list2, 0) == 1);
  assert(size(list2) == 0);
  freeList(list2);
  list2 = NULL;
}
