// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "MoveHandler.h"

#include <Devices/IMouse.h>
#include <Math/Vector.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Utils {

using OpenEngine::Math::Vector;
using OpenEngine::Scene::TransformationNode;

MoveHandler::MoveHandler(Camera& cam, IMouse& mouse) 
: cam(cam), mouse(mouse),
    forward(false), back(false),
    right(false), left(false),
    lx(middleXY), ly(middleXY), current(-1), objMove(false), slow(false),
    moveScale(0.0002)
{}

MoveHandler::~MoveHandler() {}

void MoveHandler::SetObjectMove(bool enabled) {
    objMove = enabled;
}

void MoveHandler::SetMoveScale(float m) {
    moveScale = m;
}


void MoveHandler::Handle(Core::InitializeEventArg arg) {
    mouse.HideCursor();
    mouse.SetCursor(middleXY,middleXY);
    timer.Start();
}

    void MoveHandler::Handle(Core::DeinitializeEventArg arg) {}

    void MoveHandler::Handle(MouseMovedEventArg arg) {}
    void MoveHandler::Handle(Core::ProcessEventArg arg) {
        
    MouseState s = mouse.GetState();
    unsigned int dt = timer.GetElapsedTimeAndReset().AsInt();

    //logger.info << "dt: " << dt << logger.end;

    bool reset = false;

    // reset the position, if out of the box
    if (minXY > s.x || s.x > maxXY) {
        s.x = lx = middleXY;
        reset = true;
    }
    if (minXY > s.y || s.y > maxXY) {
        s.y = ly = middleXY;
        reset = true;
    }
    if (reset) {
        mouse.SetCursor(lx, ly); //s.x,s.y);
        return; // Skip this event
    }

    double ms=(slow?0.1:1.0)*moveScale*dt, // Key moving depends on the time        
        rs=0.01; // Rotation does not depend on time!

    // compute move difference
    float x=0, z=0;
    if (forward)  z += ms;
    if (back)     z -= ms;
    if (left)     x -= ms;
    if (right)    x += ms;

    // compute rotate difference
    float dx = (float)lx - (float)s.x; // moving mouse up = positive value
    float dy = (float)ly - (float)s.y; // moving to the left = positive value

    if (current < 0) {
        // move the camera [ Move(long, tran, vert) ]
        if (x || z) cam.Move(z,x,0);
        // relative pitch (positive goes up)
       if (dy) cam.Rotate(0, dy*rs, 0);
        // rotate around up vector (positive goes left)
       if (dx) cam.Rotate(dx*rs, Vector<3,float>(0,1,0));
    } else {
        if ((unsigned)current < nodes.size()) {
            if (x || z)   nodes[current]->Move(x,0,-z);
            if (dy || dx) nodes[current]->Rotate(-dy*rs*ms, dx*rs*ms, 0);
        }
    }

    // update last
    lx = s.x;
    ly = s.y;
}

// set state of keys on up/down events
void MoveHandler::Handle(KeyboardEventArg arg) {
    bool state = (arg.type == EVENT_PRESS);
    switch (arg.sym) {
        // movement keys
    case KEY_w: forward = state; break;
    case KEY_s: back    = state; break;
    case KEY_a: left    = state; break;
    case KEY_d: right   = state; break;

    case KEY_LSHIFT:
    case KEY_RSHIFT:
        slow = state; break;
        // object changing
    default: 
        if (objMove && arg.sym >= KEY_0 && arg.sym <= KEY_9)
            current = arg.sym - KEY_0 - 1;
        break;
    
    }
}

void MoveHandler::Handle(JoystickAxisEventArg arg) {
    
    float max = 1 << 15;
    float thres = 0.5;
    

    float up = (-arg.state.axisState[3])/max;
    float down = (arg.state.axisState[3])/max;

    float left_j = (-arg.state.axisState[2])/max;
    float right_j = (arg.state.axisState[2])/max;

    forward = (up > thres);
    back = (down > thres);
    left = (left_j > thres);
    right = (right_j > thres);


}

} // NS Utils
} // NS OpenEngine
