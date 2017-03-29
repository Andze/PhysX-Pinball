#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f),PxVec3(0.f / 255.f,0.f / 255.f,200.f / 255.f) };

	//pyramid vertices						top			top					
	static PxVec3 pyramid_verts[] = {PxVec3(0.5,5,0.25),PxVec3(-0.5,5,0.25),PxVec3(0.5,5,0.-0.25),PxVec3(-0.5,5,0.-0.25), PxVec3(1,0,1), PxVec3(-1,0,1), PxVec3(-1,0,-1), PxVec3(1,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	static PxVec3 flap_verts[] = { PxVec3(1.0,4,0.25),PxVec3(-1.0,4,0.25),PxVec3(1.0,4,-0.25),PxVec3(-1.0,4,-0.25), PxVec3(1.0,0,0.25), PxVec3(-1.0,0,0.25), PxVec3(-1.0,0,-0.25), PxVec3(1.0,0,-0.25) };

	/*static PxVec3 LID_verts[] = { PxVec3(0.0,0.25,0.5),PxVec3(0.0,0.25,0.5), PxVec3(0.0,0.25,-0.5), PxVec3(0.0,0.25,-0.5), PxVec3(-0.5,0.25,0.5), PxVec3(-0.5,0.25,0.5),PxVec3(-0.5,0.25,-0.5),PxVec3(-0.5,0.25,-0.5), };
	*/
	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class LID : public ConvexMesh
	{
	public:
		LID(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 0.1f) :
			ConvexMesh(vector<PxVec3>(begin(flap_verts), end(flap_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	class CompoundObject : public StaticActor
	{
	public:
		CompoundObject(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(10.0f, 0.1f, 1.0f), PxReal density = 1.f) : StaticActor(pose)
		{
			//				X,Y,Z,D
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y * 4, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y * 4, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x * 3, dimensions.y*2, dimensions.z/2), density);
			CreateShape(PxBoxGeometry(dimensions.x * 3 , dimensions.y*2, dimensions.z/2), density);
			CreateShape(PxBoxGeometry(dimensions.x * (dimensions.y * 2), dimensions.y * 4, dimensions.z/4), density);
			CreateShape(PxBoxGeometry(dimensions.x * (dimensions.y * 2), dimensions.y * 4, dimensions.z/4), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y * 3, dimensions.z * 3), density);

		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			ACTOR0		= (1 << 0),
			ACTOR1		= (1 << 1),
			ACTOR2		= (1 << 2)
			//add more if you need
		};
	};

	///An example class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box *top;
		BoxStatic *bottom;

	public:
		Trampoline(const PxTransform& pose = PxTransform(PxIdentity),const PxVec3& dimensions=PxVec3(1.f,1.f,1.f), PxReal stiffness=1.f, PxReal damping=1.f)
		{
			PxReal thickness = .1f;
			bottom = new BoxStatic(PxTransform(pose.p + PxVec3(.0f,.0f,.0f), pose.q),PxVec3(dimensions.x,thickness,dimensions.z));
			top = new Box(PxTransform(pose.p + PxVec3(.0f, .0f, .0f), pose.q), PxVec3(dimensions.x, thickness, dimensions.z));

			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		} 

		void Plunge(PxReal force)
		{
			top->Get()->isRigidDynamic()->addForce(PxVec3(0.f, (force * 100)/2, -force * 100.f));
		}
		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool trigger;

		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						trigger = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;
					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				//check eNOTIFY_TOUCH_FOUND
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
//		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
//			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box, * box2;
		LID *Flap;
		CompoundObject* Board;
		Sphere* ball;
		Pyramid* Paddle1, *Paddle2;
		MySimulationEventCallback* my_callback;
		RevoluteJoint* paddleLeft, *paddleRight, *FlapThing;
		Trampoline* trampoline;
		
	public:
		//specify your custom filter shader here
		//PxDefaultSimulationFilterShader by default
		MyScene() : Scene() {};

		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eBODY_LIN_VELOCITY, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LOCAL_FRAMES, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eJOINT_LIMITS, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			GetMaterial()->setDynamicFriction(.2f);

			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));
			Add(plane);

			Board = new CompoundObject(PxTransform(PxVec3(0.0f, 0.5f, 0.0f), PxQuat(PxHalfPi / 4, PxVec3(1.0f, 0.f, 0.f))),PxVec3(1.0f,10.0f,1.0f));
			Board->Color(color_palette[5]);
			Board->Name("GameBoard");
			Board->GetShape(0)->setLocalPose(PxTransform(PxVec3(20.0f, 25.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(1)->setLocalPose(PxTransform(PxVec3(-20.0f, 25.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(2)->setLocalPose(PxTransform(PxVec3(0.0f, 25.0f, 40.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f))));
			Board->GetShape(3)->setLocalPose(PxTransform(PxVec3(0.0f, 25.0f, -40.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f))));
			Board->GetShape(4)->setLocalPose(PxTransform(PxVec3(0.0f, 23.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(5)->setLocalPose(PxTransform(PxVec3(0.0f, 27.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(5)->setFlag(PxShapeFlag::eVISUALIZATION, false);
			Board->GetShape(6)->setLocalPose(PxTransform(PxVec3(16.0f, 25.0f, 10.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->Color(PxVec3(0.0f, 0.0f, 0.0f), 5);
			Add(Board);

			ball = new Sphere(PxTransform(PxVec3(18.0f, 18.0f, 23.0f)));
			ball->Color(color_palette[1]);
			ball->Name("Ball");
			Add(ball);
			
			Paddle1 = new Pyramid(PxTransform(PxVec3(0.0f, 5.0f, 5.0f)));
			Paddle1->Color(color_palette[0]);
			Paddle1->Name("Paddle1");
			Add(Paddle1);

			Paddle2 = new Pyramid(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Paddle2->Color(color_palette[1]);
			Paddle2->Name("Paddle2");
			Add(Paddle2);

			paddleLeft = new RevoluteJoint(NULL, PxTransform(PxVec3(7.5f,15.0f,30.0f), PxQuat(PxPi / 2, PxVec3(0.f, -1.f, 0.f)) * PxQuat(PxHalfPi /2, PxVec3(0.0f, 0.f, 1.f))), Paddle1, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			paddleRight = new RevoluteJoint(NULL, PxTransform(PxVec3(-7.5f,15.0f,30.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi /2, PxVec3(0.0f, 0.f, -1.f))), Paddle2, PxTransform(PxVec3(0.f, 0.0f, 0.f)));

			Flap = new LID(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Flap->Color(color_palette[5]);
			Flap->Name("Flap");
			Add(Flap);

			//FlapThing = new RevoluteJoint(NULL, PxTransform(PxVec3(15.0f, 32.0f, 30.0f), PxQuat(PxPi / 2, PxVec3(0.f, -1.f, 0.f)) * PxQuat(PxHalfPi / 2, PxVec3(0.0f, 0.f, 1.f))), Paddle1, PxTransform(PxVec3(0.f, 0.0f, 0.f)));

			FlapThing = new RevoluteJoint(NULL, PxTransform(PxVec3(15.0f, 32.0f, -10.0f), PxQuat(PxPi / 2, PxVec3(0.f, -1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, 1.f))), Flap, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			FlapThing->DriveVelocity(0);
			FlapThing->SetLimits(PxPi / 4, (PxPi / 2 + PxPi / 8));

			trampoline = new Trampoline(PxTransform(PxVec3(18.0f, 15.0f, 30.0f),PxQuat(PxPi, PxVec3(.0f, .0f, 1.0f))* PxQuat(PxHalfPi + PxHalfPi /4, PxVec3(-1.0f, 0.0f, 0.0f))),PxVec3(1.0f, 4.0f, 1.0f),100.0f , 25.0f);
			trampoline->AddToScene(this);
			

			//set collision filter flags
			// box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);
			//use | operator to combine more actors e.g.
			// box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1 | FilterGroup::ACTOR2);
			//don't forget to set your flags for the matching actor as well, e.g.
			// box2->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
		
			/*box = new Box(PxTransform(PxVec3(.0f, .5f, .0f)));
			box->Color(color_palette[0]);
			box->Name("Box1");
			Add(box);

			box2 = new Box(PxTransform(PxVec3(.0f, 12.5f, .0f)));
			box2->Color(color_palette[1]);
			box2->Name("Box2");
			Add(box2);*/
			
			//joint two boxes together
			//the joint is fixed to the centre of the first box, oriented by 90 degrees around the Y axis
			//and has the second object attached 5 meters away along the Y axis from the first object.
			//RevoluteJoint joint(box, PxTransform(PxVec3(0.f,0.f,0.f), PxQuat(PxPi/2,PxVec3(0.f,1.f,0.f))), box2, PxTransform(PxVec3(0.f,5.f,0.f)));
			
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
		}

		void Plunge() {			
			trampoline->Plunge(25.0f);
		}
		void Plunge_Release() { 
			trampoline->Plunge(0.0f);
		}

		/// An example use of key release handling
		void PaddleL_Release(){	paddleLeft->DriveVelocity(10); FlapThing->DriveVelocity(10);}
		void PaddleR_Release(){	paddleRight->DriveVelocity(10);}

		/// An example use of key presse handling
		void PaddleL(){	paddleLeft->DriveVelocity(-10); FlapThing->DriveVelocity(-10);}
		void PaddleR(){	paddleRight->DriveVelocity(-10);}
	};
}
