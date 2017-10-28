#include "Vector3.h"
#include "Ray.h"
//#include ""

namespace RayTracing
{
#define HIT 1
#define MISS 0
#define INPRIM -1

	

	class Material
	{
	public:
		Material();
		void SetColor(Color& color){ m_color = color;}
		void SetDiffuse(double diff){ m_diffuse = diff;}
		void SetReflection(double ref){m_reflection = ref;}
		void SetSpecular(double spect){m_specular = spect;}
		Color GetColor(){return m_color;}
		double GetDiffuse(){return m_diffuse;}
		double GetReflection(){return m_reflection;}
		double GetSpecular(){return m_specular;}

	private:
		Color m_color;
		double m_diffuse;
		double m_reflection;
		double m_specular;
	};

	class Primitive
	{
	public:
		enum{
			SPHERE=1,
			BOARD,
			TRIANGLE
		};
		
		virtual int InterSect(Ray* ray,double& dis)=0;
		Material* GetMaterial() {return &m_Material;}
		virtual Vector3 GetNormal(Vector3 Pos)=0;
		virtual Color GetColor() {return m_Material.GetColor();}
		virtual void Light(bool light) { m_Light=light;}
		bool IsLight() {return m_Light;}
		virtual int GetType()=0;
		void SetName(std::string& name){m_Name=name;}

	private:
		Material m_Material;
		bool m_Light;
		std::string m_Name;
	};

	//here is a sphere
	class Sphere : public Primitive
	{
	public:
		int GetType() {return SPHERE;}
		Sphere(Vector3 center, double radius){
			m_Center = center; 
			m_Radius = radius;
		}

		double GetRadius(){return m_Radius;}
		int InterSect(Ray* ray, double& dist);
		Vector3 GetCenter(){return m_Center;}
		Vector3 GetNormal(Vector3 pos){
			Vector3 v3 = pos - m_Center;
			NORMALIZE(v3)
				return v3;
		}

	private:
		Vector3 m_Center;
		double m_Radius;
	};

	//board such as walls , floors ceilings and so on
	class Board : public Primitive
	{
	public:
		int GetType(){return BOARD;}
		Board(Vector3 nor, float p)
		{
			m_Normal = nor;
			m_p = p;
		}
		int InterSect(Ray* ray, double& dist);


		float Get_P(){return m_p;}
		Vector3 GetNormal(Vector3 pos){
			m_Normal.Normalize();
			return m_Normal;
		}

	private:
		Vector3 m_Normal;
		float m_p;
	};


	//board such as walls , floors ceilings and so on
	class Triangle : public Primitive
	{
	public:
		int GetType(){return TRIANGLE;}
		
		Triangle(Vector3 nor, Vector3 a,Vector3 b,Vector3 c)
		{
			m_nor=nor;
			v0=a;
			v1=b;
			v2=c;
		}

		int InterSect(Ray* ray, double& dist);

		Vector3 GetNormal(Vector3 pos){
			m_nor.Normalize();
			return m_nor;
		}

	private:
		Vector3 m_nor;
		Vector3 v0;
		Vector3 v1;
		Vector3 v2;

	};

}