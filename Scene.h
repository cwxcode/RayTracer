#include "Vector3.h"


namespace RayTracing
{
	class Primitive;
	class Scene
	{
	public:
		Scene(){
			m_Primitives=0;
			m_Primitive=0;
		}
		~Scene();
		void InitScene();
		int GetPrimitives(){return m_Primitives;}
		Primitive* GetPrimitive(int i){ return m_Primitive[i];}
private:
		int m_Primitives;
		Primitive** m_Primitive;

	};


}