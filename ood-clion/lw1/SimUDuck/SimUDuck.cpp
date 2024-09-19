#include "Ducks/DecoyDuck.h"
#include "Ducks/MallardDuck.h"
#include "Ducks/ModelDuck.h"
#include "Ducks/RedheadDuck.h"
#include "Ducks/RubberDuck.h"
#include "DuckFunctions.h"
#include <cstdlib>

int main()
{	
	try
	{
		MallardDuck mallardDuck;
		DecoyDuck decoyDuck;
		RedheadDuck redheadDuck;
		RubberDuck rubberDuck;
		ModelDuck modelDuck;

		PlayWithDuck(mallardDuck);
		PlayWithDuck(redheadDuck);
		PlayWithDuck(rubberDuck);
		PlayWithDuck(decoyDuck);
		PlayWithDuck(modelDuck);

//		mallardDuck.Fly();
//		mallardDuck.Fly();
//		std::cout << mallardDuck.GetFlightCount() << std::endl;
//        mallardDuck.SetFlyBehavior(std::make_unique<FlyNoWay>());
//        mallardDuck.Fly();
//        mallardDuck.Fly();

	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	

	return EXIT_SUCCESS;
}