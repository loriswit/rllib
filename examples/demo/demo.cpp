#include <rllib/game/Game.hpp>
#include <iostream>

int main(int argc, char ** argv)
{
    // load the game files
    rl::Game game("path/to/Rayman Legends.exe");
    
    // load a scene from the bundle
    auto path = "world/challenge/shaolinplaza/brick/easy/shaolin_brick_easy_001.isc";
    auto scene = game.getScene(path);
    
    // transform some entities
    scene["polebamboo_fat2"].scale = {0.5, 2};
    scene["dojotarget"].position = {12, -8, 4};
    scene["dojotarget@1"].rotation = 90_deg;
    
    // print position & rotation of each entity in the scene
    for(auto & entity : scene)
    {
        std::cout << entity.name << ":\n";
        std::cout << "\tposition: " << entity.position << "\n";
        std::cout << "\tscale: " << entity.scale << "\n";
        std::cout << "\trotation: " << entity.rotation << "\n";
        std::cout << std::endl;
    }
    
    // test the scene
    game.run(scene);
    
    // save the scene in a file
    scene.save("my_scene.isc");
}
