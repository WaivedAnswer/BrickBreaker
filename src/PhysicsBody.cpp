//PhysicsBody.cpp
#include "PhysicsBody.h"
#include <iostream>

PhysicsBody::PhysicsBody(Collider* collider, Vector velocity, Point position, bool isKinematic)
{
	m_collider = collider;
	m_velocity = velocity;
	m_position = position;
	m_isKinematic = isKinematic;
	if(m_collider != nullptr)
	{
		m_collider->SetCentre(m_position);
	}
}
PhysicsBody::~PhysicsBody()
{
	if(m_collider != nullptr)
	{
		delete m_collider;
		m_collider = nullptr;
	}
}

bool PhysicsBody::CheckCollision(PhysicsBody* other, Point& p)
{
	if(other == nullptr )
	{
		return false;
	}

	Collider* oCollider = other->GetCollider();

	if(oCollider == nullptr || m_collider == nullptr )
	{
		return false;
	}

	return m_collider->CheckCollision(oCollider, p);
	
}


void PhysicsBody::HandleCollision(PhysicsBody* other, const Point& p)
{
	if(other == nullptr)
	{
		return;
	}

	Collider* oCollider = other->GetCollider();

	if(oCollider == nullptr || m_collider == nullptr )
	{
		return;
	}


	//TODO implement moving away from other collider
	if(m_isKinematic)
	{
		//std::cout << "Intersect x: " <<p.x << " y: " <<p.y <<"\n";
		//right now just reflections, no actual momentum transfer
		Vector osurfaceNormal = oCollider->GetSurfaceNormal(p);
		//std::cout << "Original Vector x: " <<m_velocity.x << " y: " <<m_velocity.y <<"\n";
		//std::cout << "Normal Vector x: " <<osurfaceNormal.x << " y: " <<osurfaceNormal.y <<"\n";
		Vector reflect = m_velocity - 2.0*Dot(m_velocity, osurfaceNormal)*osurfaceNormal;
		//std::cout << "Reflect Vector x: " <<reflect.x << " y: " <<reflect.y <<"\n";
		
		this->SetVelocity(reflect);
	}
	if(other->IsKinematic())
	{
		//std::cout << "Intersect x: " <<p.x << " y: " <<p.y <<"\n";
		//right now just reflections
		Vector surfaceNormal = m_collider->GetSurfaceNormal(p);
		Vector oVelocity = other->GetVelocity();
		//std::cout << "Original Vector x: " <<oVelocity.x << " y: " <<oVelocity.y <<"\n";
		//std::cout << "Normal Vector x: " <<surfaceNormal.x << " y: " <<surfaceNormal.y <<"\n";
		Vector reflect = oVelocity - 2.0*Dot(oVelocity, surfaceNormal)*surfaceNormal;
		//std::cout << "Reflect Vector x: " <<reflect.x << " y: " <<reflect.y <<"\n";
		other->SetVelocity(reflect);
	}
	
}

void PhysicsBody::Move(float time)
{
	m_position = m_position + time/1000.0 * m_velocity;
	if(m_collider != nullptr)
	{
		m_collider->SetCentre(m_position);
	}
}

void PhysicsBody::UnMove(float time)
{
	m_position = m_position - time/1000.0 * m_velocity;
	if(m_collider != nullptr)
	{
		m_collider->SetCentre(m_position);
	}
}

Collider* PhysicsBody::GetCollider()
{
	return m_collider;
}

Vector PhysicsBody::GetVelocity()
{
	return m_velocity;
}

void PhysicsBody::SetVelocity(const Vector& velocity)
{
	m_velocity = velocity;
}

void PhysicsBody::SetPosition(const Point& posit)
{
	m_position = posit;
	if(m_collider != nullptr)
	{
		m_collider->SetCentre(m_position);
	}
}

Point PhysicsBody::GetPosition()
{
	return m_position;
}

void PhysicsBody::GetDimensions(float (&dimensions)[COORDNUM])
{
	if(m_collider != nullptr)
	{
		m_collider->GetDimensions(dimensions);
	}
}

bool PhysicsBody::IsKinematic()
{
	return m_isKinematic;
}

void PhysicsBody::SetKinematic(bool isKinematic)
{
	m_isKinematic = isKinematic;
}
