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
  if (NULL == list->root) {
    list->root = (Node *)malloc(sizeof(Node));
    list->root->data = data;
  } else {
    Node *last = list->root;
    while (NULL != last->next) {
      last = last->next;
    }
    last->next = (Node *)malloc(sizeof(Node));
    last->next->data = data;
  }
  list->size++;
}

void prepend(LinkedList *list, int data) {
  Node *newRoot = (Node *)malloc(sizeof(Node));
  newRoot->data = data;
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

void removeAt(LinkedList *list, int idx) {}

void removeItem(LinkedList *list, int data) {}

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
}
