#ifndef ARMAMENT_H
#define ARMAMENT_H

#include <string>
#include "Subsystem.hpp"
#include "Vessel.hpp"

class Vessel;

class Armament : Subsystem
{
    private:
        // The vessel the armament belongs to
        Vessel* _parent;
        // Human readable weapon type (missile, laser beam, fish)
        std::string _type;
        // What model, decorative name (Tomahawk, EE5000, Trout)
        std::string _model;
        // Base damage done by weapon
        double _impact;
        // Ratio of damage dealt to shields
        double _shieldEffect;
        // Ratio of damage dealt to hulls
        double _hullEffect;
        // Maximum firing range
        double _range;
        // Time it takes for weapon to fire again
        int _maxCooldown;
        // Amount of ammunition used when firing once
        int _cooldown;
        // Amount of ammunition left
        int _burstRate; 
        // The current cooldown timer
        int _ammoCount;
        // The current weapon target
        Vessel* _target;
    public:
        Armament(Vessel* parent, std::string type, std::string model,
                double impact, double shieldEffect, double hullEffect,
                double range, int maxCooldown, int burstRate, int ammoCount,
                int x, int y, int w, int h, int weight, int maxIntegrity,
                int energyDrain);

        void SetParent(Vessel* parent);
        void SetTarget(Vessel* target);

        Vessel* GetParent() { return _parent; }
        const std::string GetModel() const { return _model; }
        const double GetImpact() const { return _impact; }
        const double GetShieldEffect() const { return _shieldEffect; }
        const double GetShieldImpact() const { return _impact * _shieldEffect; }
        const double GetHullEffect() const { return _hullEffect; }
        const double GetHullImpact() const { return _impact * _hullEffect; }

        void HandleEvents() {}
        void Update();
        void Draw();
};

#endif
