#include "stdafx.h"
#include "TriggersManager.h"


TriggersManager* TriggersManager::trmInstance = nullptr;

TriggersManager::TriggersManager()
{
}


TriggersManager::~TriggersManager()
{
	trigers.clear();

	delete trmInstance;
	
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
	addTrigger( 0 , 169, 20, 138, "AiGoal");
	addTrigger( SCREEN_WIDTH - 20 , 169, 20, 138, "PlGoal" );
}

void TriggersManager::collisionDetected( std::shared_ptr< Object > obj )
{

	for ( auto tr : trigers )
	{

		if( strcmp( tr->getName().c_str() , "AiGoal" ) && tr->isTrigered() == true 
			&& obj->getType() == tPuck )
		{

			SoundManager::getSound("goal.wav")->play();

			Board::aiPoints += 1;

			tr->reset();

			AirHockey::Instance()->GameReset();
		
			break;
		}

		if ( strcmp(tr->getName().c_str(), "PlGoal") && tr->isTrigered() == true 
			&& obj->getType() == tPuck )
		{

			SoundManager::getSound("goal.wav")->play();

			Board::playerPoints += 1;

			tr->reset();

			AirHockey::Instance()->GameReset();

			break;
		}



	}


}
