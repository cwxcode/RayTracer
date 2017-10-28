#include "primitive.h"
#include "Vector3.h"

namespace RayTracing
{

	Material::Material()
	{
		m_color = Color(0.2, 0.2, 0.2);
		m_diffuse = 0.2;
		m_specular = 0.8;	
	}

	int Sphere::InterSect(Ray* ray, double& dist)
	{
		Vector3 v = ray->GetOrigin() - this->GetCenter();
		int retval = MISS;
		double alpha = v * ray->GetDirection() * -1;

		Vector3 q = ray->GetOrigin() + ray->GetDirection() * alpha ;

		double b = (q - this->GetCenter()) *  (q - this->GetCenter()) ;
		if(b > pow(this->GetRadius(), 2) && alpha > 0)
		{
			retval = MISS;
		}else if(b < pow(this->GetRadius(), 2))
		{
			double a = sqrt(pow(this->GetRadius(), 2) - b);
			if(alpha >= a && alpha > 0)
			{
				if(dist > alpha - a || dist < 0)
				{
					retval = HIT;
					dist = alpha - a;
				}
			}
		}
		return retval;
	}


	//int Board::InterSect(Ray* ray, double& a_dist)
	//{
	//	int retval = MISS;
	//	double c = this->GetNormal(Vector3(0, 0, 0)) * ray->GetDirection();
	//	double alpha = this->Get_D() - (ray->GetOrigin() * this->GetNormal(Vector3(0, 0, 0)));
	//	alpha /= c;

	//	if(c == 0)
	//	{
	//		retval = MISS; 
	//	}
	//	else if(alpha < 0)
	//	{
	//		retval = MISS;
	//	}
	//	else 
	//	{
	//		if(alpha < a_dist || a_dist < 0)
	//		{
	//			a_dist = alpha;
	//			retval = HIT;
	//		}
	//	}
	//	return retval;
	//}

	int Board::InterSect(Ray* ray, double& a_dist)
	{
		int retval = MISS;
		
		float donom=DOT(m_Normal,ray->GetDirection());

		float nom=DOT(m_Normal,ray->GetOrigin()) + m_p;
		
		float dist=-(nom/donom);
		
			if(donom == 0)
			{
				retval = MISS; 
			}
			else if(dist < 0)
			{
				retval = MISS;
			}
			else 
			{
				if(dist < a_dist || a_dist < 0)
				{
					a_dist = dist;
					retval = HIT;
				}
			}
			return retval;
	}
	

	int Triangle::InterSect(Ray* ray,double& dist)
	{
		Vector3 edge1=v1-v0;
		Vector3 edge2=v2-v0;
		Vector3 pVec=CROSS(ray->GetDirection(),edge2);
		float det=DOT(edge1,pVec);
		
		Vector3 tVec;
		
		if(det>0)
		{
			tVec=ray->GetOrigin()-v0;
		}
		else
		{
			tVec=v0-ray->GetOrigin();
			det=-det;
		}

		if(det<0.001f) 
			return 0;

		float u=DOT(tVec,pVec);
		if(u<0.0f || u>det) 
			return false;
		
		Vector3 qvec=MUL(tVec,edge1);
		float v=DOT(ray->GetDirection(),qvec);

		if(v<0.0f || u+v>det) 
			return 0;
		
		float t=DOT(edge2,qvec);
		float fInvDet=1.0f/det;

		t=t*fInvDet;

		if(t<dist || dist<0)
		{
			dist=t;
			return 1;
		}


		return 0;
	}
}