#pragma once

#include "Common.h"
#include "DX2DGameObject.h"

namespace SSB
{
	class DX2DProjectController : public Common
	{
	protected:
		DX2DGameObject* _controlledObject;

	public:
		DX2DProjectController(DX2DGameObject* controlledObject);
		~DX2DProjectController();

	protected:
		virtual void Logic() = 0;

	public:
		void SetControlledObject(DX2DGameObject* controlledObject);

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};

	class PlayerController : public DX2DProjectController
	{
	public:
		PlayerController(DX2DGameObject* controlledObject);
		~PlayerController();

	protected:
		void Logic() override;

	public:
		bool Init() override;
		bool Frame() override;
		bool Render() override;
		bool Release() override;
	};
	
	//class AIController : public DX2DProjectController
	//{

	//};
}
