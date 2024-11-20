#include <gtest/gtest.h>
#include <memory>
#include <optional>
#include "../task/Shape/IShape.h"
#include "../task/Shape/GroupShape.h"
#include "../task/Shape/Rectangle.h"
#include "../task/Shape/Triangle.h"
#include "../task/Slide/SlideService.h"

void AssertFrameEQ(RectD actualFrame, RectD expectedFrame)
{
    EXPECT_EQ(actualFrame.top, expectedFrame.top);
    EXPECT_EQ(actualFrame.width, expectedFrame.width);
    EXPECT_EQ(actualFrame.height, expectedFrame.height);
    EXPECT_EQ(actualFrame.left, expectedFrame.left);
}

class GroupShapeTest : public ::testing::Test {
protected:
    void SetUp() override {
        groupShape = std::make_shared<GroupShape>();
    }

    std::shared_ptr<GroupShape> groupShape;
};

TEST_F(GroupShapeTest, AddShape) {
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Triangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    size_t count = groupShape->GetShapesCount();
    EXPECT_EQ(count, 1);
}

TEST_F(GroupShapeTest, RemoveShape) {
    auto rectangle = std::make_shared<Rectangle>(
            RectD{0, 0, 100, 100},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    EXPECT_EQ(groupShape->GetShapesCount(), 1);

    groupShape->RemoveShapeAtIndex(0);
    EXPECT_EQ(groupShape->GetShapesCount(), 0);
}

TEST_F(GroupShapeTest, GetFrame) {
    auto rectangle1 = std::make_shared<Rectangle>(
            RectD{100, 100, 200, 200},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    auto rectangle2 = std::make_shared<Rectangle>(
            RectD{150, 150, 100, 100},
            std::make_unique<Style>(0x00FF00FF),
            std::make_unique<Style>(0x0000FFFF)
    );

    groupShape->InsertShape(rectangle1, 0);
    groupShape->InsertShape(rectangle2, 1);

    RectD expectedFrame = {100, 100, 200, 200};
    auto actualFrame = groupShape->GetFrame().value();
    AssertFrameEQ(actualFrame, expectedFrame);
}

TEST_F(GroupShapeTest, GetFrameOnEmptyGroups) {
    auto emptyGroupShape1 = std::make_shared<GroupShape>();
    auto emptyGroupShape2 = std::make_shared<GroupShape>();
    groupShape->InsertShape(emptyGroupShape1, 0);
    groupShape->InsertShape(emptyGroupShape2, 1);
    EXPECT_EQ(groupShape->GetFrame(), std::nullopt);
}

TEST_F(GroupShapeTest, GetShapeAtIndex) {
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(triangle, 0);
    auto shape = groupShape->GetShapeAtIndex(0);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(shape, triangle);
}

TEST_F(GroupShapeTest, SetRect) {
    auto rectangle1 = std::make_shared<Rectangle>(
            RectD{100, 100, 200, 200},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );

    auto rectangle2 = std::make_shared<Rectangle>(
            RectD{150, 150, 100, 100},
            std::make_unique<Style>(0x00FF00FF),
            std::make_unique<Style>(0x0000FFFF)
    );

    groupShape->InsertShape(rectangle1, 0);
    groupShape->InsertShape(rectangle2, 1);

    RectD expectedFrame = {100, 100, 200, 200};
    AssertFrameEQ(groupShape->GetFrame().value(), expectedFrame);

    RectD newFrame = {20, 20, 20, 20};
    groupShape->SetFrame(newFrame);
    AssertFrameEQ(groupShape->GetFrame().value(), newFrame);
}

TEST_F(GroupShapeTest, SetRectWithEmptyGroup) {
    auto rectangle = std::make_shared<Rectangle>(
            RectD{100, 100, 200, 200},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );
    auto anotherGroupShape = std::make_shared<GroupShape>();

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(anotherGroupShape, 1);

    RectD expectedFrame = {100, 100, 200, 200};
   
    EXPECT_TRUE(groupShape->GetFrame() != std::nullopt);
    AssertFrameEQ(groupShape->GetFrame().value(), expectedFrame);
}

TEST_F(GroupShapeTest, AddShapeAndGroupShape)
{
    auto rectangle = std::make_shared<Rectangle>(
            RectD{0, 0, 100, 100},
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );
    auto triangleInShape = std::make_shared<Triangle>(
            RectD{300, 300, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );
    auto anotherGroupShape = std::make_shared<GroupShape>();

    anotherGroupShape->InsertShape(triangleInShape, 0);
    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);
    groupShape->InsertShape(anotherGroupShape, 2);

    EXPECT_EQ(groupShape->GetShapesCount(), 3);
}

TEST_F(GroupShapeTest, GetStyleGroupShape)
{
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0x0000FFFF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);

    auto outlineStyleColor = groupShape->GetOutlineStyle().GetColor();
    auto fillStyleColor = groupShape->GetFillStyle().GetColor();

    EXPECT_TRUE(outlineStyleColor == std::nullopt);
    EXPECT_TRUE(fillStyleColor == std::nullopt);
}

TEST_F(GroupShapeTest, GetSameStyleGroupShape)
{
    RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
    RGBAColor expectedFillStyleColor = 0xFF0000FF;
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetOutlineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());
}

