#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>
#include "VisualDebugger.h"

namespace PhysicsEngine
{
	using namespace std;

	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {PxVec3(46.f/255.f,9.f/255.f,39.f/255.f),PxVec3(217.f/255.f,0.f/255.f,0.f/255.f),
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),PxVec3(255.f/255.f,140.f/255.f,54.f/255.f),PxVec3(4.f/255.f,117.f/255.f,111.f/255.f),PxVec3(0.f / 255.f,0.f / 255.f,200.f / 255.f) };

	//pyramid vertices						top			top					
	static PxVec3 pyramid_verts[] = {PxVec3(0.5,4,0.25),PxVec3(-0.5,4,0.25),PxVec3(0.5,4,-0.25),PxVec3(-0.5,4,-0.25), PxVec3(1,0,0.5), PxVec3(-1,0,0.5), PxVec3(-1,0,-0.5), PxVec3(1,0,-0.5)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	static PxVec3 flap_verts[] = { PxVec3(1.25,4,0.25),PxVec3(-1.25,4,0.25),PxVec3(1.25,4,-0.25),PxVec3(-1.25,4,-0.25), PxVec3(1.25,0,0.25), PxVec3(-1.25,0,0.25), PxVec3(-1.25,0,-0.25), PxVec3(1.25,0,-0.25) };

	static PxVec3 Hex_verts[] = { PxVec3(0.5,3,0.25),PxVec3(0.5,3,0.25), PxVec3(1,0,0.5), PxVec3(-1,0,0.5), PxVec3(-1,0,-0.5), PxVec3(1,0,-0.5), PxVec3(0.5,-3,0.25),PxVec3(0.5,-3,0.25), PxVec3(1,0,0.5), PxVec3(-1,0,0.5), PxVec3(-1,0,-0.5), PxVec3(1,0,-0.5) };

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal side = PxReal(0.5f), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class Hex : public ConvexMesh
	{
	public:
		Hex(PxTransform pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f) :
			ConvexMesh(vector<PxVec3>(begin(Hex_verts), end(Hex_verts)), pose, density)
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
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y/2 + dimensions.y/6, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 + dimensions.y / 6, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 + dimensions.y/4, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 + dimensions.y / 4, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 + dimensions.y / 4, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 - dimensions.y /8 , dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 , dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 - dimensions.y / 8, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 - dimensions.y / 5, dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 , dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 , dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 , dimensions.z * 3), density);
			CreateShape(PxBoxGeometry(dimensions.x / 2, dimensions.y / 2 , dimensions.z * 3), density);;
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
		bool killed;
		bool Flipped;

		//MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//string actorNames pairs[i]->get();
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND)
					{
					string triggerName = std::string(pairs[i].triggerActor->getName());
					string otherName = std::string(pairs[i].otherActor->getName());

					if (triggerName == "DeadZone")
						if (otherName == "Ball")
							killed = true;

					if (triggerName == "Flipped")
						if (otherName == "Ball")
							Flipped = true;
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST)
					{
						/*string triggerName = std::string(pairs[i].triggerActor->getName());
						string otherName = std::string(pairs[i].otherActor->getName());

						if (triggerName == "DeadZone")
								killed = false;*/
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
		BoxStatic *Trigger, *Trigger2;
		LID *Flap;
		CompoundObject* Board;
		Sphere* ball;
		Hex* Spinner,* Spinner2,* Spinner3;
		Pyramid* Paddle1, *Paddle2;
		MySimulationEventCallback* my_callback;
		RevoluteJoint* paddleLeft, *paddleRight, *FlapThing, *SpinnerJoint, *SpinnerJoint2,* SpinnerJoint3;
		Trampoline* trampoline, *trampoline2;
		
	public:
		int Score = 0;
		int Lives = 5;
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
			//Plunger wall
			Board->GetShape(6)->setLocalPose(PxTransform(PxVec3(16.0f, 25.0f, 10.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			//bottom walls
			Board->GetShape(7)->setLocalPose(PxTransform(PxVec3(10.0f, 25.0f, 30.0f), PxQuat(-PxHalfPi/2 - PxHalfPi/8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(8)->setLocalPose(PxTransform(PxVec3(-10.0f, 25.0f, 30.0f), PxQuat(PxHalfPi / 2 + PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			//pocket
			Board->GetShape(9)->setLocalPose(PxTransform(PxVec3(-16.0f, 25.0f, 33.0f), PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			//Top Corners
			Board->GetShape(10)->setLocalPose(PxTransform(PxVec3(13.5f, 25.0f, -35.0f), PxQuat(PxHalfPi / 2 + PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(11)->setLocalPose(PxTransform(PxVec3(-13.5f, 25.0f, -35.0f), PxQuat(-PxHalfPi / 2 - PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			//Paddle walls
			Board->GetShape(12)->setLocalPose(PxTransform(PxVec3(9.0f, 25.0f, 25.25f), PxQuat(-PxHalfPi / 2 - PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(14)->setLocalPose(PxTransform(PxVec3(12.0f, 25.0f, 19.25f), PxQuat(PxPi, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(13)->setLocalPose(PxTransform(PxVec3(-10.0f, 25.0f, 24.25f), PxQuat(PxHalfPi / 2 + PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(15)->setLocalPose(PxTransform(PxVec3(-14.0f, 25.0f, 19.25f), PxQuat(PxPi, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			//Middle Triangle
			Board->GetShape(16)->setLocalPose(PxTransform(PxVec3(-15.5f, 25.0f, -3.0f), PxQuat(PxHalfPi / 2 + PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(17)->setLocalPose(PxTransform(PxVec3(-15.5f, 25.0f, 2.25f), PxQuat(-PxHalfPi / 2 - PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));

			Board->GetShape(18)->setLocalPose(PxTransform(PxVec3(11.75f, 25.0f, 2.25f), PxQuat(PxHalfPi / 2 + PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));
			Board->GetShape(19)->setLocalPose(PxTransform(PxVec3(11.75f, 25.0f, -3.0f), PxQuat(-PxHalfPi / 2 - PxHalfPi / 8, PxVec3(0.0f, 1.0f, 0.0f))*PxQuat(PxHalfPi, PxVec3(1.0f, 0.0f, 0.0f))));

			Board->Color(PxVec3(0.0f, 0.0f, 0.0f), 4);
			Board->Material(CreateMaterial(0.0f,0.0f,0.5f));
			Add(Board);

			ball = new Sphere(PxTransform(PxVec3(18.0f, 18.0f, 23.0f)));
			ball->Name("Ball");
			ball->Color(color_palette[1]);
			ball->Material(CreateMaterial(0.78f, 0.27f, 0.39f));
			Add(ball);
			
			Paddle1 = new Pyramid(PxTransform(PxVec3(0.0f, 5.0f, 5.0f)));
			Paddle1->Color(color_palette[0]);
			Paddle1->Name("Paddle1");
			Paddle1->Material(CreateMaterial(0.78f, 0.27f, 0.39f));
			Add(Paddle1);

			Paddle2 = new Pyramid(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Paddle2->Color(color_palette[1]);
			Paddle2->Name("Paddle2");
			Paddle2->Material(CreateMaterial(0.78f, 0.27f, 0.39f));
			Add(Paddle2);

			paddleLeft = new RevoluteJoint(NULL, PxTransform(PxVec3(5.5f,13.5f,35.0f), PxQuat(PxPi / 2, PxVec3(0.f, -1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, 1.f))), Paddle1, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			paddleRight = new RevoluteJoint(NULL, PxTransform(PxVec3(-5.5f,13.5f,35.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))), Paddle2, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			paddleLeft->SetLimits(PxPi / 4, (PxPi / 2 + PxPi / 8));
			paddleRight->SetLimits(PxPi / 4, (PxPi / 2 + PxPi / 8));

			Flap = new LID(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Flap->Color(color_palette[5]);
			Flap->Name("Flap");
			//Parrallel Oak
			Flap->Material(CreateMaterial(0.62f, 0.48f, 0.f));
			Add(Flap);

			FlapThing = new RevoluteJoint(NULL, PxTransform(PxVec3(16.0f, 32.0f, -9.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))), Flap, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			FlapThing->SetLimits((PxPi / 10 - PxPi / 8), (PxPi / 2 + PxPi / 8));
			FlapThing->DriveVelocity(-10);

			Spinner = new Hex(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Spinner->Color(color_palette[5]);
			Spinner->Name("Spinner");
			Add(Spinner);

			Spinner2 = new Hex(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Spinner2->Color(color_palette[5]);
			Spinner2->Name("Spinner2");
			Add(Spinner2);

			Spinner3 = new Hex(PxTransform(PxVec3(0.0f, 5.0f, 10.0f)));
			Spinner3->Color(color_palette[5]);
			Spinner3->Name("Spinner3");
			Add(Spinner3);

			SpinnerJoint = new RevoluteJoint(NULL, PxTransform(PxVec3(0.0f, 34.0f, -15.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))), Spinner, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			SpinnerJoint2 = new RevoluteJoint(NULL, PxTransform(PxVec3(5.0f, 29.5f, -5.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))), Spinner2, PxTransform(PxVec3(0.f, 0.0f, 0.f)));
			SpinnerJoint3 = new RevoluteJoint(NULL, PxTransform(PxVec3(-5.0f, 29.5f, -5.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))), Spinner3, PxTransform(PxVec3(0.f, 0.0f, 0.f)));

			trampoline = new Trampoline(PxTransform(PxVec3(18.0f, 15.0f, 30.0f),PxQuat(PxPi, PxVec3(.0f, .0f, 1.0f))* PxQuat(PxHalfPi + PxHalfPi /4, PxVec3(-1.0f, 0.0f, 0.0f))),PxVec3(1.0f, 4.0f, 1.0f),100.0f , 25.0f);
			trampoline->AddToScene(this);

			trampoline2 = new Trampoline(PxTransform(PxVec3(-18.0f, 12.0f, 39.5f), PxQuat(PxPi, PxVec3(.0f, .0f, 1.0f))* PxQuat(PxHalfPi + PxHalfPi / 4, PxVec3(-1.0f, 0.0f, 0.0f))), PxVec3(1.0f, 4.0f, 1.0f), 100.0f, 25.0f);
			trampoline2->AddToScene(this);
			

			//set collision filter flags
			// box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1);
			//use | operator to combine more actors e.g.
			// box->SetupFiltering(FilterGroup::ACTOR0, FilterGroup::ACTOR1 | FilterGroup::ACTOR2);
			//don't forget to set your flags for the matching actor as well, e.g.
			// box2->SetupFiltering(FilterGroup::ACTOR1, FilterGroup::ACTOR0);
		
			Trigger = new BoxStatic(PxTransform(PxVec3(0.0f, 9.0f, 45.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))),PxVec3(2.0f,2.0f,12.0f));
			Trigger->Name("DeadZone");
			Add(Trigger);
			Trigger->SetTrigger(true);
			Trigger->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);

			Trigger2 = new BoxStatic(PxTransform(PxVec3(18.0f, 34.0f, -17.0f), PxQuat(PxPi / 2, PxVec3(0.f, 1.f, 0.f)) * PxQuat(PxHalfPi - PxHalfPi / 4, PxVec3(0.0f, 0.f, -1.f))), PxVec3(2.0f, 2.0f, 1.0f));
			Add(Trigger2);
			Trigger2->Name("Flipped");
			Trigger2->SetTrigger(true);
			Trigger2->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);

			/*
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
			Score++;
			SpinnerJoint->DriveVelocity(-8);
			SpinnerJoint2->DriveVelocity(-7);
			SpinnerJoint3->DriveVelocity(6);

			if (my_callback->killed == true)
			{
				std::cout<<"Dead"<< endl;
				my_callback->killed = false;
				resetBall();
			}
			if (my_callback->Flipped == true)
			{
				std::cout << "Flipper" << endl;
				FlapThing->DriveVelocity(10);
				my_callback->Flipped = false;
			}
		}

		void resetBall()
		{
			px_scene->removeActor(*((PxActor*)ball->Get()));
			((PxActor*)ball->Get())->release();
			ball = new Sphere(PxTransform(PxVec3(18.0f, 18.0f, 23.0f)));
			Add(ball);
			Lives--;
			if (Lives < 0)
			{
				Lives = 5;
				Score = 0;
			}
			ball->Color(color_palette[1]);
			ball->Material(CreateMaterial(0.78f, 0.27f, 0.39f));
			ball->Name("Ball");
			FlapThing->DriveVelocity(-10);
		}

		void Plunge() {			
			trampoline->Plunge(30.0f);	
		}
		void Plunge_Release() {trampoline->Plunge(0.0f);}

		void Tilt_Release() {trampoline2->Plunge(0.0f);}
		void Tilt() {trampoline2->Plunge(30.0f);}

		void PaddleL_Release(){	paddleLeft->DriveVelocity(10);}
		void PaddleR_Release(){	paddleRight->DriveVelocity(10);}

		void PaddleL(){	paddleLeft->DriveVelocity(-10);}
		void PaddleR(){	paddleRight->DriveVelocity(-10);}
	};
}
