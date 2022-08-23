#pragma once

//#include <vector>
//#include "CollisionTree.h"
//#include "Object.h"
//
//template<int dimension>
//class Core
//{
//protected:
//	CollisionTree<dimension>* _ct = nullptr;
//private:
//	std::vector<Object<dimension>*> _staticObjects;
//	//std::vector<Object<dimension>*> _dynamicObjects;
//
//public:
//	Core(CollisionTree<dimension>* ct);
//	~Core();
//
//public:
//	void AddStaticObject(Object<dimension>* object);
//	//void AddDynamicObject(Object<dimension>* object);
//
//public:
//	virtual void Init() = 0;
//
//public:
//	virtual void Run();
//
//protected:
//	virtual void Simulate(float deltaTime);
//
//protected:
//	Object<dimension>* _player = nullptr;
//	std::vector<Object<dimension>*> _collidedObjects;
//	virtual void Render() = 0;
//};
//
//template<int dimension>
//Core<dimension>::Core(CollisionTree<dimension>* ct) : _ct(ct)
//{
//
//}
//
//template<int dimension>
//Core<dimension>::~Core()
//{
//	delete _ct;
//	for (auto iter = _staticObjects.begin(); iter != _staticObjects.end(); ++iter)
//	{
//		delete (*iter);
//	}
//	//for (auto iter = _dynamicObjects.begin(); iter != _dynamicObjects.end(); ++iter)
//	//{
//	//	delete (*iter);
//	//}
//}
//
//template<int dimension>
//inline void Core<dimension>::AddStaticObject(Object<dimension>* object)
//{
//	_staticObjects.push_back(object);
//	_ct->AddObject(object);
//}
////
////template<int dimension>
////inline void Core<dimension>::AddDynamicObject(Object<dimension>* object)
////{
////	_objects.push_back(object);
////	qt.AddObject(object);
////}
//
//template<int dimension>
//void Core<dimension>::Run()
//{
//	Simulate(0.1f);
//	Render();
//}
//
//template<int dimension>
//void Core<dimension>::Simulate(float deltaTime)
//{
//	//auto dynamicObjects = _dynamicObjects;
//	//_dynamicObjects.clear();
//
//	//for (auto iter = dynamicObjects.begin(); iter != dynamicObjects.end(); ++iter)
//	//{
//	//	(*iter)->GetRigidBody()->Calculate(deltaTime);
//	//	PhysicsVector<dimension> pos = (*iter)->GetVolume()->GetCenter() + (*iter)->GetRigidBody()->GetVelocity() * deltaTime;
//	//	(*iter)->GetVolume()->Reposition(pos);
//	//	_dynamicObjects.push_back(*iter);
//	//}
//}
