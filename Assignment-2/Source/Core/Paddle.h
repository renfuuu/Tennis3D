#pragma once

#include "GameObject.h"

class Paddle : public GameObject {
public:
	Paddle(Ogre::String nme, Ogre::SceneManager* scnMgr, Ogre::SceneNode* node, Ogre::Entity* ent, OgreMotionState* ms, Simulator* sim, Ogre::Real mss, Ogre::Real rest, Ogre::Real frict, Ogre::Real scal);
	~Paddle();
	virtual void update();
};