#include <random>
#include <algorithm>
#include "obstacle.h"

//necessary for compiler linking --> not anymore due to inline keyword
//std::vector<int> Obstacle::obstacle_pos;

void FirstLvlObs::Position() {
    //do something;
}

void FirstLvlObs::Update() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, kGridWidth - 2);

    auto now = std::chrono::system_clock::now();
    //auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    std::chrono::duration<double, std::milli> diff = now - timestamp;
    
    //if starttime has passed...
    if(diff.count() > start_time) {
        // if obstacle hasn't been created (x == -1 )
        if(GetX() == -1)
        {   
            // choose a random x value  
            auto rnd_int = uni(rng);
            if (obstacle_pos.size() > 12) obstacle_pos.clear();
            while(find(obstacle_pos.begin(), obstacle_pos.end(), rnd_int) != obstacle_pos.end() || rnd_int % 2 != 0) 
            {
                rnd_int = uni(rng);
            }
            
            pos_x = rnd_int * kScreenWidth / kGridWidth; // use the whole width to place obstacles 
            obstacle_pos.emplace_back(rnd_int);
            
        } else if(GetY() > kScreenHeight) //32 * 20)
        {
            // set back to start at a potential new location
            pos_x = -1;
            pos_y = -40;
        } else
        {
            // update values  
            pos_y += speed;
        }
    }
}

void NextLvlObs::Update() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> uni(0, kGridHeight -2);

    auto now = std::chrono::system_clock::now();
    //auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    std::chrono::duration<double, std::milli> diff = now - timestamp;

    //if starttime has passed...
    if(diff.count() > start_time) {
        // if obstacle hasn't been created (x == -1 )
        if(GetY() == -1)
        {   
            // choose a random x value  
            auto rnd_int = uni(rng);
            //if (obstacle_pos.size() > 12) obstacle_pos.clear();
            /*while(find(obstacle_pos.begin(), obstacle_pos.end(), rnd_int) != obstacle_pos.end() || rnd_int % 2 != 0) 
            {
                rnd_int = uni(rng);
            }*/
            
            pos_y = rnd_int * kScreenHeight / kGridHeight; // use the whole height to place obstacles 
            //obstacle_pos.emplace_back(rnd_int);
            
        } else if(GetX() > kScreenWidth) //32 * 20)
        {
            // set back to start at a potential new location
            pos_x = -40;
            pos_y = -1;
            timestamp = std::chrono::system_clock::now();
        } else
        {
            // update values  
            pos_x += speed;
        }
    }
}