TEST_F(GroupShapeTest, SetStyleGroupShape)
{
    RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
    RGBAColor expectedFillStyleColor = 0xFF0000FF;
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFFFF00FF),
            std::make_unique<Style>(0xFFAA00FF)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0xFFAA00FF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);
    groupShape->GetOutlineStyle().SetColor(expectedOutlineStyleColor);
    groupShape->GetFillStyle().SetColor(expectedFillStyleColor);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetOutlineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());
}

TEST_F(GroupShapeTest, SetStyleShapeInGroupShape)
{
    RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
    RGBAColor expectedFillStyleColor = 0xFF0000FF;
    auto rect = RectD{0, 0, 100, 100};
    auto anotherGroupShape = std::make_shared<GroupShape>();
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );

    anotherGroupShape->InsertShape(rectangle, 0);
    anotherGroupShape->InsertShape(triangle, 1);
    groupShape->InsertShape(anotherGroupShape, 0);

    EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetOutlineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());

    RGBAColor newExpectedOutlineStyleColor = 0xFFF000FF;
    RGBAColor newExpectedFillStyleColor = 0xFFF000FF;
    rectangle->GetOutlineStyle().SetColor(newExpectedOutlineStyleColor);
    rectangle->GetFillStyle().SetColor(newExpectedFillStyleColor);

    auto outlineStyleColor = groupShape->GetOutlineStyle().GetColor();
    auto fillStyleColor = groupShape->GetFillStyle().GetColor();

    EXPECT_TRUE(outlineStyleColor == std::nullopt);
    EXPECT_TRUE(fillStyleColor == std::nullopt);

    outlineStyleColor = anotherGroupShape->GetOutlineStyle().GetColor();
    fillStyleColor = anotherGroupShape->GetFillStyle().GetColor();

    EXPECT_TRUE(outlineStyleColor == std::nullopt);
    EXPECT_TRUE(fillStyleColor == std::nullopt);
}

TEST_F(GroupShapeTest, RemoveShapeWithStyleInGroupShape)
{
    RGBAColor expectedOutlineStyleColor = 0xFF0000FF;
    RGBAColor expectedFillStyleColor = 0xFFFFF0FF;
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(expectedOutlineStyleColor),
            std::make_unique<Style>(expectedFillStyleColor)
    );
    auto triangle = std::make_shared<Triangle>(
            RectD{200, 200, 100, 100},
            std::make_unique<Style>(0xFFF000FF),
            std::make_unique<Style>(0xFFFF00FF)
    );

    groupShape->InsertShape(rectangle, 0);
    groupShape->InsertShape(triangle, 1);

    auto outlineStyleColor = groupShape->GetOutlineStyle().GetColor();
    auto fillStyleColor = groupShape->GetFillStyle().GetColor();

    EXPECT_TRUE(outlineStyleColor == std::nullopt);
    EXPECT_TRUE(fillStyleColor == std::nullopt);
    EXPECT_EQ(groupShape->GetShapesCount(), 2);

    groupShape->RemoveShapeAtIndex(1);

    EXPECT_EQ(groupShape->GetShapesCount(), 1);
    EXPECT_EQ(expectedOutlineStyleColor, groupShape->GetOutlineStyle().GetColor());
    EXPECT_EQ(expectedFillStyleColor, groupShape->GetFillStyle().GetColor());
}

TEST_F(GroupShapeTest, GetGroup) {
    auto rect = RectD{0, 0, 100, 100};
    auto rectangle = std::make_shared<Rectangle>(
            rect,
            std::make_unique<Style>(0xFF0000FF),
            std::make_unique<Style>(0x00FF00FF)
    );


    EXPECT_EQ(rectangle->GetGroup(), nullptr);
    EXPECT_TRUE(groupShape->GetGroup() != nullptr);
}

TEST_F(GroupShapeTest, GetShapesCountEmpty) {
    EXPECT_EQ(groupShape->GetShapesCount(), 0);
}