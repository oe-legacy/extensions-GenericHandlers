#ifndef _RENDER_STATE_HANDLER_H_
#define _RENDER_STATE_HANDLER_H_

#include <Core/IListener.h>
#include <Devices/Symbols.h>
#include <Devices/IKeyboard.h>
#include <Scene/RenderStateNode.h>

using namespace OpenEngine;
using namespace OpenEngine::Display;
using namespace OpenEngine::Devices;

class RenderStateHandler : public Core::IListener<KeyboardEventArg> {
private:
    Scene::RenderStateNode& rNode;
public:
 RenderStateHandler(Scene::RenderStateNode& rNode) : rNode(rNode) {}
    void Handle(KeyboardEventArg arg) {
        if (arg.type == EVENT_PRESS) {
            switch (arg.sym) {
            case KEY_F1:
                rNode.ToggleOption(RenderStateNode::WIREFRAME); break;
            case KEY_F2:
                rNode.ToggleOption(RenderStateNode::TEXTURE); break;
            case KEY_F3:
                rNode.ToggleOption(RenderStateNode::SOFT_NORMAL); break;
            case KEY_F4:
                rNode.ToggleOption(RenderStateNode::SHADER); break;
            case KEY_F5:
                rNode.ToggleOption(RenderStateNode::BACKFACE); break;
            case KEY_F6:
                rNode.ToggleOption(RenderStateNode::HARD_NORMAL); break;
            case KEY_F7: 
                rNode.ToggleOption(RenderStateNode::BINORMAL); break;
            case KEY_F8:
                rNode.ToggleOption(RenderStateNode::TANGENT); break;
        default: break;
        }
        }
    }
};

#endif
