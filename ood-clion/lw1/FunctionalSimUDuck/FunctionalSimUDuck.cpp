#include "Ducks/DecoyDuck.h"
#include "Ducks/MallardDuck.h"
#include "Ducks/ModelDuck.h"
#include "Ducks/RedheadDuck.h"
#include "Ducks/RubberDuck.h"
#include <cstdlib>

void PlayWithDuck(Duck &duck)
{
    std::cout << "---------------" << std::endl;
    duck.Display();
    duck.Swim();
    duck.Quack();
    duck.Fly();
    duck.Dance();
    std::cout << "---------------" << std::endl << std::endl;
}

int main()
{
    try
    {
        MallardDuck mallardDuck;
        DecoyDuck decoyDuck;
//		RedheadDuck redheadDuck;
//		RubberDuck rubberDuck;
//		ModelDuck modelDuck;
//
//		PlayWithDuck(mallardDuck);
//		PlayWithDuck(redheadDuck);
//		PlayWithDuck(rubberDuck);
//		PlayWithDuck(decoyDuck);
//		PlayWithDuck(modelDuck);

        mallardDuck.Fly();
        mallardDuck.Fly();
        mallardDuck.SetFlyBehavior(FlyNoWay());
        mallardDuck.Fly();
        mallardDuck.Fly();
        mallardDuck.SetFlyBehavior(FlyWithWings());
        mallardDuck.Fly();
        mallardDuck.Fly();

        decoyDuck.Fly();
        decoyDuck.Fly();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}