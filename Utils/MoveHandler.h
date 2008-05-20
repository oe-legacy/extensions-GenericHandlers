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
#include <Scene/TransformationNode.h>
#include <vector>

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Core;
using namespace OpenEngine::Display;
using namespace OpenEngine::Scene;
using namespace OpenEngine::Devices;

/**
 * Camera movement handler
 */
    class MoveHandler : public IModule, public IListener<KeyboardEventArg> {

private:
    Camera& cam;
    IMouse* mouse;
    bool forward, back, right, left; // active move direction
    int lx, ly;                      // last mouse position
    int current;                     // current node

    // define the box where the mouse should be inside
    static const int minXY = 100, maxXY = 400, middleXY=((maxXY-minXY)/2)+minXY;
public:

    std::vector<TransformationNode*> nodes; // node list

    MoveHandler(Camera& cam);
    ~MoveHandler();
    void Initialize();
    void Deinitialize();
    bool IsTypeOf(const std::type_info& inf);
    void Process(const float dt, const float percent);
    void Handle(KeyboardEventArg arg);
    void BindToEventSystem();
};

} // NS Utils
} // NS OpenEngine

#endif // _MOVE_HANDLER_H_
