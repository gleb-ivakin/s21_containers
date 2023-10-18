#include <queue>

#include "../sources/s21_list_like_class.cc"
#include "../sources/s21_queue.cc"
#include "gtest/gtest.h"

using namespace s21;

// ------- Queue Functions -------

TEST(Queue_Functions, default_constructor) {
  queue<int> test_queue;
  EXPECT_EQ(test_queue.size(), 0);
}

TEST(Queue_Functions, initializer_list_constructor) {
  queue<int> test_queue{1, 2, 3, 4, 5, 6, 7};

  for (int i = 1; test_queue.front(); i++) {
    EXPECT_EQ(i, test_queue.front());
    test_queue.pop();
  }

  // пустая очередь
  queue<int> null_queue{};
  EXPECT_EQ(null_queue.size(), 0);
}

TEST(Queue_Functions, copy_constructor) {
  queue<int> copy_queue{1, 2, 3, 4, 5, 6, 7};
  queue<int> test_queue = copy_queue;

  std::queue<int> std_queue;

  for (int i = 1; i <= 7; i++) {
    std_queue.push(i);
  }

  while (test_queue.front()) {
    EXPECT_EQ(test_queue.front(), std_queue.front());
    test_queue.pop();
    std_queue.pop();
  }

  EXPECT_EQ(test_queue.size(), std_queue.size());

  // копирование пустой очереди
  queue<int> null_queue;
  std::queue<int> null_std_queue;
  queue<int> test_queue_2 = null_queue;
  std::queue<int> std_queue_2 = null_std_queue;

  EXPECT_EQ(test_queue_2.front(), std_queue_2.front());
  EXPECT_EQ(test_queue_2.size(), std_queue_2.size());
  // стандартный back() сегается на пуcтой очереди, поэтому его не сравниваем
  // EXPECT_EQ(test_queue_2.back(), std_queue_2.back());
}

TEST(Queue_Functions, move_constructor) {
  queue<int> moving_queue{1, 2, 3, 4, 5, 6, 7};
  queue<int> test_queue = std::move(moving_queue);

  std::queue<int> moving_std_queue;
  for (int i = 1; i <= 7; i++) {
    moving_std_queue.push(i);
  }
  std::queue<int> std_queue = std::move(moving_std_queue);

  EXPECT_EQ(test_queue.front(), std_queue.front());
  EXPECT_EQ(test_queue.back(), std_queue.back());
  EXPECT_EQ(test_queue.size(), std_queue.size());

  EXPECT_EQ(moving_queue.size(), moving_std_queue.size());

  // перемещение пустой очереди
  queue<int> null_queue;
  queue<int> test_queue_2 = std::move(null_queue);
  std::queue<int> null_std_queue;
  std::queue<int> std_queue_2 = std::move(null_std_queue);

  EXPECT_EQ(test_queue_2.size(), std_queue_2.size());
}

TEST(Queue_Functions, assignment_operator_overload) {
  queue<int> test_queue;
  test_queue = {1};
  test_queue.pop();

  test_queue = {1, 2, 3};
  std::queue<int> std_queue;
  for (int i = 1; i <= 3; i++) {
    std_queue.push(i);
  }

  queue<int> test_queue_2 = {1, 2, 3, 4, 5};
  test_queue_2 = std::move(test_queue);
  std::queue<int> std_queue_2;
  for (int i = 1; i <= 5; i++) {
    std_queue_2.push(i);
  }
  std_queue_2 = std::move(std_queue);

  while (test_queue.front()) {
    EXPECT_EQ(test_queue.front(), std_queue.front());
    test_queue.pop();
    std_queue.pop();
  }

  EXPECT_EQ(test_queue_2.front(), std_queue_2.front());
  EXPECT_EQ(test_queue_2.back(), std_queue_2.back());
  EXPECT_EQ(test_queue_2.size(), std_queue_2.size());
}

// ------- Queue Element access -------

