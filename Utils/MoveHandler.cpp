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
      lx(middleXY), ly(middleXY), current(-1) {}

MoveHandler::~MoveHandler() {}

void MoveHandler::Handle(InitializeEventArg arg) {
    mouse.HideCursor();
    mouse.SetCursor(middleXY,middleXY);
    timer.Start();
}

void MoveHandler::Handle(DeinitializeEventArg arg) {}

void MoveHandler::Handle(ProcessEventArg arg) {
    MouseState s = mouse.GetState();
    unsigned int dt = timer.GetElapsedTimeAndReset().AsInt();

    // reset the position, if out of the box
    if (minXY > s.x || s.x > maxXY) {
        s.x = lx = middleXY;
    }
    if (minXY > s.y || s.y > maxXY) {
        s.y = ly = middleXY;
    }
    mouse.SetCursor(s.x,s.y);

    float ms=.0001*dt, rs=.007; // scaling factors

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
       if (dy) cam.Rotate(0, ms*dy*rs, 0);
        // rotate around up vector (positive goes left)
       if (dx) cam.Rotate(ms*dx*rs, Vector<3,float>(0,1,0));
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
    bool state = (arg.type == KeyboardEventArg::PRESS);
    switch (arg.sym) {
        // movement keys
    case KEY_w: forward = state; break;
    case KEY_s: back    = state; break;
    case KEY_a: left    = state; break;
    case KEY_d: right   = state; break;
        // object changing
    default: 
        if (arg.sym >= KEY_0 && arg.sym <= KEY_9)
            current = arg.sym - KEY_0 - 1;
        break;
        // ignore all other keys
    }
}

} // NS Utils
} // NS OpenEngine
