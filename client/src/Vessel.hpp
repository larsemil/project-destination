#ifndef VESSEL_H
#define VESSEL_H

#include <vector>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL/SDL.h>
#include "Entity.hpp"
#include "Subsystem.hpp"

/* Client representation of a starship */

class Vessel : public Entity
{
  private:
    int _id;
    // Open GL texture ID
    GLuint _textureId;

    std::string _name;

    std::vector<Subsystem*> _subsystems;

    double _steering;
    double _throttle;

  public:
    Vessel() { }
    Vessel(int id, std::string name, std::vector<Subsystem*>& _subsystems,
        float x, float y, float rot);
    ~Vessel();

    const std::string GetName() const { return _name; }
    const bool IsAlive() const { return _isAlive; }

    //void TakeDamage(const Armament* const armament);
    void Destroy();

    void ReceiveWorld();
    void Update();
    void Draw();
};

#endif
