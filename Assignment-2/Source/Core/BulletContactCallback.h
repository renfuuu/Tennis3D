#pragma once

#include <btBulletDynamicsCommon.h>
#include "CollisionContext.h"

/*
A struct to handle contactTest queries via the ContactResultCallback
Based on this example code: http://www.bulletphysics.org/mediawiki-1.5.8/index.php?title=Collision_Callbacks_and_Triggers
*/
struct BulletContactCallback : public btCollisionWorld::ContactResultCallback {
	
	//! Constructor, pass whatever context you want to have available when processing contacts
	/*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
	 *  (supplied by the superclass) for needsCollision() */
	BulletContactCallback(btRigidBody& tgtBody , CollisionContext& context);
	
	btRigidBody& body; //!< The body the sensor is monitoring
	CollisionContext& ctxt; //!< External information for contact processing
	
	//! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
	/*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
	 *  then this is unnecessaryócheckCollideWithOverride isn't available */
	virtual bool needsCollision(btBroadphaseProxy* proxy) const;
	
	//! Called with each contact for your own processing
	virtual btScalar addSingleResult(btManifoldPoint& cp,
		const btCollisionObject* colObj0, int partId0, int index0,
		const btCollisionObject* colObj1, int partId1, int index1);

#ifdef __linux__
	// Not sure why this second signature is part of the BulletContactCallback interface. This is onlyn needed for the lab machine's version of Ogre.
	virtual btScalar addSingleResult(btManifoldPoint& cp, const btCollisionObjectWrapper* colObj, int partId1, int index1, const btCollisionObjectWrapper* colbj1Wrap, int partId2, int index2);
#endif
};

