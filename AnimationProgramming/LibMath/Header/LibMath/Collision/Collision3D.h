#include "LibMath/Vector.h"
#include "LibMath/Matrix/Mat4x4.h"

#include <cmath>

namespace LibMath 
{
	typedef LibMath::Vector3 Point3D;

	class Plane
	{
	public:
		Plane() = default;

		Plane(float a, float b, float c);

		Plane(const LibMath::Vector3&);

		Plane(const Plane&) = default;

		Plane(Plane&&) = default;

		Plane& operator=(const Plane&) = default;

		~Plane() = default;

	private:
		Vector3 planeVector;
 	};

	class Triangle3D
	{
	public:
		Triangle3D() = default;

		Triangle3D(const Triangle3D&) = default;

		Triangle3D(Triangle3D&&) = default;

		Triangle3D(const Point3D& a, const Point3D& b, const Point3D& c) : a(a), b(b), c(c) {};

		Triangle3D& operator=(const Triangle3D&) = default;

		float area();

		Point3D a;
		Point3D b;
		Point3D c;
	};

	class Ray3D
	{
	public :

		Ray3D() = default;

		Ray3D(const LibMath::Vector3& a, const LibMath::Vector3& b) : origin(a), direction(b) {};

		Ray3D(const Ray3D&) = default;

		Ray3D(Ray3D&&) = default;

		Ray3D& operator=(const Ray3D&) = default;

		Point3D getOrigin() const;

		Point3D getDirection() const;

		~Ray3D() = default;
	private:
		Point3D origin;
		Point3D direction;
	};

	class Sphere 
	{
	public:

		Sphere() = default;

		Sphere(const LibMath::Vector3& a, const float b) : center(a), radius(b) {};

		Sphere(const Sphere&) = default;

		Sphere(Sphere&&) = default;

		Sphere& operator=(const Sphere&) = default;

		Point3D getCenter() const;

		float getRadius() const;

		~Sphere() = default;
	private:
		Point3D center;
		float radius;
	};

	class AABB 
	{
	public:

		AABB() = default;

		AABB(const LibMath::Vector3& a, const float b, const float c, const float d) : center(a), width(b), height(c), depth(d) {};

		AABB(const AABB&) = default;

		AABB(AABB&&) = default;

		AABB& operator=(const AABB&) = default;

		Point3D getCenter() const;

		float ExtentX() const;

		float ExtentY() const;

		float ExtentZ() const;

		~AABB() = default;
	private:
		Point3D center;
		float width;
		float height;
		float depth;
	};

	class OOBB
	{
	public:

		OOBB() = default;

		OOBB(const LibMath::Vector3& a, const float b, const float c, const float d) : center(a), width(b), height(c), depth(d) {};

		OOBB(const OOBB&) = default;

		OOBB(OOBB&&) = default;

		OOBB& operator=(const OOBB&) = default;

		Point3D getCenter() const;

		float ExtentX() const;

		float ExtentY() const;

		float ExtentZ() const;

		LibMath::Mat4 getRotation();

		~OOBB() = default;
	private:
		Point3D center;
		float width;
		float height;
		float depth;

		LibMath::Mat4 rotation;
	};

	namespace CollisionCheck 
	{
		bool PointToSphere(const Point3D&, const Sphere&);		//Check collision with a Point and a Sphere

		bool RayToSphere(const Ray3D&, const Sphere&);			//Check collision with a ray and a sphere

		bool SpheretoSphere(const Sphere&, const Sphere&);		//Check collision with two Spheres

		bool PointToAABB(const Point3D&, const AABB&);			//Check collision with a point and a rectangle

		bool SphereToAABB(const Sphere&, const AABB&);			//Check collision with a sphere and a rectangle

		bool AABBToAABB(const AABB&, const AABB&);				//Check collision with two rectangles

		bool isInTriangle(Triangle3D triangle, Point3D point);
	}
}