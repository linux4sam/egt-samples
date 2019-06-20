#ifndef HOOMAN_H
#define HOOMAN_H

#include <Box2D/Box2D.h>
#include <cairo.h>

// inspired by https://github.com/trbljump/CairOLed

#include <iostream>
#include <vector>
#include <map>

class Hooman
{
public:
    Hooman(b2World& world);

    ~Hooman();

    bool isAlive() const
    {
        return (head->GetPosition()(1) > lower_torso->GetPosition()(1));
    }

    size_t variableCount() const
    {
        return joints.size();
    }

    void setVariable(size_t i, double d) {
        joints[i]->SetMotorSpeed(d);
    }

    double getX() const
    {
        b2Vec2 pos(0,0);
        size_t i;

        for (i=0; i < bodies.size(); i++)
        {
            pos += bodies[i]->GetPosition();
        }

        return pos(0)/i;
    }

    void render_to_cairo(cairo_t* cr, bool blackout = false);

    protected:
    b2World& world;

    b2Body* createBoxElement(const b2Vec2& size,
                             const b2Vec2& position);

    b2Joint* createRevoluteJoint(b2Body* bodyA,
                                 b2Body* bodyB,
                                 const b2Vec2& deltaPosition,
                                 double minAngle = 0,
                                 double maxAngle = 6.28318530718,
                                 bool enableMotor=false,
                                 double maxMotorTorque=0);

    b2Joint* createWeldJoint(b2Body* bodyA,
                             b2Body* bodyB,
                             const b2Vec2& anchorA,
                             const b2Vec2& anchorB,
                             double referenceAngle=0);


    private:
    // Ragdoll model from http://rednuht.org/genetic_walkers/

    static constexpr double TORSO_UPPER_WIDTH = 0.25;
    static constexpr double TORSO_UPPER_HEIGHT = 0.45;
    static constexpr double TORSO_LOWER_WIDTH = 0.25;
    static constexpr double TORSO_LOWER_HEIGHT = 0.2;

    static constexpr double FEMUR_WIDTH = 0.18;
    static constexpr double FEMUR_LENGTH = 0.45;
    static constexpr double TIBIA_WIDTH = 0.13;
    static constexpr double TIBIA_LENGTH = 0.38;
    static constexpr double FOOT_HEIGHT = 0.08;
    static constexpr double FOOT_LENGTH = 0.28;

    static constexpr double ARM_WIDTH = 0.12;
    static constexpr double ARM_LENGTH = 0.37;
    static constexpr double FOREARM_WIDTH = 0.1;
    static constexpr double FOREARM_LENGTH = 0.42;

    static constexpr double HEAD_WIDTH = 0.22;
    static constexpr double HEAD_HEIGHT = 0.22;
    static constexpr double NECK_WIDTH = 0.1;
    static constexpr double NECK_HEIGHT = 0.08;

    b2Body* head;
    b2Body* neck;
    b2Body* upper_torso;
    b2Body* lower_torso;
    b2Body* left_arm_upper;
    b2Body* left_arm_lower;
    b2Body* right_arm_upper;
    b2Body* right_arm_lower;
    b2Body* left_leg_upper;
    b2Body* left_leg_lower;
    b2Body* left_leg_foot;
    b2Body* right_leg_upper;
    b2Body* right_leg_lower;
    b2Body* right_leg_foot;

    std::map<const b2Body*, b2Vec2> sizes;
    std::vector<b2RevoluteJoint*> joints;
    std::vector<b2Body*> bodies;

    double rr, gg, bb;
};

#endif
