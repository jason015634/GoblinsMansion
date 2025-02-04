#pragma once

#include "ECS.h"
#include "Matrix4x4.h"
#include "Vector3D.h"

struct Transform
{
	ECS_DECLARE_TYPE

		Transform() = default;
	explicit Transform(const Vector3D xyz_Position, const Vector3D xyz_Rotation = { 0.f, 0.f, 0.f }, const Vector3D xyz_Scale = { 1.f, 1.f, 1.f })
		: m_Position(xyz_Position)
		, m_Rotation(xyz_Rotation)
		, m_Scale(xyz_Scale)
	{
	
	}

	std::string m_ComponentName = "Transform";

	Vector3D m_Rotation = { 0.f, 0.f, 0.f };
	Vector3D m_Position = { 0.f, 0.f, 0.f };
	Vector3D m_Scale = { 1.f, 1.f, 1.f };

	Matrix4x4 m_RelativeMatrix;
	Matrix4x4 m_WorldMatrix;

	bool m_FreezeRotationX = false;
	bool m_FreezeRotationY = false;
	bool m_FreezeRotationZ = false;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Transform, m_ComponentName, m_Position, m_Rotation, m_Scale, m_FreezeRotationX, m_FreezeRotationY, m_FreezeRotationZ)
};

ECS_DEFINE_TYPE(Transform)

