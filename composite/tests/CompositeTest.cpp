#include "stdafx.h"
#include "../composite/Group.h"
#include "../composite/SimpleShapes.h"

struct GroupWithShape
{
	GroupWithShape()
	{
		auto rectangleShape = std::make_shared<CRectangle>(RectD{ 10, 10, 4, 4 });
		auto zeroRectangle = std::make_shared<CRectangle>(RectD{ 0, 0, 1, 1 });
		group.InsertShape(rectangleShape);
		group.InsertShape(zeroRectangle);

	}
	CGroup group;
};

BOOST_FIXTURE_TEST_SUITE(testing_resize_group, GroupWithShape)

BOOST_AUTO_TEST_CASE(test_position_shapes_after_move)
{
	auto rect = group.GetFrame();	
	group.SetFrame({ 10, 10, rect.width, rect.height });
	auto rectangleFrame = group.GetShape(0)->GetFrame();
	BOOST_CHECK_EQUAL(rectangleFrame.top, 20);
	BOOST_CHECK_EQUAL(rectangleFrame.left, 20);
	BOOST_CHECK_EQUAL(rectangleFrame.width, 4);
	BOOST_CHECK_EQUAL(rectangleFrame.height, 4);
}

BOOST_AUTO_TEST_CASE(test_size_shapes_after_resize)
{
	auto rect = group.GetFrame();
	group.SetFrame({ rect.left, rect.top, 28, 28 });
	auto rectangleFrame = group.GetShape(0)->GetFrame();
	BOOST_CHECK_EQUAL(rectangleFrame.top, 20);
	BOOST_CHECK_EQUAL(rectangleFrame.left, 20);
	BOOST_CHECK_EQUAL(rectangleFrame.width, 8);
	BOOST_CHECK_EQUAL(rectangleFrame.height, 8);
}

BOOST_AUTO_TEST_CASE(test_size_and_position_shapes_after_resize_with_move)
{
	auto rect = group.GetFrame();
	group.SetFrame({ 10, 10, 28, 28 });
	auto rectangleFrame = group.GetShape(0)->GetFrame();
	BOOST_CHECK_EQUAL(rectangleFrame.top, 30);
	BOOST_CHECK_EQUAL(rectangleFrame.left, 30);
	BOOST_CHECK_EQUAL(rectangleFrame.width, 8);
	BOOST_CHECK_EQUAL(rectangleFrame.height, 8);
}

BOOST_AUTO_TEST_CASE(can_make_shape_a_little)
{
	auto rect = group.GetFrame();
	group.SetFrame({ 0, 0, 7, 7 });
	auto rectangleFrame = group.GetShape(0)->GetFrame();
	BOOST_CHECK_EQUAL(rectangleFrame.top, 5);
	BOOST_CHECK_EQUAL(rectangleFrame.left, 5);
	BOOST_CHECK_EQUAL(rectangleFrame.width, 2);
	BOOST_CHECK_EQUAL(rectangleFrame.height, 2);
}

BOOST_AUTO_TEST_SUITE_END()