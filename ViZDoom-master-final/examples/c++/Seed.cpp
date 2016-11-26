#include "ViZDoom.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

void sleep(unsigned int time){
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

using namespace vizdoom;

int main(){

    std::cout << "\n\nSEED EXAMPLE\n\n";


    DoomGame *game = new DoomGame();

    // Choose scenario config file you wish to be watched by agent.
    // Don't load two configs cause the second will overwrite the first one.
    // Multiple config files are ok but combining these ones doesn't make much sense.

    game->loadConfig("../../examples/config/basic.cfg");
    // game->loadConfig("../../examples/config/deadly_corridor.cfg");
    // game->loadConfig("../../examples/config/deathmatch.cfg");
    // game->loadConfig("../../examples/config/defend_the_center.cfg");
    // game->loadConfig("../../examples/config/defend_the_line.cfg");
    // game->loadConfig("../../examples/config/health_gathering.cfg");
    // game->loadConfig("../../examples/config/my_way_home.cfg");
    // game->loadConfig("../../examples/config/predict_position.cfg");
    // game->loadConfig("../../examples/config/take_cover.cfg");

    game->setScreenResolution(RES_640X480);

    // Lets make episode shorter and observe starting position of Cacodemon.
    game->setEpisodeTimeout(50);

    unsigned int seed = 666;
    // Sets the seed. It could be after init as well.
    game->setSeed(seed);

    game->init();

    // Define some actions.
    std::vector<int> actions[3];
    actions[0] = {1, 0, 0};
    actions[1] = {0, 1, 0};
    actions[2] = {0, 0, 1};

    std::srand(time(0));

    int episodes = 10;
    unsigned int sleepTime = 28;

    for (int i = 0; i < episodes; ++i) {

        std::cout << "Episode #" << i + 1 << "\n";

        // Seed can be changed anytime. It will affect next episodes.
        // game->setSeed(seed);
        game->newEpisode();

        while (!game->isEpisodeFinished()) {

            // Get the state
            GameStatePtr state = game->getState();

            // Make random action and get reward
            double reward = game->makeAction(actions[std::rand() % 3]);

            std::cout << "State #" << state->number << "\n";
            std::cout << "Action reward: " << reward << "\n";
            std::cout << "Seed: " << game->getSeed() << "\n";
            std::cout << "=====================\n";

            if(sleepTime) sleep(sleepTime);

        }

        std::cout << "Episode finished.\n";
        std::cout << "Total reward: " << game->getTotalReward() << "\n";
        std::cout << "************************\n";

    }

    // It will be done automatically in destructor but after close You can init it again with different settings.
    game->close();
    delete game;
}

