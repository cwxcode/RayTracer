#include "Engine.h"

namespace RayTracing
{

	Engine::Engine()
	{
		this->m_Scene = new Scene();
		m_Scene->InitScene();
	}

	Engine::~Engine()
	{
		delete m_Scene;
	}

	Primitive* Engine::RayTrace(Ray* ray, Color& acc, int depth, double r_index, double& dist)
	{
		if(depth > 3)
			return 0;
		Vector3 pi;
		Primitive* prim = 0;
		int result;
//同每一个物体求交，得到最近点
		for(int s = 0; s < m_Scene->GetPrimitives(); s++)
		{
			Primitive* pr = m_Scene->GetPrimitive(s);
			int res;
			if(res = pr->InterSect(ray, dist))
			{
				prim = pr;
				result = res;	
			}		
		}

		if(!prim)
		{
			return 0;
		}
//如果是光 直接返回颜色
		if(prim->IsLight())
		{
			acc = Color(1, 1, 1);
		}else
		{
			pi = ray->GetOrigin() + ray->GetDirection() * dist;
//如果物体不是光，则从该点向光源发出射线
			for ( int l = 0; l < m_Scene->GetPrimitives(); l++ )
			{
				Primitive* p = m_Scene->GetPrimitive(l);
				double shade = 1;
				if(p->IsLight())
				{
					Primitive* light = p;


					if(light->GetType() == Primitive::SPHERE)
					{
						Vector3 L = ((Sphere*)light)->GetCenter() - pi;
						double distance = LENGTH(L);
						L = L * (1 / distance);
						Ray r = Ray(pi + L * 0.001, L);
                       //交点与光源的直线被物体档住，则阴影
						for ( int s = 0; s < m_Scene->GetPrimitives(); s++ )
						{
							Primitive* pr = m_Scene->GetPrimitive( s );
							if ((pr != light) && pr != prim && (pr->InterSect( &r, distance )))
							{
								shade = 0;
								break;
							}
						}
					}		
					//没被档住
					if(shade > 0)
					{
						Vector3 L = ((Sphere*)light)->GetCenter() - pi;
						L.Normalize();
						Vector3 N = prim->GetNormal(pi);

						//计算环境光
						if(prim->GetMaterial()->GetDiffuse() > 0)
						{
							double dot = DOT( L, N );
							if(dot > 0)
							{
								double diff = dot * prim->GetMaterial()->GetDiffuse() * shade;
								acc = acc + MUL(light->GetMaterial()->GetColor(), prim->GetMaterial()->GetColor()) * diff;
							}

						}

						//计算镜面光
						if(prim->GetMaterial()->GetSpecular() > 0)
						{
							Vector3 V = ray->GetDirection();
							Vector3 R = L -  N * 2 * DOT( L, N );
							double dot = DOT(V, R);

							if(dot > 0)
							{
								double spec = pow( dot, 20 ) * prim->GetMaterial()->GetSpecular() * shade;
								// add specular component to ray color
								acc = acc + light->GetMaterial()->GetColor() * spec;
							}
						}


					}		
				}
			}


			//如果表面有反射，则从该点，沿反射方向，发出射线，遍历~~ 
			double ref = prim->GetMaterial()->GetReflection();
			if(ref > 0 && depth < TRACEDEPTH)
			{
				Vector3 N = prim->GetNormal(pi);
				Vector3 R = ray->GetDirection() - N * DOT(ray->GetDirection() , N) * 2;
				Color rcol(0, 0, 0);
				double dis;
				RayTrace(&Ray(pi + R * 0.001, R), rcol, depth + 1, r_index, dis);
				acc = acc + MUL(rcol, prim->GetMaterial()->GetColor()) * ref; 
			}

		}

		return prim;

	}

	void Engine::InitRender()
	{


	}

}