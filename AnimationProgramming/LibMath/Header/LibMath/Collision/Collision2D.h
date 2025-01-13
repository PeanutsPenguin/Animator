#include "LibMath/Vector/Vec2.h"
#include <vector>

namespace LibMath
{
	typedef LibMath::Vector2 Point2D;

	class Line2D
	{
	public:

		Line2D() = default;

		Line2D(const Line2D&) = default;

		Line2D(Line2D&&) = default;

		Line2D(const Point2D& a, const Point2D& b) : start(a), end(b) {};

		Line2D& operator=(const Line2D&) = default;

		~Line2D() = default;

		float length();

		float lengthSquared() const;

		Point2D getStart() const;

		Point2D getEnd() const;

	private:
		Point2D start;
		Point2D end;
	};

	class Circle2D
	{
	public:
		Circle2D() = default;

		Circle2D(const Circle2D&) = default;

		Circle2D(Circle2D&&) = default;

		Circle2D(const Point2D& a, const float b) : center(a), radius(b) {};

		Circle2D& operator=(const Circle2D&) = default;

		~Circle2D() = default;

		Point2D Center() const;

		float Radius() const;

	private:
		Point2D center;
		float radius;
	};

	class Triangle2D
	{
	public:
		Triangle2D() = default;

		Triangle2D(const Triangle2D&) = default;

		Triangle2D(Triangle2D&&) = default;

		Triangle2D(const Point2D& a, const Point2D& b, const Point2D& c) : a(a), b(b), c(c) {};

		Triangle2D& operator=(const Triangle2D&) = default;

		static float Area(const Point2D& a, const Point2D& b, const Point2D& c);

		Point2D a;
		Point2D b;
		Point2D c;
	};

	class Rectangle2D
	{
	public:
		Rectangle2D() = default;

		Rectangle2D(const Rectangle2D&) = default;

		Rectangle2D(Rectangle2D&&) = default;

		Rectangle2D(const Point2D& a, const float b, const float c) : center(a), width(b), height(c) {};

		Rectangle2D& operator=(const Rectangle2D&) = default;

		~Rectangle2D() = default;

		Point2D Center() const;

		float ExtentX() const;

		float ExtentY() const;

	private:
		Point2D center;
		float width;
		float height;
	};

	class OrientedRectangle2D
	{
	public:
		OrientedRectangle2D() = default;

		OrientedRectangle2D(const OrientedRectangle2D&) = default;

		OrientedRectangle2D(OrientedRectangle2D&&) = default;

		OrientedRectangle2D(const Point2D& a, const float b, const float c, const float d) : center(a), width(b), height(c), rotation(d) {};

		OrientedRectangle2D& operator=(const OrientedRectangle2D&) = default;

		~OrientedRectangle2D() = default;

		Point2D Center() const;

		float ExtentX()const;

		float ExtentY()const;

		float Roation()const;

	private:
		Point2D center;
		float width;
		float height;
		float rotation;
	};

	class ConvexForm2D
	{
	public:
		ConvexForm2D() = default;

		ConvexForm2D(const ConvexForm2D&) = default;

		ConvexForm2D(ConvexForm2D&&) = default;

		ConvexForm2D(std::vector<Point2D> a) : vertexArray(a) {};

		~ConvexForm2D() = default;

		ConvexForm2D& operator=(const ConvexForm2D&) = default;

		Point2D& operator[](size_t index);

		std::vector<Point2D> getVertexArray();

	private:
		std::vector<Point2D> vertexArray;
	};
	
	namespace CollisionCheck
	{
		bool Circle2DtoCircle2D(const Circle2D&, const Circle2D&);				//Check collision between two circles

		bool Line2DtoCircle2D(const Line2D&, const Circle2D&);					//Check collision between a line and a circle

		bool Rectangle2DtoCircle2D(const Rectangle2D&, const Circle2D&);		//Check collision between a rectangle and a circle

		bool LinetoLine(const Line2D&, const Line2D&);							//Check collision between two lines

		bool LinetoRectangle(const Line2D&, const Rectangle2D&);				//Check collision between a line and a rectangle

		bool PointtoRectangle(const Point2D&, const Rectangle2D&);				//Check collision between a point and a rectangle

		bool SATConvexForm(const ConvexForm2D&, const ConvexForm2D&);			//Separate axis theorem collision check function

		bool checkMaxAndMin(Vector2&, ConvexForm2D&, ConvexForm2D&);			//Fonction for the SAT

		bool isInTriangle(Triangle2D triangle, Point2D& point);
	}
}