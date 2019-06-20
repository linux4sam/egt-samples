#include "hooman.h"
#include <iostream>

using namespace std;

#define DEGTORAD (3.14159/180.0)

Hooman::Hooman(b2World& world) : world(world)
{
    rr = 0.5 + 0.5 * drand48();
    gg = 0.5 + 0.5 * drand48();
    bb = 0.5 + 0.5 * drand48();

    head = createBoxElement(b2Vec2(HEAD_WIDTH, HEAD_HEIGHT),
                            b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                   FOOT_HEIGHT + TIBIA_LENGTH
                                   + FEMUR_LENGTH + TORSO_LOWER_HEIGHT
                                   + TORSO_UPPER_HEIGHT + NECK_HEIGHT
                                   + HEAD_HEIGHT / 2));

    neck = createBoxElement(b2Vec2(NECK_WIDTH, NECK_HEIGHT),
                            b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                   FOOT_HEIGHT + TIBIA_LENGTH
                                   + FEMUR_LENGTH + TORSO_LOWER_HEIGHT
                                   + TORSO_UPPER_HEIGHT + NECK_HEIGHT / 2));

    upper_torso = createBoxElement(b2Vec2(TORSO_UPPER_WIDTH, TORSO_UPPER_HEIGHT),
                                   b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                          FOOT_HEIGHT + TIBIA_LENGTH
                                          + FEMUR_LENGTH + TORSO_LOWER_HEIGHT
                                          + TORSO_UPPER_HEIGHT / 2));

    lower_torso = createBoxElement(b2Vec2(TORSO_LOWER_WIDTH, TORSO_LOWER_HEIGHT),
                                   b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                          FOOT_HEIGHT + TIBIA_LENGTH
                                          + FEMUR_LENGTH
                                          + TORSO_LOWER_HEIGHT / 2));

    left_arm_upper = createBoxElement(b2Vec2(ARM_WIDTH, ARM_LENGTH),
                                      b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                              FOOT_HEIGHT + TIBIA_LENGTH
                                              + FEMUR_LENGTH
                                              + TORSO_LOWER_HEIGHT
                                              + TORSO_UPPER_HEIGHT
                                              - ARM_LENGTH / 2));

    left_arm_lower = createBoxElement(b2Vec2(FOREARM_WIDTH, FOREARM_LENGTH),
                                      b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                              FOOT_HEIGHT + TIBIA_LENGTH
                                              + FEMUR_LENGTH
                                              + TORSO_LOWER_HEIGHT
                                              + TORSO_UPPER_HEIGHT
                                              - ARM_LENGTH
                                              - FOREARM_LENGTH / 2));

    right_arm_upper = createBoxElement(b2Vec2(ARM_WIDTH, ARM_LENGTH),
                                       b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                               FOOT_HEIGHT + TIBIA_LENGTH
                                               + FEMUR_LENGTH
                                               + TORSO_LOWER_HEIGHT
                                               + TORSO_UPPER_HEIGHT
                                               - ARM_LENGTH / 2));

    right_arm_lower = createBoxElement(b2Vec2(FOREARM_WIDTH, FOREARM_LENGTH),
                                       b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                               FOOT_HEIGHT + TIBIA_LENGTH
                                               + FEMUR_LENGTH
                                               + TORSO_LOWER_HEIGHT
                                               + TORSO_UPPER_HEIGHT
                                               - ARM_LENGTH
                                               - FOREARM_LENGTH / 2));


    left_leg_upper = createBoxElement(b2Vec2(FEMUR_WIDTH, FEMUR_LENGTH),
                                      b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                              FOOT_HEIGHT + TIBIA_LENGTH
                                              + FEMUR_LENGTH / 2));
    left_leg_lower = createBoxElement(b2Vec2(TIBIA_WIDTH, TIBIA_LENGTH),
                                      b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                              FOOT_HEIGHT + TIBIA_LENGTH / 2));
    left_leg_foot = createBoxElement(b2Vec2(FOOT_LENGTH, FOOT_HEIGHT),
                                     b2Vec2(0.5,
                                            FOOT_HEIGHT / 2));

    right_leg_upper = createBoxElement(b2Vec2(FEMUR_WIDTH, FEMUR_LENGTH),
                                       b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                               FOOT_HEIGHT + TIBIA_LENGTH
                                               + FEMUR_LENGTH / 2));
    right_leg_lower = createBoxElement(b2Vec2(TIBIA_WIDTH, TIBIA_LENGTH),
                                       b2Vec2(0.5 - FOOT_LENGTH / 2 + TIBIA_WIDTH / 2,
                                               FOOT_HEIGHT + TIBIA_LENGTH / 2));
    right_leg_foot = createBoxElement(b2Vec2(FOOT_LENGTH, FOOT_HEIGHT),
                                      b2Vec2(0.5,
                                              FOOT_HEIGHT / 2));

    createRevoluteJoint(neck, head, b2Vec2(0, NECK_HEIGHT),
                        -6 * DEGTORAD, 6 * DEGTORAD, true, 20);

    createWeldJoint(neck, upper_torso, b2Vec2(0, -NECK_HEIGHT / 2),
                    b2Vec2(0, TORSO_UPPER_HEIGHT / 2));

    createRevoluteJoint(upper_torso, lower_torso, b2Vec2(-TORSO_LOWER_WIDTH / 3,
                        -TORSO_UPPER_HEIGHT / 2),
                        -10 * DEGTORAD, 18 * DEGTORAD, true, 250);

    createRevoluteJoint(upper_torso, right_arm_upper, b2Vec2(0,
                        TORSO_UPPER_HEIGHT / 2),
                        -36 * DEGTORAD, 45 * DEGTORAD, true, 120);
    createRevoluteJoint(right_arm_upper, right_arm_lower,
                        b2Vec2(0, -ARM_LENGTH / 2), 0, 50 * DEGTORAD, true, 60);

    createRevoluteJoint(upper_torso, left_arm_upper, b2Vec2(0,
                        TORSO_UPPER_HEIGHT / 2),
                        -36 * DEGTORAD, 45 * DEGTORAD, true, 120);
    createRevoluteJoint(left_arm_upper, left_arm_lower,
                        b2Vec2(0, -ARM_LENGTH / 2), 0, 50 * DEGTORAD, true, 60);

    createRevoluteJoint(lower_torso, right_leg_upper,
                        b2Vec2(0, -TORSO_LOWER_HEIGHT),
                        -25 * DEGTORAD, 30 * DEGTORAD, true, 250);
    createRevoluteJoint(right_leg_upper, right_leg_lower,
                        b2Vec2(-FEMUR_WIDTH / 4, -FEMUR_LENGTH / 2),
                        -90 * DEGTORAD, -5 * DEGTORAD, true, 160);
    createRevoluteJoint(right_leg_lower, right_leg_foot,
                        b2Vec2(0, -TIBIA_LENGTH / 2),
                        -36 * DEGTORAD, 30 * DEGTORAD, true, 70);

    createRevoluteJoint(lower_torso, left_leg_upper,
                        b2Vec2(0, -TORSO_LOWER_HEIGHT),
                        -25 * DEGTORAD, 30 * DEGTORAD, true, 250);
    createRevoluteJoint(left_leg_upper, left_leg_lower,
                        b2Vec2(-FEMUR_WIDTH / 4, -FEMUR_LENGTH / 2),
                        -90 * DEGTORAD, -5 * DEGTORAD, true, 160);
    createRevoluteJoint(left_leg_lower, left_leg_foot,
                        b2Vec2(0, -TIBIA_LENGTH / 2),
                        -36 * DEGTORAD, 30 * DEGTORAD, true, 70);


    b2FixtureDef sensorFixtureDef;
}

