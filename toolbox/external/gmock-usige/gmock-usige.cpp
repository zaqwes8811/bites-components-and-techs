// gmock-usige.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// C
#include <stdio.h>

// C++
#include <iostream>
using std::cout;
using std::endl;

#include "gmock/gmock.h"
#include "gtest/gtest.h"
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::Ge;
using ::testing::InSequence;  // Делает строгую зависимость вызовов
using ::testing::Throw;

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using boost::shared_ptr;
using boost::weak_ptr;

class Turtle {
public:
  virtual ~Turtle() {}
  virtual void PenUp() = 0;
  virtual void PenDown() = 0;
  virtual void Forward(int distance) = 0;
  virtual void Turn(int degrees) = 0;
  virtual void GoTo(int x, int y) = 0;
  virtual int GetX() const = 0;
  virtual int GetY() const = 0;
};

namespace test_space {
class MockTurtle : public Turtle {
 public:
  MOCK_METHOD0(PenUp, void());
  MOCK_METHOD0(PenDown, void());
  MOCK_METHOD1(Forward, void(int distance));
  MOCK_METHOD1(Turn, void(int degrees));
  MOCK_METHOD2(GoTo, void(int x, int y));
  MOCK_CONST_METHOD0(GetX, int());
  MOCK_CONST_METHOD0(GetY, int());
};
}

void test(shared_ptr<Turtle> b) {
  b->PenDown();
}

void test(weak_ptr<Turtle> b) {
  if(shared_ptr<Turtle> r = b.lock()) {
    r->PenDown();
  }
}

void test_getter(weak_ptr<Turtle> b) {
  if(shared_ptr<Turtle> r = b.lock()) {
    cout << r->GetX() << endl;
  }
}

void test_getter_y(weak_ptr<Turtle> b) {
  if(shared_ptr<Turtle> r = b.lock()) {
    cout << r->GetY() << endl;
  }
}

TEST(PainterTest, CanDrawSomething) {
  //@CreateObjectGraph
  // Нужно создать прямо моковского типа!
  shared_ptr<test_space::MockTurtle> bear(new test_space::MockTurtle);

  //@Expectations
  EXPECT_CALL(*bear, PenDown())
    .Times(AtLeast(1));

  EXPECT_CALL(*bear, GetX())
    .Times(5)
    .WillOnce(Return(100))
    .WillOnce(Return(150))
    .WillRepeatedly(Return(200));


  /*
  // Возможно лучше подходит для...?
  ON_CALL(foo, Sign(Gt(0)))
      .WillByDefault(Return(1))
  */
  EXPECT_CALL(*bear, GetY())
    .WillOnce(Throw(std::string("asdffd")));

  //@Runners
  weak_ptr<Turtle> weak_bear(bear);

  // Указатель приводится вверх
  //@Warning: Это upcasting - кажется все норм
  test(weak_bear);

  test_getter(weak_bear);
  test_getter(weak_bear);
  test_getter(weak_bear);
  test_getter(weak_bear);
  test_getter(weak_bear);

  EXPECT_THROW(test_getter_y(weak_bear), std::string);
} 

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  RUN_ALL_TESTS();
  std::cout << "press any key\n";
  char c;
  c = getchar();
  return 0;
}
