// Patrik Tennberg, 2015
// Algorithms from "Introduction to Algorithms, 3ed"

#include <iostream>
#include <vector>

template <typename T>
class Node {
 public:
  Node() = default;
  ~Node() = default;

  std::shared_ptr<Node>& left() { return left_; }
  std::shared_ptr<Node>& right() { return right_; }
  void set_data(const T& data) { data_ = std::make_shared<T>(data); }
  bool has_data() const { return data_ != nullptr; }
  const T& get_data() { return *data_.get(); }
  bool has_left_link() const { return left_ != nullptr; }
  void make_left_link() { left_ = std::make_shared<Node>(); }
  bool has_right_link() const { return right_ != nullptr; }
  void make_right_link() { right_ = std::make_shared<Node>(); }

 private:
  std::shared_ptr<Node<T>> left_;
  std::shared_ptr<Node<T>> right_;
  std::shared_ptr<T> data_;
};

template <typename T>
class BinaryTree {
 public:
  BinaryTree() = default;
  BinaryTree(const std::initializer_list<T>& data) {
    for (auto& v : data) {
      Insert(v);
    }
  }
  ~BinaryTree() = default;

  void Insert(const T& data) { Insert(root_, data); }
  void VisitPreOrder() { VisitPreOrder(root_); }
  void VisitPreOrderIterative() { VisitPreOrderIterative(root_); }
  void VisitInOrder() { VisitInOrder(root_); }
  void VisitInOrderIterative() { VisitInOrderIterative(root_); }
  void VisitPostOrder() { VisitPostOrder(root_); }
  void VisitPostOrderIterative() { VisitPostOrderIterative(root_); }

 protected:
  void Insert(std::shared_ptr<Node<T>> node, const T& data) {
    if (!node->has_data()) {
      node->set_data(data);
      return;
    }
    if (data < node->get_data()) {
      if (!node->has_left_link()) {
        node->make_left_link();
      }
      Insert(node->left(), data);
    } else if (data > node->get_data()) {
      if (!node->has_right_link()) {
        node->make_right_link();
      }
      Insert(node->right(), data);
    }
  }

  void VisitPreOrder(std::shared_ptr<Node<T>> node) {
    if (node == nullptr) {
      return;
    }
    std::cout << node->get_data() << '\n';
    VisitPreOrder(node->left());
    VisitPreOrder(node->right());
  }

  void VisitPreOrderIterative(std::shared_ptr<Node<T>> node) {
    std::vector<std::shared_ptr<Node<T>>> stack;

    while (!stack.empty() || node) {
      if (node) {
        std::cout << node->get_data() << '\n';
        if (node->has_right_link()) {
          stack.push_back(node->right());
        }
        node = node->left();
      } else {
        node = stack.back();
        stack.pop_back();
      }
    }
  }

  void VisitInOrder(std::shared_ptr<Node<T>> node) {
    if (!node) {
      return;
    }
    VisitInOrder(node->left());
    std::cout << node->get_data() << '\n';
    VisitInOrder(node->right());
  }

  void VisitInOrderIterative(std::shared_ptr<Node<T>> node) {
    std::vector<std::shared_ptr<Node<T>>> stack;

    while (!stack.empty() || node) {
      if (node) {
        stack.push_back(node);
        node = node->left();
      } else {
        node = stack.back();
        stack.pop_back();
        std::cout << node->get_data() << '\n';
        node = node->right();
      }
    }
  }

  void VisitPostOrder(std::shared_ptr<Node<T>> node) {
    if (!node) {
      return;
    }
    VisitPostOrder(node->left());
    VisitPostOrder(node->right());
    std::cout << node->get_data() << '\n';
  }

  void VisitPostOrderIterative(std::shared_ptr<Node<T>> node) {
    std::vector<std::shared_ptr<Node<T>>> stack;

    std::shared_ptr<Node<T>> peek_node;
    std::shared_ptr<Node<T>> last_not_visited;

    while (!stack.empty() || node) {
      if (node) {
        stack.push_back(node);
        node = node->left();
      } else {
        peek_node = stack.back();

        if (peek_node->has_right_link() &&
            peek_node->right() != last_not_visited) {
          node = peek_node->right();
        } else {
          std::cout << peek_node->get_data() << '\n';
          last_not_visited = stack.back();
          stack.pop_back();
        }
      }
    }
  }

 private:
  std::shared_ptr<Node<T>> root_ = std::make_shared<Node<T>>();
};

int main(int, char* []) {
  BinaryTree<int> in_order{20, 9, 15, 11, 5, 53, 79};
  BinaryTree<int> pre_order{20, 9, 15, 11, 5, 53, 79};
  BinaryTree<int> post_order{20, 9, 15, 11, 5, 53, 79};

  std::cout << "In order\n";
  in_order.VisitInOrderIterative();
  std::cout << "Pre order\n";
  pre_order.VisitPreOrder();
  std::cout << "Post order\n";
  post_order.VisitPostOrder();

  return 0;
}