Hooman::~Hooman()
{
    for (auto i = bodies.begin();
         i != bodies.end();
         ++i)
    {
        world.DestroyBody(*i);
    }

}

b2Body* Hooman::createBoxElement(const b2Vec2& size, const b2Vec2& position)
{
    b2BodyDef prototypeBodyDef;
    b2FixtureDef prototypeFixtureDef;
    b2PolygonShape prototypeShape;
    b2Body* result;

    prototypeBodyDef.type =  b2_dynamicBody;
    prototypeBodyDef.linearDamping = 0;
    prototypeBodyDef.angularDamping = 0.001;
    prototypeBodyDef.allowSleep = false;
    prototypeBodyDef.awake = true;
    prototypeBodyDef.active = true;
    prototypeBodyDef.position = position;

    result = world.CreateBody(&prototypeBodyDef);

    prototypeShape.SetAsBox(size(0) / 2.0, size(1) / 2.0);

    prototypeFixtureDef.restitution = 0.1;
    prototypeFixtureDef.friction = 0.01;
    prototypeFixtureDef.density = 50;
    prototypeFixtureDef.shape = &prototypeShape;
    prototypeFixtureDef.filter.groupIndex = -1;

    result->CreateFixture(&prototypeFixtureDef);

    sizes[result] = size;

    bodies.push_back(result);

    return result;
}

