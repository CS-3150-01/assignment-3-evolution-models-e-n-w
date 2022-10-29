#include <vector>

class Creature;
class Predator;
class Prey;
class Plant;
class World;

struct Vector2{
    int x;
    int y;
    double distance(Vector2 v);
};

class Creature{
    protected:
        World* world;
        int hunger;
        int deathChance;
        Vector2* wanderTarget;
    public:
        int reproductionChance;
        Vector2 position;
        void die();
        Creature(int x, int y);
};

class Predator:public Creature{
    Prey* target;
    Predator* attractor;
    void eat(Prey p);
    void reproduce(Predator p);
    public:
        Predator(int x, int y);
        void update();
};

class Prey:public Creature{
    Plant* target;
    Prey* attractor;
    void eat(Plant p);
    void reproduce(Prey p);
    public:
        Prey(int x, int y);
        void update();
};

class Plant{
    public:
        Vector2 position;
        void die();
        Plant(int x, int y);
};

class World{
    int plantTimer;
    public:
        std::vector<Predator> predators;
        std::vector<Prey> prey;
        std::vector<Plant> plants;
        void createPredator(int x, int y);
        void createPrey(int x, int y);
        void update();
};