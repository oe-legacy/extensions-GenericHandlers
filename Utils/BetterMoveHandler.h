// 
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS)
//
// This program is free software; It is covered by the GNU General
// Public License version 2 or any later version.
// See the GNU General Public License for more details (see LICENSE).
//--------------------------------------------------------------------


#ifndef _BETTER_MOVE_HANDLER_H_
#define _BETTER_MOVE_HANDLER_H_

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
class BetterMoveHandler : public IModule,
                          public IListener<KeyboardEventArg>,
                          public IListener<JoystickAxisEventArg>,
                          public IListener<MouseMovedEventArg>,
                          public IListener<MouseButtonEventArg> {
private:
    Timer timer;
    //Camera& cam;
    vector<Camera*> cams;
    IMouse& mouse;
    bool forward, back, right, left; // active move direction
    int lx, ly;                      // last mouse position
    Vector<2,int> restorePos;
    unsigned int current;                     // current node
    bool objMove;   // if enabled objects from 1-9 can be moved. 0 = cam.
 
    // define the box where the mouse should be inside
    static const int minXY = 100, maxXY = 400, middleXY=((maxXY-minXY)/2)+minXY;
    bool mouseDownOnly;
    bool skip;    
    bool active;
    
    float moveScale;
    bool slow;
public:

    std::vector<TransformationNode*> nodes; // node list

    BetterMoveHandler(Camera& cam, IMouse& mouse, bool mouseDownOnly=false);
    ~BetterMoveHandler();
    
    void SetObjectMove(bool enabled);
    void SetMoveScale(float m);

    void PushCamera(Camera*);

    void Handle(Core::InitializeEventArg arg);
    void Handle(Core::ProcessEventArg arg);
    void Handle(Core::DeinitializeEventArg arg);
    void Handle(MouseMovedEventArg arg);
    void Handle(MouseButtonEventArg arg);
    void Handle(KeyboardEventArg arg);
    void Handle(JoystickAxisEventArg arg);
};

} // NS Utils
} // NS OpenEngine

#endif // _BETTER_MOVE_HANDLER_H_
