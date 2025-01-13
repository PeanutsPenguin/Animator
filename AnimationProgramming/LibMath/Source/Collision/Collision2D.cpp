#include "LibMath/Collision/Collision2D.h"

namespace LibMath
{
	/**********LINE 2D**********/
	float Line2D::length()
	{
		return Vector2::Distance(this->start, this->end);
	}
	float Line2D::lengthSquared() const
	{
		return Vector2::DistanceSquared(this->start, this->end);
	}
	Point2D Line2D::getStart() const
	{
		return this->start;
	}
	Point2D Line2D::getEnd() const
	{
		return this->end;
	}

	/**********CIRCLE 2D**********/
	Point2D Circle2D::Center() const
	{
		return this->center;
	}
	float Circle2D::Radius() const
	{
		return this->radius;
	}

	/**********RECTANGLE 2D**********/
	Point2D Rectangle2D::Center() const
	{
		return this->center;
	}
	float Rectangle2D::ExtentX()const
	{
		return this->width;
	}
	float Rectangle2D::ExtentY() const
	{
		return this->height;
	}

	/**********ORIENTED RECTANGLE 2D**********/
	Point2D OrientedRectangle2D::Center() const
	{
		return this->center;
	}
	float OrientedRectangle2D::ExtentX() const
	{
		return this->width;
	}
	float OrientedRectangle2D::ExtentY() const
	{
		return this->height;
	}
	float OrientedRectangle2D::Roation() const
	{
		return this->rotation;
	}

	/**********CONVEX FORM 2D**********/
	Point2D& ConvexForm2D::operator[](size_t index)
	{
		return this->vertexArray[index];
	}

	std::vector<Point2D> ConvexForm2D::getVertexArray()
	{
		return this->vertexArray;
	}

	float Triangle2D::Area(const Point2D& a, const Point2D& b, const Point2D& c)
	{
		return (float)abs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
	}

	namespace CollisionCheck
	{
		bool Circle2DtoCircle2D(const Circle2D& a, const Circle2D& b)
		{
			if (LibMath::Vector2::DistanceSquared(a.Center(), b.Center()) <= (a.Radius() + b.Radius()) * (a.Radius() + b.Radius()))
				return true;

			return false;
		}

		bool Line2DtoCircle2D(const Line2D& a, const Circle2D& b)
		{
			float dot = ((b.Center().x - a.getStart().x) * (a.getEnd().x - a.getStart().x)) +
				((b.Center().y - a.getStart().y) * (a.getEnd().y - a.getStart().y)) /
				a.lengthSquared();

			Point2D closest;

			closest.x = a.getStart().x + (dot * (a.getEnd().x - a.getStart().x));
			closest.y = a.getStart().y + (dot * (a.getEnd().y - a.getStart().y));

			if (LibMath::Vector2::DistanceSquared(closest, b.Center()) <= b.Radius() * b.Radius())
				return true;

			return false;
		}

		bool Rectangle2DtoCircle2D(const Rectangle2D& a, const Circle2D& b)
		{
			Point2D TopRight(a.Center() + a.ExtentX() * 0.5f, a.Center() + a.ExtentY() * 0.5f);
			Point2D BottomRight(a.Center() + a.ExtentX() * 0.5f, a.Center() - a.ExtentY() * 0.5f);
			Point2D TopLeft(a.Center() - a.ExtentX() * 0.5f, a.Center() + a.ExtentY() * 0.5f);
			Point2D BottomLeft(a.Center() - a.ExtentX() * 0.5f, a.Center() - a.ExtentY() * 0.5f);

			if (Line2DtoCircle2D({ TopRight, BottomRight }, b))
				return true;
			else if (Line2DtoCircle2D({ BottomRight, BottomLeft }, b))
				return true;
			else if (Line2DtoCircle2D({ BottomLeft, TopLeft }, b))
				return true;
			else if (Line2DtoCircle2D({ TopLeft, TopRight }, b))
				return true;

			return false;
		}

		bool LinetoLine(const Line2D& a, const Line2D& b)
		{
			float firstDistance = ((b.getEnd().x - b.getStart().x) * (a.getStart().y - b.getStart().y) -
				(b.getEnd().y - b.getStart().y) * (a.getStart().x - b.getStart().x)) /
				((b.getEnd().y - b.getStart().y) * (a.getEnd().x - a.getStart().x) -
					(b.getEnd().x - b.getStart().x) * (a.getEnd().y - a.getStart().y));

			float secondDistance = ((a.getEnd().x - a.getStart().x) * (a.getStart().y - b.getStart().y) -
				(a.getEnd().y - a.getStart().y) * (a.getStart().x - b.getStart().x)) /
				((b.getEnd().y - b.getStart().y) * (a.getEnd().x - a.getStart().x) -
					(b.getEnd().x - b.getStart().x) * (a.getEnd().y - a.getStart().y));

			if (firstDistance >= 0 && firstDistance <= 1 && secondDistance >= 0 && secondDistance <= 1)
				return true;

			return false;
		}

