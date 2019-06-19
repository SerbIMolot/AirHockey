#include "stdafx.h"
#include "TriggersManager.h"


//std::vector< std::shared_ptr< Trigger > > TriggersManager::trigers = std::vector< std::shared_ptr< Trigger > >();
TriggersManager* TriggersManager::trmInstance = nullptr;

TriggersManager::TriggersManager()
{
}


TriggersManager::~TriggersManager()
{
	delete trmInstance;
	trigers.clear();
}

TriggersManager* TriggersManager::Instance()
{
	if( trmInstance == nullptr )
	{
		trmInstance = new TriggersManager();

		trmInstance->Init();
	}
	return trmInstance;
}

void TriggersManager::addTrigger(int x, int y, int w, int h, std::string name)
{
	//Trigger::id += 1;

	std::shared_ptr< Trigger > tr = std::make_shared< Trigger >( x, y, w, h );

	tr->setName( name );

	trigers.push_back( tr );



}

void TriggersManager::addTrigger(std::shared_ptr<Vector2d> vec, int w, int h, std::string name)
{
	std::shared_ptr< Trigger > tr = std::make_shared< Trigger >( vec, w, h );

	tr->setName( name );

	trigers.push_back( tr );
}

void TriggersManager::Init()
{
	addTrigger( 0 , 180, 30, 277 , "AiGoal");
	addTrigger( SCREEN_WIDTH - 30 , 180, 30, 277, "PlGoal" );
}

void TriggersManager::collisionDetected( std::shared_ptr< Object > obj )
{

	for ( auto tr : trigers )
	{

		if( strcmp( tr->getName().c_str() , "AiGoal" ) && tr->isTrigered() == true 
			&& obj->getType() == tPuck )
		{
			Board::aiPoints += 1;
			
			for (int i = 0 ; i < 10; i++)
			{
				std::cout << "AI GOAL score = " << i << std::endl;
			}

			AirHockey::Instance()->GameReset();
		}

		if ( strcmp(tr->getName().c_str(), "PlGoal") && tr->isTrigered() == true 
			&& obj->getType() == tPuck )
		{
			Board::playerPoints += 1;
			for (int i = 0; i < 10; i++)
			{
				std::cout << "AI GOAL score = " << i << std::endl;
			}
			AirHockey::Instance()->GameReset();
		}



	}


}
