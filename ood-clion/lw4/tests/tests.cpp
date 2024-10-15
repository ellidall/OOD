#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../task1/ShapeFactory/Shape/Shape.h"
#include "../task1/ShapeFactory/Shape/Color.h"
#include "../task1/ShapeFactory/IShapeFactory.h"
#include "../task1/Designer/IDesigner.h"
#include "../task1/Painter/IPainter.h"
#include "../task1/ShapeFactory/Shape/Point.h"
#include "../task1/ShapeFactory/Shape/Rectangle.h"
#include "../task1/ShapeFactory/Shape/Triangle.h"
#include "../task1/ShapeFactory/Shape/Ellipse.h"
#include "../task1/ShapeFactory/Shape/RegularPolygon.h"
#include "../task1/ShapeFactory/ShapeFactory.h"
#include "../task1/Designer/Designer.h"
#include "../task1/Painter/Painter.h"
#include "../task1/Client.h"

using ::testing::_;
using ::testing::Return;

class MockShape final : public Shape
{
public:
    explicit MockShape(const Color color) : Shape(color)
    {
    }

    MOCK_METHOD(void, Draw, (ICanvas & canvas), (const, override));
};

class MockShapeFactory final : public IShapeFactory
{
public:
    MOCK_METHOD(std::unique_ptr<Shape>, CreateShape, (const std::string& description), (override));
};

class MockDesigner final : public IDesigner
{
public:
    MOCK_METHOD(PictureDraft, CreateDraft, (std::istream & inputData), (override));
};

class MockPainter final : public IPainter
{
public:
    MOCK_METHOD(void, DrawPicture, (const PictureDraft& draft, ICanvas& canvas), (override));
};

class MockCanvas final : public ICanvas
{
public:
    MOCK_METHOD(void, SetColor, (uint32_t color), (override));
    MOCK_METHOD(void, MoveTo, (double x, double y), (override));
    MOCK_METHOD(void, LineTo, (double x, double y), (override));
    MOCK_METHOD(void, DrawEllipse, (double cx, double cy, double rx, double ry), (override));
};

void ExpectEqualPoint(const Point expectedPoint, const Point actualPoint)
{
    EXPECT_EQ(expectedPoint.x, actualPoint.x);
    EXPECT_EQ(expectedPoint.y, actualPoint.y);
}

TEST(RectangleTest, SuccessCreate)
{
    constexpr Color color = 0x000000;
    constexpr Point leftTop(10, 10);
    constexpr Point rightBottom(40, 20);

    const Rectangle rectangle(color, {leftTop, rightBottom});

    EXPECT_EQ(color, rectangle.GetColor());
    ExpectEqualPoint(leftTop, rectangle.GetLeftTop());
    EXPECT_EQ(30, rectangle.GetWidth());
    EXPECT_EQ(10, rectangle.GetHeight());
}

TEST(RectangleTest, SuccessDraw)
{
    constexpr Color color = 0x000000;
    constexpr Point leftTop(200, 200);
    constexpr Point rightBottom(250, 280);

    const Rectangle rectangle(color, Rect(leftTop, rightBottom));
    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color)).Times(1);
    EXPECT_CALL(mockCanvas, MoveTo(leftTop.x, leftTop.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(rightBottom.x, leftTop.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(rightBottom.x, rightBottom.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(leftTop.x, rightBottom.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(leftTop.x, leftTop.y)).Times(1);
    rectangle.Draw(mockCanvas);
}

TEST(EllipseTest, SuccessCreate)
{
    constexpr Color color = 0x000000;
    constexpr Point center(50, 50);
    constexpr double horizontalRadius = 30;
    constexpr double verticalRadius = 20;

    const Ellipse ellipse(color, center, horizontalRadius, verticalRadius);

    EXPECT_EQ(color, ellipse.GetColor());
    ExpectEqualPoint(center, ellipse.GetCenter());
    EXPECT_EQ(horizontalRadius, ellipse.GetHorizontalRadius());
    EXPECT_EQ(verticalRadius, ellipse.GetVerticalRadius());
}

TEST(EllipseTest, SuccessDraw)
{
    constexpr Color color = 0x000000;
    constexpr Point center(50, 50);
    constexpr double horizontalRadius = 30;
    constexpr double verticalRadius = 20;

    const Ellipse ellipse(color, center, horizontalRadius, verticalRadius);
    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color)).Times(1);
    EXPECT_CALL(mockCanvas, DrawEllipse(center.x, center.y, horizontalRadius, verticalRadius))
            .Times(1);
    ellipse.Draw(mockCanvas);
}

TEST(TriangleTest, SuccessCreate)
{
    constexpr Color color = 0x000000;
    constexpr Point firstAngle(10, 20);
    constexpr Point secondAngle(40, 20);
    constexpr Point thirdAngle(25, 50);

    const Triangle triangle(color, firstAngle, secondAngle, thirdAngle);

    EXPECT_EQ(color, triangle.GetColor());
    ExpectEqualPoint(firstAngle, triangle.GetFirstAngle());
    ExpectEqualPoint(secondAngle, triangle.GetSecondAngle());
    ExpectEqualPoint(thirdAngle, triangle.GetThirdAngle());
}

TEST(TriangleTest, SuccessDraw)
{
    constexpr Color color = 0x000000;
    constexpr Point firstAngle(10, 20);
    constexpr Point secondAngle(40, 20);
    constexpr Point thirdAngle(25, 50);

    const Triangle triangle(color, firstAngle, secondAngle, thirdAngle);
    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color)).Times(1);
    EXPECT_CALL(mockCanvas, MoveTo(firstAngle.x, firstAngle.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(secondAngle.x, secondAngle.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(thirdAngle.x, thirdAngle.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(firstAngle.x, firstAngle.y)).Times(1);
    triangle.Draw(mockCanvas);
}

TEST(LineTest, SuccessCreate)
{
    constexpr Color color = 0x000000;
    constexpr Point start(10, 20);
    constexpr Point end(40, 20);

    const Line line(color, start, end);

    EXPECT_EQ(color, line.GetColor());
    ExpectEqualPoint(start, line.GetStartPoint());
    ExpectEqualPoint(end, line.GetEndPoint());
}

TEST(LineTest, SuccessDraw)
{
    constexpr Color color = 0x000000;
    constexpr Point start(10, 20);
    constexpr Point end(40, 20);

    const Line line(color, start, end);
    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color)).Times(1);
    EXPECT_CALL(mockCanvas, MoveTo(start.x, start.y)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(end.x, end.y)).Times(1);
    line.Draw(mockCanvas);
}

