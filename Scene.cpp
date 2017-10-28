#include "Vector3.h"
#include "Scene.h"
#include "primitive.h"

namespace RayTracing
{

	Scene::~Scene(){delete m_Primitive;}

	void Scene::InitScene()
	{
		m_Primitive = new Primitive* [20];

		int mi=0;

		//ground plane
		m_Primitive[mi] = new Board( Vector3( 0, 1, 0 ), 6 );
		m_Primitive[mi]->SetName( std::string("plane") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0.8 );	
		m_Primitive[mi]->GetMaterial()->SetDiffuse(0.8);
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.9, 0.9, 0.3) );
		m_Primitive[mi]->Light( false);
        
		mi++;  //1
		//ground plane
		m_Primitive[mi] = new Board( Vector3( 1, 0, 0 ), 10 );
		m_Primitive[mi]->SetName( std::string("plane2") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0);	
		m_Primitive[mi]->GetMaterial()->SetDiffuse(0.8);
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.3, 0.9, 0.3) );
		m_Primitive[mi]->Light( false);

		mi++;  //2
		//ground plane
		m_Primitive[mi] = new Board( Vector3( 0, 0, 1 ), 15 );
		m_Primitive[mi]->SetName( std::string("plane2") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0.6 );	
		m_Primitive[mi]->GetMaterial()->SetDiffuse(0.8);
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.7, 0.9, 0.6) );
		m_Primitive[mi]->Light( false);

		mi++;  //3
		//ground plane
		m_Primitive[mi] = new Board( Vector3( -1, 0, 0 ), 10 );
		m_Primitive[mi]->SetName( std::string("plane2") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0 );	
		m_Primitive[mi]->GetMaterial()->SetDiffuse(0.8);
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.3, 0.5, 0.9) );
		m_Primitive[mi]->Light( false);

		//mi++;//4
		//// light source 1
		//m_Primitive[mi] = new Sphere( Vector3( 0, 3, 0 ), 0.1 );
		//m_Primitive[mi]->Light( true);
		//m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.8, 0.8,0.81 ) );
		//
		mi++;//5
		// light source 2
		m_Primitive[mi] = new Sphere( Vector3( 2, 10, 2 ), 0.1 );
		m_Primitive[mi]->Light( true );
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 1.0, 1.0, 1.0 ) );

		mi++;//6
		// small sphere
		m_Primitive[mi] = new Sphere( Vector3( -2, 0, -2 ), 1 );
		m_Primitive[mi]->SetName( std::string("small sphere") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0.5 );	
		m_Primitive[mi]->Light( false);
		m_Primitive[mi]->GetMaterial()->SetDiffuse( 0.4 );
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.7, 0.0,0.9 ) );

		mi++; //7
		// a little bigger sphere
		m_Primitive[mi] = new Sphere( Vector3( 3, 0, -2 ), 1 );
		m_Primitive[mi]->SetName( std::string("small sphere") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0.5 );	
		m_Primitive[mi]->Light( false);
		m_Primitive[mi]->GetMaterial()->SetDiffuse( 0.4 );
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.0, 0.7, 1.0 ) );

		mi++; //7
		// a little bigger sphere
		m_Primitive[mi] = new Sphere( Vector3( 3, -2, -3 ), 2 );
		m_Primitive[mi]->SetName( std::string("small sphere2") );
		m_Primitive[mi]->GetMaterial()->SetReflection( 0.3 );	
		m_Primitive[mi]->Light( false);
		m_Primitive[mi]->GetMaterial()->SetDiffuse( 0.4 );
		m_Primitive[mi]->GetMaterial()->SetColor( Color( 0.5, 0.7, 0.3 ) );

		int prim = 8;

		m_Primitives = prim;

	}
}