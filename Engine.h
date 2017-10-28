#include "Vector3.h"
#include "primitive.h"
#include "Scene.h"

namespace RayTracing
{
	class Engine
	{
		public:
			Engine();
			~Engine();
			Scene* GetScene(){return m_Scene;}
			Primitive* RayTrace(Ray* ray, Color& color, int depth, double r_index, double& dist );
			void InitRender();
			bool Render();
			void SetTarget(int m_Width, int m_Height, int*** m_Buffer)
			{
				m_Width = m_Width;
				m_Height = m_Height;
				buffer = m_Buffer;
			}

		private:
			Scene* m_Scene;
			int m_Width, m_Height, m_CurrentLine, m_Pos;
			int*** buffer;
	};

}