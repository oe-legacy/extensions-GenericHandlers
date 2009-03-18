// Basic movement handler.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _MOVE_HANDLER_H_
#define _MOVE_HANDLER_H_

#include <Core/IModule.h>
#include <Display/Camera.h>
#include <Devices/IKeyboard.h>
#include <Devices/IMouse.h>
#include <Devices/IJoystick.h>
#include <Scene/TransformationNode.h>
#include <vector>
#include <Utils/Timer.h>

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Devices;
using OpenEngine::Utils::Timer;

/**
 * Camera movement handler
 */
class MoveHandler : public IModule, public IListener<KeyboardEventArg>,
                    public IListener<JoystickAxisEventArg> {
private:
    Timer timer;
    Camera& cam;
    IMouse& mouse;
    bool forward, back, right, left; // active move direction
    int lx, ly;                      // last mouse position
    int current;                     // current node
    bool objMove;   // if enabled objects from 1-9 can be moved. 0 = cam.
 
    // define the box where the mouse should be inside
    static const int minXY = 100, maxXY = 400, middleXY=((maxXY-minXY)/2)+minXY;
public:

    std::vector<TransformationNode*> nodes; // node list

    MoveHandler(Camera& cam, IMouse& mouse);
    ~MoveHandler();
    
    void SetObjectMove(bool enabled);

    void Handle(InitializeEventArg arg);
    void Handle(ProcessEventArg arg);
    void Handle(DeinitializeEventArg arg);
    void Handle(KeyboardEventArg arg);
    void Handle(JoystickAxisEventArg arg);
};

} // NS Utils
} // NS OpenEngine

#endif // _MOVE_HANDLER_H_
