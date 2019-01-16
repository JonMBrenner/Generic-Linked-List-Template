#ifndef LINKED_LIST_JMB_H_
#define LINKED_LIST_JMB_H_

#include <cstddef>
#include <string>

namespace jmb {
class LinkedList {
  public:
    LinkedList() = default;
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    ~LinkedList();

    bool empty() const;
    int size() const;
    void append_front(std::string data);
    void append_back(std::string data);
    void remove(std::size_t index);
    std::string& operator[](std::size_t index);
    const std::string& operator[](std::size_t index) const;
    bool operator==(const LinkedList& other) const;
    bool operator!=(const LinkedList& other) const;

  private:
    struct Node {
      std::string data_;
      Node* next_{};
    };
    Node* head_{};
    std::size_t size_{};
};
}

#endif
