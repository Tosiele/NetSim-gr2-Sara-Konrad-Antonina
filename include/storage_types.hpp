//
// Created by konfe on 07.01.2026.
//

#ifndef STORAGE_TYPES_HPP
#define STORAGE_TYPES_HPP
#include <iostream>
#include <list>
#include "Package.hpp"
  enum class QueueType {
    Fifo, Lifo
};

void return_queue_type(QueueType t);

class IPackageStockpile {
  public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual void push(Package&& p) = 0;
    virtual ~IPackageStockpile() = default;

    virtual const_iterator begin() =0;
    virtual const_iterator end() =0;
    virtual const const_iterator cbegin() const =0;
    virtual const const_iterator cend() const =0;

    virtual const unsigned long long size() const =0;
    virtual const bool empty() const =0;
};

class IPackageQueue : public IPackageStockpile {
  public:
    virtual Package pop() = 0;
    virtual const void get_queue_type() =0;
    virtual ~IPackageQueue() {}
};

class PackageQueue : public IPackageQueue {
  public:
    explicit PackageQueue(const QueueType t) : qt(t) { qt = t; }
    Package pop() override;
    void push(Package&& p) override;

  const void get_queue_type()override { return return_queue_type(qt); }

  const_iterator begin()  override { return packages.begin(); }
  const_iterator end()  override { return packages.end(); }
  const const_iterator cbegin() const override { return packages.cbegin(); }
  const const_iterator cend() const override { return packages.cend(); }

  const unsigned long long size() const override { return packages.size(); }
  const bool empty() const override { return packages.empty(); }
  private:
    QueueType qt;
    std::list<Package> packages;
};


#endif //STORAGE_TYPES_HPP
