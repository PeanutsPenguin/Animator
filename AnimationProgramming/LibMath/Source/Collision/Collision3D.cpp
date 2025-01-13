#include "LibMath/Collision/Collision3D.h"

#define AABB_NORMAL_AXIS 3

namespace LibMath 
{
	/*************PLANE 3D**************/
	Plane::Plane(float a, float b, float c)
	{
		this->planeVector.x = a;
		this->planeVector.y = b;
		this->planeVector.z = c;
	}
	Plane::Plane(const LibMath::Vector3& a)
	{
		this->planeVector = a;
	}

	/*************RAY 3D**************/
	Point3D Ray3D::getOrigin() const
	{
		return this->origin;
	}
	Point3D Ray3D::getDirection() const
	{
		return this->direction;
	}

	/*************SPEHERE 3D**************/
	Point3D Sphere::getCenter() const
	{
		return this->center;
	}
	float Sphere::getRadius() const
	{
		return this->radius;
	}

	/*************AABB 3D**************/
	Point3D AABB::getCenter() const
	{
		return this->center;
	}
	float AABB::ExtentX() const
	{
		return this->width;
	}
	float AABB::ExtentY() const
	{
		return this->height;
	}
	float AABB::ExtentZ() const
	{
		return this->depth;
	}

	/*************OOBB 3D**************/
	Point3D OOBB::getCenter() const
	{
		return this->center;
	}
	float OOBB::ExtentX() const
	{
		return this->width;
	}
	float OOBB::ExtentY() const
	{
		return this->height;
	}
	float OOBB::ExtentZ() const
	{
		return this->depth;
	}
	LibMath::Mat4 OOBB::getRotation()
	{
		return this->rotation;
	}


	float Triangle3D::area() 
	{ 
		Point3D AB(this->b.x - this->a.x, this->b.y - this->a.y, this->b.z - this->a.z);
		Point3D AC(this->c.x - this->a.x, this->c.y - this->a.y, this->c.z - this->a.z);

		return (LibMath::Vector3::cross(AB, AC).Magnitude() * 0.5f);
	}
	namespace CollisionCheck
	{
		bool PointToSphere(const Point3D& a, const Sphere& b)
		{
			float distanceSquared = LibMath::Vector3::distanceSquared(a, b.getCenter());

			return distanceSquared < (b.getRadius() * b.getRadius());
		}	

		bool RayToSphere(const Ray3D& a, const Sphere& b)
		{
			LibMath::Vector3 dif = b.getCenter() - a.getOrigin();

			if (LibMath::Vector3::dot(a.getDirection(), dif) <= 0)
				return false;

			LibMath::Vector3 proj = LibMath::Vector3::Project(b.getCenter(), a.getDirection());

			return LibMath::Vector3::distanceSquared(proj, b.getCenter()) < (b.getRadius() * b.getRadius());
		}
	
		bool SpheretoSphere(const Sphere& a, const Sphere& b)
		{
			float distanceSquared = (a.getCenter().x - b.getCenter().x) * (a.getCenter().x - b.getCenter().x) +
									(a.getCenter().y - b.getCenter().y) * (a.getCenter().y - b.getCenter().y) +
									(a.getCenter().z - b.getCenter().z) * (a.getCenter().z - b.getCenter().z);

			return distanceSquared < ((a.getRadius() + b.getRadius()) * (a.getRadius() + b.getRadius()));
		}		
	
		bool PointToAABB(const Point3D& a, const AABB& b)
		{
			float minX = b.getCenter().x - (b.ExtentX() * 0.5f);
			float maxX = b.getCenter().x + (b.ExtentX() * 0.5f);

			float minY = b.getCenter().y - (b.ExtentY() * 0.5f);
			float maxY = b.getCenter().y + (b.ExtentY() * 0.5f);

			float minZ = b.getCenter().z - (b.ExtentZ() * 0.5f);
			float maxZ = b.getCenter().z + (b.ExtentZ() * 0.5f);

			return (
				a.x >= minX &&
				a.x <= maxX &&
				a.y >= minY &&
				a.y <= maxY &&
				a.z >= minZ &&
				a.z <= maxZ);
		}
	
		bool SphereToAABB(const Sphere& a, const AABB& b)
		{
			float squaredDistance = 0.0f;

			LibMath::Vector3 minAABB(b.getCenter().x - (b.ExtentX() * 0.5f), 
									 b.getCenter().y - (b.ExtentY() * 0.5f), 
									 b.getCenter().z - (b.ExtentZ() * 0.5f));

			LibMath::Vector3 maxAABB(b.getCenter().x + (b.ExtentX() * 0.5f),
									 b.getCenter().y + (b.ExtentY() * 0.5f),
									 b.getCenter().z + (b.ExtentZ() * 0.5f));

			LibMath::Vector3 sphereCenter = a.getCenter();

			for (int axis = 0; axis < AABB_NORMAL_AXIS; axis++) 
			{
				/* If the center is between the min and max, then the distance is 0 */
				if (sphereCenter[axis] < minAABB[axis])
					squaredDistance += (minAABB[axis] - sphereCenter[axis]) * (minAABB[axis] - sphereCenter[axis]);
				else if (sphereCenter[axis] > maxAABB[axis])
					squaredDistance += (sphereCenter[axis] - maxAABB[axis]) * (sphereCenter[axis] - maxAABB[axis]);
			}

			return  squaredDistance <= (a.getRadius() * a.getRadius());
		}
	
		bool AABBToAABB(const AABB& a, const AABB& b)
		{
			float minXOne = a.getCenter().x - (a.ExtentX() * 0.5f);
			float maxXOne = a.getCenter().x + (a.ExtentX() * 0.5f);

			float minYOne = a.getCenter().y - (a.ExtentY() * 0.5f);
			float maxYOne = a.getCenter().y + (a.ExtentY() * 0.5f);

			float minZOne = a.getCenter().z - (a.ExtentZ() * 0.5f);
			float maxZOne = a.getCenter().z + (a.ExtentZ() * 0.5f);

			float minXTwo = b.getCenter().x - (b.ExtentX() * 0.5f);
			float maxXTwo = b.getCenter().x + (b.ExtentX() * 0.5f);

			float minYTwo = b.getCenter().y - (b.ExtentY() * 0.5f);
			float maxYTwo = b.getCenter().y + (b.ExtentY() * 0.5f);

			float minZTwo = b.getCenter().z - (b.ExtentZ() * 0.5f);
			float maxZTwo = b.getCenter().z + (b.ExtentZ() * 0.5f);

			return	minXOne <= maxXTwo &&
					maxXOne >= minXTwo &&
					minYOne <= maxYTwo &&
					maxYOne >= minYTwo &&
					minZOne <= maxZTwo &&
					maxZOne >= minZTwo;
		}

		bool isInTriangle(Triangle3D triangle, Point3D pt)
		{
			/* Calculate area of triangle ABC */
			float A = Triangle3D(triangle.a, triangle.b, triangle.c).area();

			/* Calculate area of triangle PBC */
			float A1 = Triangle3D(pt, triangle.b, triangle.c).area();

			/* Calculate area of triangle PAC */
			float A2 = Triangle3D(triangle.a, pt, triangle.c).area();

			/* Calculate area of triangle PAB */
			float A3 = Triangle3D(triangle.a, triangle.b, pt).area();

			/* Check if sum of A1, A2 and A3 is same as A */ /* #barycentric */
			return (A == A1 + A2 + A3);
		}
	} // namespace CollisionCheck
} // namespace LibMath
