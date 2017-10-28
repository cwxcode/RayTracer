#include <string>
#include "Vector3.h"

namespace RayTracing
{
	class Ray
	{
		public:
			Ray(Vector3& origin,Vector3& direction):m_Origin(origin)
			{
				NORMALIZE(direction)
				m_Direction=direction;
			}
			Ray():m_Origin(Vector3(0,0,0)),m_Direction(Vector3(0,0,0)){}
			Vector3 GetOrigin() {return m_Origin;}
			Vector3 GetDirection() {return m_Direction;}
			void SetOrigin(Vector3 v3)
			{
				m_Origin=v3;
			}
			void SetDirection(Vector3 v3)
			{
				NORMALIZE(v3);
				m_Direction=v3;
			}
		private:
			Vector3 m_Origin;
			Vector3 m_Direction;
	};

}