		bool LinetoRectangle(const Line2D& a, const Rectangle2D& b)
		{

			float xRight = static_cast<float>(b.Center().x) + b.ExtentX() * 0.5f;
			float xLeft = static_cast<float>(b.Center().x) - b.ExtentX() * 0.5f;

			float yTop = static_cast<float>(b.Center().y) + b.ExtentY() * 0.5f;
			float yBottom = static_cast<float>(b.Center().y) - b.ExtentY() * 0.5f;

			if (LinetoLine(a, { {xLeft, yTop}, {xLeft, yBottom} }))
				return true;
			else if (LinetoLine(a, { { xLeft, yBottom }, {xRight, yBottom} }))
				return true;
			else if (LinetoLine(a, { {xRight, yBottom}, {xRight, yTop} }))
				return true;
			else if (LinetoLine(a, { {xRight, yTop}, {xLeft, yTop} }))
				return true;

			return false;
		}

		bool PointtoRectangle(const Point2D& a, const Rectangle2D& b)
		{
			if (a.x >= (b.Center().x - b.ExtentX() * 0.5) &&
				a.x <= (b.Center().x + b.ExtentX() * 0.5) &&
				a.y >= (b.Center().y - b.ExtentY() * 0.5) &&
				a.y <= (b.Center().y + b.ExtentY() * 0.5))
			{
				return true;
			}

			return false;
		}

		bool SATConvexForm(ConvexForm2D& a, ConvexForm2D& b)
		{
			for (int i = 0; i < a.getVertexArray().size(); ++i)
			{
				LibMath::Vector2 normedVector = LibMath::Vector2::toNormal(a[i]);
				if (checkMaxAndMin(normedVector, a, b))
					return true;
			}

			for (int i = 0; i < b.getVertexArray().size(); ++i)
			{
				LibMath::Vector2 normedVector = LibMath::Vector2::toNormal(b[i]);
				if (checkMaxAndMin(normedVector, a, b))
					return true;
			}

			return false;
		}

		bool checkMaxAndMin(Vector2& normedVector, ConvexForm2D& a, ConvexForm2D& b)
		{
			float   MAXONE = LibMath::Vector2::Dot(normedVector, a[0]), MINONE = LibMath::Vector2::Dot(normedVector, a[0]);
			float   MAXTWO = LibMath::Vector2::Dot(normedVector, b[0]), MINTWO = LibMath::Vector2::Dot(normedVector, b[0]);
			float   result = 0;

			for (unsigned int i = 1; i < a.getVertexArray().size(); i++)
			{
				result = LibMath::Vector2::Dot(normedVector, a[i]);

				if (result > MAXONE)
				{
					MAXONE = result;
					continue;
				}
				else if (result < MINONE)
				{
					MINONE = result;
				}
			}

			for (unsigned int i = 0; i < b.getVertexArray().size(); i++)
			{
				result = LibMath::Vector2::Dot(normedVector, b[i]);
				if (result > MAXTWO)
				{
					MAXTWO = result;
					continue;
				}
				else if (result < MINTWO)
				{
					MINTWO = result;
				}
			}

			if (!(MAXONE >= MINTWO && MAXTWO >= MINONE))
			{
				return false;
			}
			else
				return true;
		}

		bool isInTriangle(Triangle2D triangle, Point2D& point)
		{
			/* Calculate area of triangle ABC */
			float A = LibMath::Triangle2D::Area(triangle.a, triangle.b, triangle.c);

			/* Calculate area of triangle PBC */
			float A1 = LibMath::Triangle2D::Area(point, triangle.b, triangle.c);

			/* Calculate area of triangle PAC */
			float A2 = LibMath::Triangle2D::Area(triangle.a, point, triangle.c);

			/* Calculate area of triangle PAB */
			float A3 = LibMath::Triangle2D::Area(triangle.a, triangle.b, point);

			/* Check if sum of A1, A2 and A3 is same as A */
			return (A == A1 + A2 + A3);
		}
	}
}

