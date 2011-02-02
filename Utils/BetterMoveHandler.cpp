// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include "BetterMoveHandler.h"

#include <Devices/IMouse.h>
#include <Math/Vector.h>
#include <Logging/Logger.h>

namespace OpenEngine {
namespace Utils {

using OpenEngine::Math::Vector;
using OpenEngine::Scene::TransformationNode;
    
BetterMoveHandler::BetterMoveHandler(Camera& cam, IMouse& mouse, bool mouseDownOnly) 
: mouse(mouse),
    forward(false), back(false),
    right(false), left(false),
    lx(middleXY), ly(middleXY), 
    current(0), objMove(true),
    mouseDownOnly(mouseDownOnly), //skip(false),
    active(false),moveScale(0.0002),
    inverted(false), slow(false) {
    cams.push_back(&cam);
}

BetterMoveHandler::~BetterMoveHandler() {}

void BetterMoveHandler::PushCamera(Camera* c) {
    cams.push_back(c);
}

void BetterMoveHandler::SetObjectMove(bool enabled) {
    objMove = enabled;
}

void BetterMoveHandler::SetMoveScale(float m) {
    moveScale = m;
}

void BetterMoveHandler::SetInverted(bool inv) {
    inverted = inv;
}


void BetterMoveHandler::Handle(Core::InitializeEventArg arg) {
    if (!mouseDownOnly) {
        mouse.HideCursor();
        mouse.SetCursor(middleXY,middleXY);
    }
    timer.Start();
}

void BetterMoveHandler::Handle(Core::DeinitializeEventArg arg) {}

void BetterMoveHandler::Handle(MouseMovedEventArg arg) {
    Camera& cam = *(cams[current]);
    if (!active) return;
    if (arg.buttons & BUTTON_LEFT) {
        // if (skip) {
        //     skip = false;
        //     return;
        // }

        MouseState s = mouse.GetState();

        //bool reset = false;

        // // reset the position, if out of the box
        // if (minXY > s.x || s.x > maxXY) {
        //     s.x = lx = middleXY;
        //     reset = true;
        // }
        // if (minXY > s.y || s.y > maxXY) {
        //     s.y = ly = middleXY;
        //     reset = true;
        // }
        // if (reset) {
        //     mouse.SetCursor(lx, ly); //s.x,s.y);
        //     return; // Skip this event
        // }
        
        // compute rotate difference
        float dx = int(arg.x) - int(restorePos[0]); 
        //float dx = inverted ? -1 * arg.dx : arg.dx;
        float dy = int(arg.y) - int(restorePos[1]); 
        // float dy = inverted ? -1 * arg.dy : arg.dy;
        if (inverted) { dx = -dx; dy = -dy; }

        double rs = 0.005;

        
        // relative pitch (positive goes up)
        if (dy) cam.Rotate(0, dy*rs, 0);
        // rotate around up vector (positive goes left)
        if (dx) cam.Rotate(dx*rs, Vector<3,float>(0,1,0));
        
        // skip = true;
        mouse.SetCursor(restorePos[0],restorePos[1]);
   
    }
}
void BetterMoveHandler::Handle(MouseButtonEventArg arg) {
    if (arg.type == EVENT_PRESS && arg.button == BUTTON_LEFT) {
        restorePos[0] = arg.state.x;
        restorePos[1] = arg.state.y;
        mouse.HideCursor();
        active = true;
    } else if (arg.type == EVENT_RELEASE && arg.button == BUTTON_LEFT && active) {
        mouse.SetCursor(restorePos[0], restorePos[1]);
        mouse.ShowCursor();
        active = false;
    }
}
void BetterMoveHandler::Handle(Core::ProcessEventArg arg) {
    Camera& cam = *(cams[current]);

    unsigned int dt = timer.GetElapsedTimeAndReset().AsInt();
    double ms=(slow?0.1:1.0)*moveScale*dt; // Key moving depends on the time

    // compute move difference
    float x=0, z=0;
    if (forward)  z += ms;
    if (back)     z -= ms;
    if (left)     x -= ms;
    if (right)    x += ms;

    
    // move the camera [ Move(long, tran, vert) ]
    if (x || z) cam.Move(z,x,0);
    // relative pitch (positive goes up)
    
}

// set state of keys on up/down events
void BetterMoveHandler::Handle(KeyboardEventArg arg) {
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
        if (arg.sym >= KEY_0 && arg.sym <= KEY_9) {
            unsigned int c = arg.sym - KEY_0 - 1;
            if (c < cams.size())
                current = c;
        }
        break;
        // ignore all other keys
    }
}

void BetterMoveHandler::Handle(JoystickAxisEventArg arg) {
    
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
