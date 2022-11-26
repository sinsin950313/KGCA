//#pragma once
//
//#include "PhysicsVector.h"
//
//namespace SSB
//{
//	template<int dimension>
//	class Rigidbody
//	{
//	private:
//		float _mass;
//		PhysicsVector<dimension> _acc;
//		PhysicsVector<dimension> _vel;
//
//	public:
//		Rigidbody(float mass = 1) : _mass(mass) { }
//
//	public:
//		void AddForce(const PhysicsVector<dimension>& newForce);
//		void Calculate(float deltaTime);
//
//	public:
//		float GetMass() { return _mass; }
//		PhysicsVector<dimension> GetAcceleration() { return _acc; }
//		PhysicsVector<dimension> GetVelocity() { return _vel; }
//	};
//
//	template<int dimension>
//	inline void Rigidbody<dimension>::AddForce(const PhysicsVector<dimension>& newForce)
//	{
//		_acc += newForce / _mass;
//	}
//
//	template<int dimension>
//	inline void Rigidbody<dimension>::Calculate(float deltaTime)
//	{
//		_vel += _acc * deltaTime;
//
//		_acc.Clear();
//	}
//
//	using Rigidbody2D = Rigidbody<2>;
//	using Rigidbody3D = Rigidbody<3>;
//}
