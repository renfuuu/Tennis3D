//How this callback works in the code:
#pragma once

#include "BulletContactCallback.h"
#include "Simulator.h"
#include "CollisionContext.h"
#include "OgreMotionState.h"
#include "OISManager.h"
#include "SoundScoreManager.h"

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>
#include <OgreWindowEventUtilities.h>
#include <OgreRenderTargetListener.h>
#include <OgreParticleSystem.h>

// Simulator & GameObject inclue each other (circular reference).

//Some declarations within the game object class
class GameObject {
public: 
	enum objectType {PADDLE_OBJECT, BALL_OBJECT, FLOOR_OBJECT, WALL_OBJECT, FRONT_WALL_OBJECT, BACK_WALL_OBJECT, NO_TYPE};

protected:
	Ogre::String name;
	Ogre::SceneManager* sceneMgr;
	Ogre::SceneNode* rootNode;
	Ogre::Entity* geom;
	Ogre::Real scale;
	Ogre::Vector3 vscale;
	Ogre::Vector3 startPos;
	OgreMotionState* motionState;

	Simulator* simulator;
	btCollisionShape* shape;
	btRigidBody* body;
	btTransform tr;
	btVector3 inertia;

	SoundScoreManager* soundScoreManager;

	GameObject::objectType type;

	btScalar mass;
	btScalar restitution;
	btScalar friction;
	bool kinematic;
	bool needsUpdates;

	CollisionContext* context;

	Ogre::ParticleSystem* particle;

public:
	BulletContactCallback* cCallBack;

	GameObject(Ogre::String nme, GameObject::objectType tp, Ogre::SceneManager* scnMgr, SoundScoreManager* ssm, Ogre::SceneNode* node, Ogre::Entity* ent, OgreMotionState* ms, Simulator* sim, Ogre::Real mss, Ogre::Real rest, Ogre::Real frict, Ogre::Real scal, bool kin);
	GameObject(Ogre::String nme, GameObject::objectType tp, Ogre::SceneManager* scnMgr, SoundScoreManager* ssm, Ogre::SceneNode* node, Ogre::Entity* ent, OgreMotionState* ms, Simulator* sim, Ogre::Real mss, Ogre::Real rest, Ogre::Real frict, Ogre::Vector3 scal, bool kin);
	inline btRigidBody* getBody() { return body; }
	void addToSimulator();
	virtual void updateTransform();
	void translate(float x, float y, float z);
	void applyForce(float x, float y, float z);
	void setPosition(float x, float y, float z);
	void setPosition(const Ogre::Vector3& pos);
	Ogre::SceneNode* getNode();
	
	void reset();
	void resetScore();
	void startScore();
	void showColliderBox();

	virtual void update() = 0;
	virtual int getPoints();
	virtual GameObject::objectType getType();
	virtual void movePaddle(OISManager* _oisManager, int height, int width);
	virtual Ogre::String getName(void);
	virtual void setPoints(int points);
};