b2Joint* Hooman::createRevoluteJoint(b2Body* bodyA,
                                     b2Body* bodyB,
                                     const b2Vec2& deltaPosition,
                                     double minAngle,
                                     double maxAngle,
                                     bool /*enableMotor*/,
                                     double maxMotorTorque)
{
    b2RevoluteJointDef jointDef;
    b2RevoluteJoint* result;
    b2Vec2 position(bodyA->GetPosition()(0) + deltaPosition(0),
                    bodyA->GetPosition()(1) + deltaPosition(1));

    jointDef.Initialize(bodyA, bodyB, position);
    jointDef.lowerAngle = minAngle;
    jointDef.upperAngle = maxAngle;
    jointDef.enableLimit = true;
    jointDef.maxMotorTorque = maxMotorTorque;
    jointDef.motorSpeed = 0;
    jointDef.enableMotor = true;
    jointDef.collideConnected = false;

    result = (b2RevoluteJoint*) world.CreateJoint(&jointDef);

    joints.push_back(result);

    return result;
}

b2Joint* Hooman::createWeldJoint(b2Body* bodyA,
                                 b2Body* bodyB,
                                 const b2Vec2& anchorA,
                                 const b2Vec2& anchorB,
                                 double referenceAngle)
{
    b2WeldJointDef jointDef;
    b2Joint* result;

    jointDef.bodyA = bodyA;
    jointDef.bodyB = bodyB;
    jointDef.localAnchorA = anchorA;
    jointDef.localAnchorB = anchorB;
    jointDef.referenceAngle = referenceAngle;

    result = world.CreateJoint(&jointDef);

    return result;
}

void Hooman::render_to_cairo(cairo_t* cr, bool blackout)
{
    for (auto i = bodies.begin();
         i != bodies.end();
         ++i)
    {
        const b2Body* body;
        body = *i;

        const b2Vec2 size = sizes[body];
        b2Vec2 position = body->GetPosition();
        float32 angle = body->GetAngle();

        cairo_save(cr);
        cairo_translate(cr, position(0), position(1));
        cairo_rotate(cr, angle);

        if (blackout)
        {
            cairo_rectangle(cr, -size(0) / 2.0 - .1, -size(1) / 2.0 - .1,
                            size(0) + .2, size(1) + .2);
            cairo_set_source_rgb(cr, 0, 0, 0);
            cairo_fill(cr);
        }
        else
        {
            cairo_rectangle(cr, -size(0) / 2.0, -size(1) / 2.0,
                            size(0), size(1));
            cairo_set_source_rgba(cr, rr * 0.9, gg * 0.9, bb * 0.9, 0.9);
            cairo_fill_preserve(cr);
            cairo_set_source_rgba(cr, rr, gg, bb, 0.9);
            cairo_stroke(cr);
        }
        cairo_restore(cr);
    }
}