TEST(Queue_Elemets_access, front_back) {
  queue<int> test_queue = {1, 2, 3, 4, 5, 6, 7};
  std::queue<int> std_queue;
  for (int i = 1; i <= 7; i++) {
    std_queue.push(i);
  }
  EXPECT_EQ(test_queue.front(), std_queue.front());
  EXPECT_EQ(test_queue.back(), std_queue.back());

  // пустая очередь
  queue<int> test_queue_2;
  std::queue<int> std_queue_2;
  EXPECT_EQ(test_queue_2.size(), std_queue_2.size());
}

// ------- Queue Capacity -------

TEST(Queue_Capacity, empty) {
  queue<int> test_queue = {0, 1, 2, 3, 4, 5};
  std::queue<int> std_queue;
  for (int i = 1; i <= 5; i++) {
    std_queue.push(i);
  }
  EXPECT_EQ(test_queue.empty(), std_queue.empty());

  // пустая очередь
  queue<int> test_queue_2;
  std::queue<int> std_queue_2;
  EXPECT_EQ(test_queue_2.empty(), std_queue_2.empty());
}

// ------- Queue Modifiers -------

TEST(Queue_Modifiers, push) {
  queue<int> test_queue = {0, 1, 2, 3, 4, 5};
  std::queue<int> std_queue;
  for (int i = 1; i <= 5; i++) {
    std_queue.push(i);
  }

  test_queue.push(350);
  std_queue.push(350);
  while (test_queue.front()) {
    EXPECT_EQ(test_queue.front(), std_queue.front());
    test_queue.pop();
    std_queue.pop();
  }

  // вставка в пустую очередь
  queue<int> test_queue_2;
  std::queue<int> std_queue_2;
  test_queue_2.push(350);
  std_queue_2.push(350);
  EXPECT_EQ(test_queue_2.front(), std_queue_2.front());
  EXPECT_EQ(test_queue_2.back(), std_queue_2.back());
}

TEST(Queue_Modifiers, pop) {
  queue<int> test_queue = {0, 1, 2, 3, 4, 5};
  std::queue<int> std_queue;
  for (int i = 0; i <= 5; i++) {
    std_queue.push(i);
  }

  test_queue.pop();
  std_queue.pop();
  while (test_queue.front()) {
    EXPECT_EQ(test_queue.front(), std_queue.front());
    test_queue.pop();
    std_queue.pop();
  }

  // удаление из пустой очереди
  queue<int> test_queue_2;
  std::queue<int> std_queue_2;
  test_queue_2.pop();
  std_queue_2.pop();
}

TEST(Queue_Modifiers, swap) {
  queue<int> q1 = {1, 2, 3};
  queue<int> q2 = {4, 5, 6, 7};
  q1.swap(q2);

  std::queue<int> std_q1;
  for (int i = 1; i <= 3; i++) {
    std_q1.push(i);
  }
  std::queue<int> std_q2;
  for (int i = 4; i <= 7; i++) {
    std_q2.push(i);
  }
  std_q1.swap(std_q2);

  while (q1.front()) {
    EXPECT_EQ(q1.front(), std_q1.front());
    q1.pop();
    std_q1.pop();
  }

  while (q2.front()) {
    EXPECT_EQ(q2.front(), std_q2.front());
    q2.pop();
    std_q2.pop();
  }

  // пустая очередь
  queue<int> q3;
  std::queue<int> std_q3;
  queue<int> q4 = {1, 2, 3};
  std::queue<int> std_q4;
  for (int i = 1; i <= 3; i++) {
    std_q4.push(i);
  }
  q3.swap(q4);
  std_q3.swap(std_q4);

  while (q3.front()) {
    EXPECT_EQ(q3.front(), std_q3.front());
    q3.pop();
    std_q3.pop();
  }

  // двe пустых очереди
  queue<int> q5;
  std::queue<int> std_q5;
  q5.swap(q4);
  std_q5.swap(std_q4);
}

// int main(int argc, char **argv)
// {
//   ::testing::InitGoogleTest(&argc, argv);
//   std::cout << "Running tests:" << std::endl;
//   int ret{RUN_ALL_TESTS()};
//   if (!ret)
//     std::cout << "Well done." << std::endl;
//   else
//     std::cout << "Fail." << std::endl;
//   return 0;
// }
