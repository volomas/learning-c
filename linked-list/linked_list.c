#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  //TODO generics? or how to support multiple types
  // "void *"
  int data;
  Node *next;
};

typedef struct LinkedList LinkedList;
struct LinkedList {
  int size;
  Node *root;
};

LinkedList* create_linked_list() {
  return (LinkedList*) malloc(sizeof(LinkedList));
}

void append(LinkedList *list, int data) {
  if (NULL == list->root) {
    list->root = (Node*)malloc(sizeof(Node));
    list->root->data = data;
  } else {
    Node* last = list->root;
    while (NULL != last->next) {
      last = last->next;
    }
    last->next = (Node*)malloc(sizeof(Node));
    last->next->data = data;
  }
  list->size++;
}

void prepend(LinkedList *list, int data) {}

// TODO what if linked list is empty?
int first(LinkedList *list) { 
  return list->root->data; 
}

int last(LinkedList *list) {
  Node *last = list->root;
  while (NULL != last->next) {
    last = last->next;
  }
  return last->data;
}

int get(LinkedList *list, int idx) { return 0; }

int size(LinkedList *list) { return list->size; }

void removeAt(LinkedList *list, int idx) {}

void removeItem(LinkedList *list, int data) {}

int main(int argc, char *argv[]) {
  printf("Creating new linked list\n");
  LinkedList *list = create_linked_list();
  printf("empty ll length: %d\n", size(list));
  assert(size(list) == 0);

  append(list, 9);
  assert(size(list) == 1);

  append(list, 5);
  assert(last(list) == 5);

  append(list, 3);
  assert(size(list) == 3);
  assert(last(list) == 3);


  //TODO test prepend
  // prepend(list, 1);
  // assert(size(list) == 4);
  // assert(first(list) == 4);
  // assert(get(list, 1) == 9);
}