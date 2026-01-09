#include <gtest/gtest.h>

#include "storage_types.hpp"
#include "Package.hpp"

TEST(PackageQueueTest, queue_correctness){
Package P1 = Package(7);
Package P2 = Package(8);
Package P3 = Package(9);
PackageQueue Q1 = PackageQueue(QueueType::Lifo);
PackageQueue Q2 = PackageQueue(QueueType::Fifo);
Q1.push(P1);
Q1.push(P2);
Q1.push(P3);
Q2.push(P1);
Q2.push(P2);
Q2.push(P3);
Package Px = Q1.pop();
Package Py = Q2.pop();
ASSERT_EQ(Px,P3);
ASSERT_EQ(Py,P1);
}
