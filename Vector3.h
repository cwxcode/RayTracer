#ifndef _VECTOR3
#define _VECTOR3
#include <math.h>

namespace RayTracing{

#define NORMALIZE(A)	{double l=1/sqrtf(A.m_x*A.m_x+A.m_y*A.m_y+A.m_z*A.m_z);A.m_x*=l;A.m_y*=l;A.m_z*=l;}
#define DOT(A, B) (A.m_x * B.m_x + A.m_y * B.m_y + A.m_z * B.m_z)
#define TRACEDEPTH 5
#define LENGTH(A) (sqrt(A.m_x*A.m_x+A.m_y*A.m_y+A.m_z*A.m_z))
#define MUL(A, B) (Vector3(A.m_x * B.m_x, A.m_y * B.m_y, A.m_z * B.m_z))

#define CROSS(A,B) (Vector3(A.m_y*B.m_z-A.m_z*B.m_y,A.m_z*B.m_x-A.m_x*B.m_z,A.m_x*B.m_y-A.m_y*B.m_x))

	class Vector3
	{
	public:
		Vector3(double x, double y, double z) :
		  m_x(x), m_y(y), m_z(z){}

		  Vector3() :
		  m_x(0), m_y(0), m_z(0){}


		  Vector3 operator = (Vector3 Vector3)
		  {
			  this->m_x = Vector3.m_x;
			  this->m_y = Vector3.m_y;
			  this->m_z = Vector3.m_z;

			  return *this;
		  }

		  bool operator ==(Vector3 b)
		  {
			  if(this->m_x == b.m_x && this->m_y == b.m_y && this->m_z == b.m_z)
				  return true;
			  else
				  return false;
		  }

		  Vector3(Vector3& ax)
		  {
			  m_x = ax.m_x;
			  m_y = ax.m_y;
			  m_z = ax.m_z;			
		  }

		  Vector3 Normalize()
		  {
			  double result = sqrt( pow(m_x, 2)  + pow(m_y, 2) + pow(m_z, 2));
			  m_x = m_x / result;
			  m_y = m_y / result;
			  m_z = m_z / result; 
			  return *this;
		  }

		  double operator * (Vector3 v3)
		  {
			  double result = 0;
			  result = this->m_x * v3.m_x +	this->m_y * v3.m_y + this->m_z * v3.m_z;
			  return result;
		  }

		  Vector3 operator * (double f)
		  {
			  Vector3* vv3 = new Vector3();
			  vv3->m_x = this->m_x * f;
			  vv3->m_y = this->m_y * f;
			  vv3->m_z = this->m_z * f;

			  return *vv3;
		  }

		  Vector3 operator -(Vector3 v3)
		  {
			  Vector3* vv3 = new Vector3();
			  vv3->m_x = this->m_x - v3.m_x;
			  vv3->m_y = this->m_y - v3.m_y;
			  vv3->m_z = this->m_z - v3.m_z;

			  return * vv3;
		  }

		  Vector3 operator +(Vector3 v3)
		  {
			  Vector3* vv3 = new Vector3();
			  vv3->m_x = this->m_x + v3.m_x;
			  vv3->m_y = this->m_y + v3.m_y;
			  vv3->m_z = this->m_z + v3.m_z;

			  return * vv3;
		  }

	public:
		double m_x, m_y, m_z;
	};


	typedef Vector3 Color;


};

#endif