TEST(RegularPolygonTest, SuccessCreate)
{
    constexpr Color color = 0x000000;
    constexpr Point center(50, 50);
    constexpr int pointsCount = 5;
    constexpr double radius = 30.0;

    const RegularPolygon polygon(color, center, pointsCount, radius);

    EXPECT_EQ(color, polygon.GetColor());
    ExpectEqualPoint(center, polygon.GetCenter());
    EXPECT_EQ(pointsCount, polygon.GetPointsCount());
    EXPECT_EQ(radius, polygon.GetRadius());
}

TEST(RegularPolygonTest, SuccessDraw)
{
    constexpr Color color = 0x000000;
    constexpr Point center(50, 50);
    constexpr int pointsCount = 5;
    constexpr double radius = 30.0;

    const RegularPolygon polygon(color, center, pointsCount, radius);
    MockCanvas mockCanvas;

    EXPECT_CALL(mockCanvas, SetColor(color)).Times(1);
    constexpr double angleStep = 2 * M_PI / pointsCount;
    const double startX = center.x + radius * std::cos(0);
    const double startY = center.y + radius * std::sin(0);
    double prevX = startX;
    double prevY = startY;
    for (int i = 1; i <= pointsCount; ++i)
    {
        const double angle = i * angleStep;
        const double x = center.x + radius * std::cos(angle);
        const double y = center.y + radius * std::sin(angle);

        EXPECT_CALL(mockCanvas, MoveTo(prevX, prevY)).Times(1);
        EXPECT_CALL(mockCanvas, LineTo(x, y)).Times(1);

        prevX = x;
        prevY = y;
    }
    EXPECT_CALL(mockCanvas, MoveTo(prevX, prevY)).Times(1);
    EXPECT_CALL(mockCanvas, LineTo(startX, startY)).Times(1);
    polygon.Draw(mockCanvas);
}

TEST(ShapeFactoryTest, SuccessCreateTriangle)
{
    const std::string description = "#EB5757 triangle 200 200 400 100 600 200";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Triangle));

    auto* triangle = dynamic_cast<Triangle*>(shape.get());
    ASSERT_NE(triangle, nullptr);

    EXPECT_EQ(triangle->GetColor(), 0xEB5757FF);
    ExpectEqualPoint(triangle->GetFirstAngle(), Point(200, 200));
    ExpectEqualPoint(triangle->GetSecondAngle(), Point(400, 100));
    ExpectEqualPoint(triangle->GetThirdAngle(), Point(600, 200));
}

TEST(ShapeFactoryTest, SuccessCreateEllipse)
{
    const std::string description = "#FCC846 ellipse 45 45 35 35";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Ellipse));

    auto* ellipse = dynamic_cast<Ellipse*>(shape.get());
    ASSERT_NE(ellipse, nullptr);

    EXPECT_EQ(ellipse->GetColor(), 0xFCC846FF);
    ExpectEqualPoint(ellipse->GetCenter(), Point(45, 45));
    EXPECT_EQ(ellipse->GetHorizontalRadius(), 35);
    EXPECT_EQ(ellipse->GetVerticalRadius(), 35);
}

TEST(ShapeFactoryTest, SuccessCreateRectangle)
{
    const std::string description = "#EB5757 rectangle 200 200 400 180";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Rectangle));

    auto* rectangle = dynamic_cast<Rectangle*>(shape.get());
    ASSERT_NE(rectangle, nullptr);

    EXPECT_EQ(rectangle->GetColor(), 0xEB5757FF);
    ExpectEqualPoint(rectangle->GetLeftTop(), Point(200, 200));
    EXPECT_EQ(rectangle->GetWidth(), 400);
    EXPECT_EQ(rectangle->GetHeight(), 180);
}

