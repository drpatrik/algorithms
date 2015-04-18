// Patrik Tennberg, 2015
// Algorithm used Tortoise and hare, thought I had invented it
// but of course someone else did long before me :-)

#include <iostream>

struct Node {
  int data_;
  Node *next_;
};

Node *List_Create() {
  Node *node = new Node;

  node->data_ = 0;
  node->next_ = nullptr;

  return node;
}

Node *List_Insert(Node *node, int data) {
  if (nullptr == node) {
    return nullptr;
  }
  Node *new_node = new Node;

  new_node->data_ = data;
  new_node->next_ = nullptr;

  node->next_ = new_node;

  return new_node;
}

void List_Print(Node *root) {
  Node *node = root;

  while (nullptr != node) {
    printf("%d\n", node->data_);
    node = node->next_;
  }
}

bool HasLoop(Node *root) {
  if (!root || !root->next_) {
    return false;
  }
  Node *first = root;
  Node *second = root->next_->next_;

  while (second && second->next_) {
    if (first == second) {
      return true;
    }
    first = first->next_;
    second = second->next_->next_;
  }
  return false;
}

int main(int, char **) {
  Node *root = List_Create();

  Node *node = root;
  Node *loop = nullptr;

  for (int i = 1;i < 9;i++) {
    if (1 == i) {
      loop = node;
    }
    node = List_Insert(node, i);
  }
  node->next_ = loop;

  if (HasLoop(root)) {
    std::cout << "Yes\n";
  } else {
    std::cout << "No\n";
  }
  return 0;
}
