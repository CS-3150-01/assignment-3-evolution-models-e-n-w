#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "classes.hpp"

double Vector2::distance(Vector2 v){
    return sqrt((v.x - x)*(v.x - x) + (v.y - y)*(v.y - y));
}


void Creature::die(){
    delete this;
}
Creature::Creature(int x, int y){
    position.x = x;
    position.y = y;
    hunger = 100;
    reproductionChance = 40;
    deathChance = 0;
}

void Predator::eat(Prey p){
    hunger += 30;
    reproductionChance += 30;
    p.die();
}
void Predator::reproduce(Predator p){
    reproductionChance = 0;
    p.reproductionChance = 0;
    world->createPredator(position.x, position.y);
}
Predator::Predator(int x, int y):Creature(x, y){}
void Predator::update(){
    hunger--;
    if(hunger <= 50){
        deathChance += 2;
        reproductionChance -= 2;
        if(hunger == 0){
            die();
        }
    }else if(hunger >= 50){
        deathChance -= 2;
        if(deathChance < 0){
            deathChance = 0;
        }
    }
    if(deathChance >= rand() % 100 + 1){
        die();
    }

    if(target == nullptr){
        for(Prey p : world->prey){
            if(position.distance(p.position) <= 5){
                target = &p;
            }
        }
        if(attractor == nullptr && target == nullptr){
            for(Predator p : world->predators){
                if(position.distance(p.position) <= 5){
                    attractor = &p;
                }
            }
            if(wanderTarget = nullptr){
                wanderTarget = new Vector2;
                wanderTarget->x = rand() % 51 - 25;
                wanderTarget->y = rand() % 51 - 25;
            }else{
                if(position.x == wanderTarget->x && position.y == wanderTarget->y){
                    delete wanderTarget;
                }else{
                int tx = wanderTarget->x;
                int ty = wanderTarget->y;
                position.x += std::signbit(tx) ? -1 : 1;
                position.y += std::signbit(ty) ? -1 : 1;
                }
            }
        }else if(attractor != nullptr && target == nullptr){
            if(reproductionChance < 50 || attractor->reproductionChance < 50){
                attractor = nullptr;
            }
            if(position.distance(attractor->position) <= 1.5){
                reproduce(*attractor);
                attractor = nullptr;
            }else{
                int tx = attractor->position.x;
                int ty = attractor->position.y;
                position.x += std::signbit(tx) ? -1 : 1;
                position.y += std::signbit(ty) ? -1 : 1;
            }
        }
    }else{
        if(position.distance(target->position) <= 1.5){
            eat(*target);
            target = nullptr;
        }else{
            int tx = target->position.x;
            int ty = target->position.y;
            position.x += std::signbit(tx) ? -1 : 1;
            position.y += std::signbit(ty) ? -1 : 1;
        }
    }
}


void Prey::eat(Plant p){
    hunger += 40;
    p.die();
}
void Prey::reproduce(Prey p){
    reproductionChance = 0;
    p.reproductionChance = 0;
    world->createPrey(position.x, position.y);
    world->createPrey(position.x, position.y);
}
Prey::Prey(int x, int y):Creature(x, y){};
void Prey::update(){
    hunger--;
    if(hunger <= 50){
        deathChance += 2;
        reproductionChance -= 2;
        if(hunger == 0){
            die();
        }
    }else if(hunger >= 50){
        deathChance -= 2;
        if(deathChance < 0){
            deathChance = 0;
        }
    }
    if(deathChance >= rand() % 100 + 1){
        die();
    }

    if(target == nullptr){
        for(Plant p : world->plants){
            if(position.distance(p.position) <= 5){
                target = &p;
            }
        }
        if(attractor == nullptr && target == nullptr){
            for(Prey p : world->prey){
                if(position.distance(p.position) <= 5){
                    attractor = &p;
                }
            }
            if(wanderTarget = nullptr){
                wanderTarget = new Vector2;
                wanderTarget->x = rand() % 51 - 25;
                wanderTarget->y = rand() % 51 - 25;
            }else{
                if(position.x == wanderTarget->x && position.y == wanderTarget->y){
                    delete wanderTarget;
                }else{
                int tx = wanderTarget->x;
                int ty = wanderTarget->y;
                position.x += std::signbit(tx) ? -1 : 1;
                position.y += std::signbit(ty) ? -1 : 1;
                }
            }
        }else if(attractor != nullptr && target == nullptr){
            if(reproductionChance < 50 || attractor->reproductionChance < 50){
                attractor = nullptr;
            }
            if(position.distance(attractor->position) <= 1.5){
                reproduce(*attractor);
                attractor = nullptr;
            }else{
                int tx = attractor->position.x;
                int ty = attractor->position.y;
                position.x += std::signbit(tx) ? -1 : 1;
                position.y += std::signbit(ty) ? -1 : 1;
            }
        }
    }else{
        if(position.distance(target->position) <= 1.5){
            eat(*target);
            target = nullptr;
        }else{
            int tx = target->position.x;
            int ty = target->position.y;
            position.x += std::signbit(tx) ? -1 : 1;
            position.y += std::signbit(ty) ? -1 : 1;
        }
    }
}

Plant::Plant(int x, int y){
    position.x = x;
    position.y = y;
}
void Plant::die(){
    delete this;
}

void World::createPredator(int x, int y){
    predators.push_back(Predator(x, y));
}
void World::createPrey(int x, int y){
    prey.push_back(Prey(x, y));
}
void World::update(){
    for(Predator p:predators){
        p.update();
    }
    for(Prey p:prey){
        p.update();
    }
    plantTimer--;
    if(plantTimer == 0){
        int x = rand() % 51 - 25;
        int y = rand() % 51 - 25;
        plants.push_back(Plant(x, y));
    }
}

int main(){
    srand(time(0));

    World world;

    for(int i = 0; i++; i<30){
        int x = rand() % 51 - 25;
        int y = rand() % 51 - 25;
        world.predators.push_back(Predator(x, y));
    }
    for(int i = 0; i++; i<30){
        int x = rand() % 51 - 25;
        int y = rand() % 51 - 25;
        world.prey.push_back(Prey(x, y));
    }
    for(int i = 0; i++; i<40){
        int x = rand() % 51 - 25;
        int y = rand() % 51 - 25;
        world.plants.push_back(Plant(x, y));
    }

    while(true){
        world.update();
        if(world.predators.size() == 0){
            std::cout << "No more predators";
            break;
        }else if(world.prey.size() == 0){
            std::cout << "No more prey";
            break;
        }
    }
}