TEST(ShapeFactoryTest, SuccessCreateLine)
{
    const std::string description = "#EB5757 line 200 200 400 180";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(Line));

    auto* line = dynamic_cast<Line*>(shape.get());
    ASSERT_NE(line, nullptr);

    EXPECT_EQ(line->GetColor(), 0xEB5757FF);
    ExpectEqualPoint(line->GetStartPoint(), Point(200, 200));
    ExpectEqualPoint(line->GetEndPoint(), Point(400, 180));
}

TEST(ShapeFactoryTest, SuccessCreateRegularPolygon)
{
    const std::string description = "#FF0000 regular_polygon 400 50 10 30";

    ShapeFactory shapeFactory;
    auto shape = shapeFactory.CreateShape(description);

    EXPECT_NE(shape, nullptr);
    EXPECT_EQ(typeid(*shape), typeid(RegularPolygon));

    auto* polygon = dynamic_cast<RegularPolygon*>(shape.get());
    ASSERT_NE(polygon, nullptr);

    EXPECT_EQ(polygon->GetColor(), 0xFF0000FF);
    ExpectEqualPoint(polygon->GetCenter(), Point(400, 50));
    EXPECT_EQ(polygon->GetPointsCount(), 10);
    EXPECT_EQ(polygon->GetRadius(), 30);
}

TEST(ShapeFactoryTest, UnknownShapeException)
{
    const std::string description = "#FCC846 circle 45 45 35 35";

    ShapeFactory shapeFactory;

    EXPECT_THROW(shapeFactory.CreateShape(description), std::invalid_argument);
}

TEST(PictureDraftTest, SuccessAddShape)
{
    PictureDraft draft;
    auto triangle = std::make_unique<MockShape>(0x000000);
    auto ellipse = std::make_unique<MockShape>(0x000000);
    auto rectangle = std::make_unique<MockShape>(0x000000);

    draft.AddShape(std::move(triangle));
    draft.AddShape(std::move(ellipse));
    draft.AddShape(std::move(rectangle));

    EXPECT_EQ(std::distance(draft.begin(), draft.end()), 3);
}

TEST(PictureDraftTest, SuccessIterateShapes)
{
    PictureDraft draft;
    auto triangle = std::make_unique<MockShape>(0x000000);
    auto ellipse = std::make_unique<MockShape>(0x000000);

    draft.AddShape(std::move(triangle));
    draft.AddShape(std::move(ellipse));

    int count = 0;
    for (const auto &shape: draft)
    {
        EXPECT_NE(shape, nullptr);
        count++;
    }

    EXPECT_EQ(count, 2);
}

TEST(DesignerTest, SuccessCreateDraftWithShapes)
{
    MockShapeFactory mockFactory;
    Designer designer(mockFactory);

    std::istringstream inputData(
            "#B7B7B7 rectangle 0 380 800 500\n"
            "#FCC846 ellipse 45 45 35 35\n"
            "#FCC846 line 85 45 115 45\n"
    );

    EXPECT_CALL(mockFactory, CreateShape("#B7B7B7 rectangle 0 380 800 500"))
            .WillOnce(Return(std::make_unique<MockShape>(0xB7B7B7FF)));
    EXPECT_CALL(mockFactory, CreateShape("#FCC846 ellipse 45 45 35 35"))
            .WillOnce(Return(std::make_unique<MockShape>(0xFCC846FF)));
    EXPECT_CALL(mockFactory, CreateShape("#FCC846 line 85 45 115 45"))
            .WillOnce(Return(std::make_unique<MockShape>(0xFCC846FF)));
    PictureDraft draft = designer.CreateDraft(inputData);
    EXPECT_EQ(std::distance(draft.begin(), draft.end()), 3);
}

TEST(PainterTest, SuccessDrawPicture)
{
    Painter painter;
    MockCanvas mockCanvas;
    auto shape1 = std::make_unique<MockShape>(0x000000);
    auto shape2 = std::make_unique<MockShape>(0xFF0000);

    EXPECT_CALL(*shape1, Draw(testing::Ref(mockCanvas))).Times(1);
    EXPECT_CALL(*shape2, Draw(testing::Ref(mockCanvas))).Times(1);
    PictureDraft draft;
    draft.AddShape(std::move(shape1));
    draft.AddShape(std::move(shape2));

    painter.DrawPicture(draft, mockCanvas);
}

TEST(ClientTest, SuccessHandleCommand)
{
    MockDesigner mockDesigner;
    MockPainter mockPainter;
    MockCanvas mockCanvas;

    Client client(mockDesigner);

    std::istringstream inputData("#FCC846 line 85 45 115 45\n");

    EXPECT_CALL(mockDesigner, CreateDraft(testing::Ref(inputData)))
            .WillOnce(Return(PictureDraft()));
    EXPECT_CALL(mockPainter, DrawPicture(_, testing::Ref(mockCanvas))).Times(1);
    client.HandleCommand(inputData, mockCanvas, mockPainter);
}