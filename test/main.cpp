#include<gtest/gtest.h>
#include"../Queue.h"

TEST(QueueTest, QueueSize)
{
    Queue<int> queue(2);

    EXPECT_EQ(queue.Size(), 2);
}

TEST(QueueTest, QueueCount)
{
    Queue<int> queue(2);
    queue.Push(1);

    EXPECT_EQ(queue.Count(), 1);
}

TEST(QueueTest, QueuePushPop)
{
    Queue<int> queue(2);
    queue.Push(1);

    EXPECT_EQ(queue.Pop(), 1);
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}