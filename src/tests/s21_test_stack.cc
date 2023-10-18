#include <stack>

#include "../sources/s21_list_like_class.cc"
#include "../sources/s21_stack.cc"
#include "gtest/gtest.h"

using namespace s21;

// ------- Stack Functions -------

TEST(Stack_Functions, default_constructor) {
  stack<int> test_stack;
  EXPECT_EQ(test_stack.size(), 0);
}

TEST(Stack_Functions, initializer_list_constructor) {
  stack<int> test_stack{1, 2, 3, 4, 5, 6, 7};

  for (int i = 1; test_stack.top(); i++) {
    EXPECT_EQ(i, test_stack.top());
    test_stack.pop();
  }

  // пустой стэк
  stack<int> null_stack{};
  EXPECT_EQ(null_stack.size(), 0);
}

TEST(Stack_Functions, copy_constructor) {
  stack<int> copy_stack{1, 2, 3, 4, 5, 6, 7};
  stack<int> test_stack = copy_stack;

  std::stack<int> std_stack;
  for (int i = 7; i >= 1; i--) {
    std_stack.push(i);
  }

  while (test_stack.top()) {
    EXPECT_EQ(test_stack.top(), std_stack.top());
    test_stack.pop();
    std_stack.pop();
  }

  //   копирование пустого стэка
  stack<int> null_stack;
  stack<int> test_stack_2 = null_stack;

  // стандартный пустой стэк сегается при попытке доступа к top() или size(),
  // поэтому его здесь не используем
  EXPECT_EQ(test_stack_2.top(), 0);
  EXPECT_EQ(test_stack_2.size(), 0);
}

TEST(Stack_Functions, move_constructor) {
  stack<int> moving_stack{1, 2, 3, 4, 5, 6, 7};
  stack<int> test_stack = std::move(moving_stack);

  std::stack<int> moving_std_stack;
  for (int i = 7; i >= 1; i--) {
    moving_std_stack.push(i);
  }
  std::stack<int> std_stack = std::move(moving_std_stack);

  EXPECT_EQ(test_stack.top(), std_stack.top());
  EXPECT_EQ(test_stack.size(), std_stack.size());

  EXPECT_EQ(moving_stack.top(), 0);
  EXPECT_EQ(moving_stack.size(), 0);

  // перемещение пустого стэка
  stack<int> null_stack;
  stack<int> test_stack_2 = std::move(null_stack);
  std::stack<int> null_std_stack;
  std::stack<int> std_stack_2 = std::move(null_std_stack);

  EXPECT_EQ(test_stack_2.top(), 0);
  EXPECT_EQ(test_stack_2.size(), 0);
}

TEST(Stack_Functions, assignment_operator_overload) {
  stack<int> test_stack;
  test_stack = {1};
  test_stack.pop();

  test_stack = {1, 2, 3};
  std::stack<int> std_stack;
  for (int i = 3; i >= 1; i--) {
    std_stack.push(i);
  }

  stack<int> test_stack_2 = {1, 2, 3, 4, 5};
  test_stack_2 = std::move(test_stack);
  std::stack<int> std_stack_2;
  for (int i = 1; i <= 5; i++) {
    std_stack_2.push(i);
  }
  std_stack_2 = std::move(std_stack);

  while (test_stack.top()) {
    EXPECT_EQ(test_stack.top(), std_stack.top());
    test_stack.pop();
    std_stack.pop();
  }

  EXPECT_EQ(test_stack_2.top(), std_stack_2.top());
  EXPECT_EQ(test_stack_2.size(), std_stack_2.size());
}

// ------- Stack Element access -------

TEST(Stack_Elemets_access, front_back) {
  stack<int> test_stack = {1, 2, 3, 4, 5, 6, 7};
  std::stack<int> std_stack;
  for (int i = 7; i >= 1; i--) {
    std_stack.push(i);
  }
  EXPECT_EQ(test_stack.top(), std_stack.top());

  // пустой стэк
  stack<int> test_stack_2;
  EXPECT_EQ(test_stack_2.top(), 0);
  EXPECT_EQ(test_stack_2.size(), 0);
}

// ------- Stack Capacity -------

TEST(Stack_Capacity, empty) {
  stack<int> test_stack = {0, 1, 2, 3, 4, 5};
  std::stack<int> std_stack;
  for (int i = 5; i >= 1; i--) {
    std_stack.push(i);
  }
  EXPECT_EQ(test_stack.empty(), std_stack.empty());

  // пустой стэк
  stack<int> test_stack_2;
  EXPECT_EQ(test_stack_2.top(), 0);
  EXPECT_EQ(test_stack_2.size(), 0);
}

// ------- Stack Modifiers -------

TEST(Stack_Modifiers, push) {
  stack<int> test_stack = {0, 1, 2, 3, 4, 5};
  std::stack<int> std_stack;
  for (int i = 5; i >= 1; i--) {
    std_stack.push(i);
  }

  test_stack.push(350);
  std_stack.push(350);
  while (test_stack.top()) {
    EXPECT_EQ(test_stack.top(), std_stack.top());
    test_stack.pop();
    std_stack.pop();
  }

  // вставка в пустую очередь
  stack<int> test_stack_2;
  std::stack<int> std_stack_2;
  test_stack_2.push(350);
  std_stack_2.push(350);
  EXPECT_EQ(test_stack_2.top(), std_stack_2.top());
}

TEST(Stack_Modifiers, pop) {
  stack<int> test_stack = {0, 1, 2, 3, 4, 5};
  std::stack<int> std_stack;
  for (int i = 5; i >= 0; i--) {
    std_stack.push(i);
  }

  test_stack.pop();
  std_stack.pop();
  while (test_stack.top()) {
    EXPECT_EQ(test_stack.top(), std_stack.top());
    test_stack.pop();
    std_stack.pop();
  }

  // удаление из пустого стэка
  stack<int> test_stack_2;
  std::stack<int> std_stack_2;
  test_stack_2.pop();
  std_stack_2.pop();
}

TEST(Stack_Modifiers, swap) {
  stack<int> q1 = {1, 2, 3};
  stack<int> q2 = {4, 5, 6, 7};
  q1.swap(q2);

  std::stack<int> std_q1;
  for (int i = 3; i >= 1; i--) {
    std_q1.push(i);
  }
  std::stack<int> std_q2;
  for (int i = 7; i >= 4; i--) {
    std_q2.push(i);
  }
  std_q1.swap(std_q2);

  while (q1.top()) {
    EXPECT_EQ(q1.top(), std_q1.top());
    q1.pop();
    std_q1.pop();
  }

  while (q2.top()) {
    EXPECT_EQ(q2.top(), std_q2.top());
    q2.pop();
    std_q2.pop();
  }

  // пустой стэк
  stack<int> q3;
  std::stack<int> std_q3;
  stack<int> q4 = {1, 2, 3};
  std::stack<int> std_q4;
  for (int i = 3; i >= 1; i--) {
    std_q4.push(i);
  }
  q3.swap(q4);
  std_q3.swap(std_q4);

  while (q3.top()) {
    EXPECT_EQ(q3.top(), std_q3.top());
    q3.pop();
    std_q3.pop();
  }

  // двe пустых очереди
  stack<int> q5;
  std::stack<int> std_q5;
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
