// Copyright 2013 Google. All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd
#ifndef B2_PARTICLE_GROUP
#define B2_PARTICLE_GROUP

#include <Box2D/Particle/b2Particle.h>

class b2Shape;
class b2World;
class b2ParticleSystem;
class b2ParticleGroup;
struct b2ParticleColor;

/// A particle group definition holds all the data needed to construct a particle group.
/// You can safely re-use these definitions.
struct b2ParticleGroupDef
{

	b2ParticleGroupDef()
	{
		flags = 0;
		position = b2Vec2_zero;
		angle = 0;
		linearVelocity = b2Vec2_zero;
		angularVelocity = 0;
		color = b2ParticleColor_zero;
		strength = 1;
		shape = NULL;
		destroyAutomatically = true;
		userData = NULL;
	}

	/// The logical sum of the particle-behavior flags.
	uint32 flags;

	/// The world position of the group.
	/// Moves the group’s shape a distance equal to the value of position.
	b2Vec2 position;

	/// The world angle of the group in radians.
	/// Rotates the shape by an angle equal to the value of angle.
	float32 angle;

	/// The linear velocity of the group's origin in world co-ordinates.
	b2Vec2 linearVelocity;

	/// The angular velocity of the group.
	float32 angularVelocity;

	/// The color of all particles in the group.
	b2ParticleColor color;

	/// The strength of cohesion among the particles in a group with flag b2_elasticParticle or b2_springParticle.
	float32 strength;

	/// Shape containing the particle group.
	const b2Shape* shape;

	/// If true, destroy the group automatically after its last particle has been destroyed.
	bool destroyAutomatically;

	/// Use this to store application-specific group data.
	void* userData;

};

/// A group of particles. These are created via b2World::CreateParticleGroup.
class b2ParticleGroup
{

public:

	/// Get the next particle group from the list in b2_World.
	b2ParticleGroup* GetNext();
	const b2ParticleGroup* GetNext() const;

	/// Get the number of particles.
	int32 GetParticleCount() const;

	/// Gets an indexed buffer containing the type of each particle in the group. The indices in the buffer match
	/// those of the particles themselves. For instance, the behavior flags for the zeroth-index particle are
	/// stored in the zeroth index of the buffer.
	/// You can change particle types on the fly by writing new values to the buffer.
	uint32* GetParticleFlagsBuffer();

	/// Get the position of each particle in the group.
	b2Vec2* GetParticlePositionBuffer();

	/// Get the velocity of each particle in the group.
	b2Vec2* GetParticleVelocityBuffer();

	/// Get the color of each particle in the group.
	b2ParticleColor* GetParticleColorBuffer();

	/// Get application-specific data for each particle in the group.
	void** GetParticleUserDataBuffer();

	/// Get the type of each particle in the group. The obtained values cannot be changed.
	const uint32* GetParticleFlagsBuffer() const;

	/// Get the position of each particle in the group. The obtained values cannot be changed.
	const b2Vec2* GetParticlePositionBuffer() const;

	/// Get the velocity of each particle in the group. The obtained values cannot be changed.
	const b2Vec2* GetParticleVelocityBuffer() const;

	/// Get the color of each particle in the group. The obtained values cannot be changed.
	const b2ParticleColor* GetParticleColorBuffer() const;

	/// Get application-specific data for each particle in the group. The obtained values cannot be changed.
	void* const* GetParticleUserDataBuffer() const;

	/// Get the iniital particle-behavior flags for the group.
	int32 GetFlags() const;

	/// Get the total mass of the group: the sum of all particles in it.
	float32 GetMass() const;

	/// Get the moment of inertia for the group.
	float32 GetInertia() const;

	/// Get the center of gravity for the group.
	b2Vec2 GetCenter() const;

	/// Get the linear velocity of the group.
	b2Vec2 GetLinearVelocity() const;

	/// Get the angular velocity of the group.
	float32 GetAngularVelocity() const;

	/// Get the position of the group's origin and rotation.
	/// Used only with groups of rigid particles.
	const b2Transform& GetTransform() const;

	/// Get position of the particle group as a whole.
	/// Used only with groups of rigid particles.
	const b2Vec2& GetPosition() const;

	/// Get the rotational angle of the particle group as a whole.
	/// Used only with groups of rigid particles.
	float32 GetAngle() const;

	/// Get the user data pointer that was provided in the group definition.
	void* GetUserData() const;

	/// Set the user data. Use this to store your application specific data.
	void SetUserData(void* data);

private:

	friend class b2ParticleSystem;

	b2ParticleSystem* m_system;
	int32 m_firstIndex, m_lastIndex;
	uint32 m_flags;
	float32 m_strength;
	b2ParticleGroup* m_prev;
	b2ParticleGroup* m_next;

	mutable int32 m_timestamp;
	mutable float32 m_mass;
	mutable float32 m_inertia;
	mutable b2Vec2 m_center;
	mutable b2Vec2 m_linearVelocity;
	mutable float32 m_angularVelocity;
	mutable b2Transform m_transform;

	unsigned m_destroyAutomatically:1;
	unsigned m_toBeDestroyed:1;
	unsigned m_toBeSplit:1;

	void* m_userData;

	b2ParticleGroup();
	~b2ParticleGroup();
	void UpdateStatistics() const;

};

inline b2ParticleGroup* b2ParticleGroup::GetNext()
{
	return m_next;
}

inline const b2ParticleGroup* b2ParticleGroup::GetNext() const
{
	return m_next;
}

inline int32 b2ParticleGroup::GetParticleCount() const
{
	return m_lastIndex - m_firstIndex;
}

#endif
