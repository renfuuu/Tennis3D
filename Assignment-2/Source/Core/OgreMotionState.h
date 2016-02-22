#pragma once

#include <btBulletDynamicsCommon.h>
#include <OgreSceneManager.h>

class OgreMotionState : public btMotionState {
protected:
	Ogre::SceneNode* mVisibleobj;
	btTransform mPos1;
public:
	OgreMotionState(const btTransform &initialpos, Ogre::SceneNode* node);

	virtual ~OgreMotionState();

 	//Provides flexibility in terms of object visibility
	void setNode(Ogre::SceneNode* node);

	virtual void getWorldTransform(btTransform &worldTrans) const;

	virtual void setWorldTransform(const btTransform &worldTrans);	
};