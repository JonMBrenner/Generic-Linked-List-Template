#ifndef LINKED_LIST_JMB_H_
#define LINKED_LIST_JMB_H_

#include <cstddef>
#include <stdexcept>

namespace jmb {
template <typename T>
class LinkedList {
  public:
    LinkedList() = default;

    LinkedList(const LinkedList& other)
      : head_{new Node{other.head_->data_, other.head_->next_}}
      , size_{other.size_} {
      Node* cur = head_;
      Node* cur_other = other.head_;
      for (std::size_t i = 1; i < size_; ++i) {
        cur_other = cur_other->next_;
        cur->next_ = new Node{cur_other->data_, cur_other->next_};
        cur = cur->next_;
      }
      tail_ = cur;
    }

    LinkedList& operator=(const LinkedList& other) {
      if (this == &other) {
        return *this;
      }
      this->destroy();
      size_ = other.size_;
      head_ = new Node{other.head_->data_, other.head_->next_};
      Node* cur = head_;
      Node* cur_other = other.head_;
      for (std::size_t i = 1; i < size_; ++i) {
        cur_other = cur_other->next_;
        cur->next_ = new Node{cur_other->data_, cur_other->next_};
        cur = cur->next_;
      }
      tail_ = cur;
      return *this;
    }

    ~LinkedList() {
      this->destroy();
    }

    bool empty() const {
      return !size_;
    }

    int size() const {
      return size_;
    }

    void append_front(T data) {
      if (this->empty()) {
        head_ = new Node{data, nullptr};
        tail_ = head_;
      } else {
        head_ = new Node{data, head_};
      }
      ++size_;
    }

    void append_back(T data) {
      if (this->empty()) {
        head_ = new Node{data, nullptr};
        tail_ = head_;
      } else {
        tail_->next_ = new Node{data, nullptr};
        tail_ = tail_->next_;
      }
      ++size_;
    }

    //void remove(std::size_t index);

    T& operator[](std::size_t index) {
      if (this->empty() || index > size_-1) {
        throw std::out_of_range("index out of range");
      }
      Node* cur = head_;
      for (std::size_t i = 0; i < index; ++i) {
        cur = cur->next_;
      }
      return cur->data_;
    }

    const T& operator[](std::size_t index) const {
      if (this->empty() || index > size_-1) {
        throw std::out_of_range("index out of range");
      }
      Node* cur = head_;
      for (std::size_t i = 0; i < index; ++i) {
        cur = cur->next_;
      }
      return cur->data_;
    }

    //bool operator==(const LinkedList& other) const;
    //bool operator!=(const LinkedList& other) const;

  private:
    struct Node {
      T data_;
      Node* next_{};
    };
    Node* head_{};
    Node* tail_{};
    std::size_t size_{};

    void destroy() {
      Node* cur = head_;
      Node* next;
      for (std::size_t i = 0; i < size_; ++i) {
        next = cur->next_;
        delete cur;
        cur = next;
      }
    }
};
}

#endif
