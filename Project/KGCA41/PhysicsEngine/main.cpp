#include "Core.h"

//class QuadTreeCoreTest : public Core<2>
//{
//private:
//	int _width = 100;
//	int _height = 100;
//
//public:
//	QuadTreeCoreTest() : Core<2>(new QuadTree(100, 100, 3)) { _player = new Object2D(new Rectangle(0, 0, 10, 10), Rigidbody2D()); }
//	void Init() override;
//	void Run() override;
//	void Simulate(float deltaTime) override;
//	void Render() override;
//};
//
//class OctTreeCoreTest : public Core<3>
//{
//private:
//	Object3D* _player = nullptr;
//
//public:
//	OctTreeCoreTest() : Core<3>(new OctTree(100, 100, 100, 3)), _player(new Object3D(new Box(Vector3D(Vector3DData{ 0, 0, 0 }), 10, 10, 10), Rigidbody3D())) { }
//	void Init() override;
//};
//
//int main()
//{
//	QuadTreeCoreTest qtCore;
//	qtCore.Init();
//	qtCore.Run();
//
//	//OctTreeCoreTest otCore;
//	//otCore.Init();
//	//otCore.Run();
//}
//
//void QuadTreeCoreTest::Init()
//{
//	float centerX = (rand() % _width) - (_width / 2);
//	float centerY = (rand() % _height) - (_height / 2);
//	float width = rand() % 10 + 1.0f;
//	float height = rand() % 10 + 1.0f;
//	Object2D* object = new Object2D(new Rectangle(centerX, centerY, width, height), Rigidbody2D());
//	AddStaticObject(object);
//}
//
//void QuadTreeCoreTest::Run()
//{
//	_player->GetRigidBody()->AddForce(Vector2D(Vector2DData{ 10, 10 }));
//
//	Core::Run();
//}
//
//void QuadTreeCoreTest::Simulate(float deltaTime)
//{
//	Core::Simulate(deltaTime);
//
//	_collidedObjects = _ct->GetCollidedObjects(_player);
//}
//
//void OctTreeCoreTest::Init()
//{
//}
//
//void QuadTreeCoreTest::Render()
//{
//	const Volume<2>* playerVolume = _player->GetVolume();
//	playerVolume->Print();
//	
//	for (auto iter = _collidedObjects.begin(); iter != _collidedObjects.end(); ++iter)
//	{
//		const Volume<2>* tmp = (*iter)->GetVolume();
//		tmp->Print();
//	}
//}
