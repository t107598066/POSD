#include <gtest/gtest.h>
#include "../src/shape.h"
#include "../src/circle.h"
#include "../src/rectangle.h"
#include "../src/triangle.h"
#include <algorithm>


TEST(ShapeTest, Circle)
{
  Circle c(10.0);
  ASSERT_NEAR(314.159, c.area(), 0.001);
  ASSERT_NEAR(62.831, c.perimeter(), 0.001);
  ASSERT_NEAR(12.5660, c.compactness(), 0.001);
}

TEST(Circle, Compactness)
{
  try
  {
    Circle c(0.0);
  }
  catch(const std::string message)
  {
    ASSERT_EQ(message,"Division by zero");
  }
}

TEST(ShapeTest, Rectangle)
{
  Rectangle r(10.0 , 5.0);
  ASSERT_NEAR(50.0, r.area(), 0.001);
  ASSERT_NEAR(30.0, r.perimeter(), 0.001);
}

TEST(ShapeTest, Triangle)
{
  Triangle t(-3.0,0.0, 0.0, 4.0, 5.0, 0.0);
  ASSERT_NEAR(16.0, t.area(), 0.001);
  ASSERT_NEAR(19.4031, t.perimeter(), 0.001);
}

TEST(Triangle, isTriangle)
{
  Triangle t(-3.0,0.0, 0.0, 4.0, 5.0, 0.0);
  ASSERT_TRUE(t.isTriangle());
}

TEST(Triangle, isNotTriangle)
{
  try
  {
    Triangle t(0.0,0.0, 0.0, 0.0, 0.0, 0.0);
      ASSERT_TRUE(t.isTriangle());
  }
  catch(const std::string message)
  {
    ASSERT_EQ(message,std::string("Not a triangle."));
  }
}
