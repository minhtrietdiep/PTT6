#include "gtest/gtest.h"
#include "../Coordinates.h"
 
TEST(HAL, CoordinatesVectorEqualSize) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	std::vector<int> x = coords.GetCoordinates();
	std::vector<int> y { 1, 2, 3, 4 };
	
	ASSERT_EQ(x.size(), y.size());
}

TEST(HAL, CoordinatesVectorNotEqualSize) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	std::vector<int> x = coords.GetCoordinates();
	std::vector<int> y { 1, 2, 3, 4, 5 };
	
	ASSERT_NE(x.size(), y.size());
}

TEST(HAL, CoordinatesValuesEqual) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	std::vector<int> x = coords.GetCoordinates();
	std::vector<int> y { 1, 2, 3, 4 };
	
	for (unsigned int i = 0; i < x.size(); ++i) {
		EXPECT_EQ(x[i], y[i]);
	}
}

TEST(HAL, CoordinatesValuesNotEqual) 
{
	Coordinates coords = Coordinates(1, 2, 3, 4);

	std::vector<int> x = coords.GetCoordinates();
	std::vector<int> y { 4, 3, 2, 1 };
	
	for (unsigned int i = 0; i < x.size(); ++i) {
		EXPECT_NE(x[i], y[i]);
	}
}
