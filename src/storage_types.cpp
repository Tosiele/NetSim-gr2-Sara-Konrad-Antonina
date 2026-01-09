#include <iostream>
#include "storage_types.hpp"

void return_queue_type(QueueType t) {
    switch (t) {
        case QueueType::Fifo:
            std::cout << "fifo" << std::endl;
        break;
        case QueueType::Lifo:
            std::cout << "lifo" << std::endl;
        break;
        default:
            throw std::invalid_argument("Invalid QueueType");
        break;
    }
}

Package PackageQueue::pop() {
  if (qt == QueueType::Fifo) {
      Package p = packages.pop_front();
  }
  else if (qt == QueueType::Lifo) {
      Package p = packages.pop_back();
  }
  else {
    throw std::invalid_argument("Invalid QueueType");
  }
  }

void PackageQueue::push( Package&& p) {
  packages.push_front(p);
}