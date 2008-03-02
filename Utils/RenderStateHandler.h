#ifndef _RENDER_STATE_HANDLER_H_
#define _RENDER_STATE_HANDLER_H_

#include <Devices/Symbols.h>
#include <Devices/IKeyboard.h>

using namespace OpenEngine::Devices;

class RenderStateHandler {
private:
    RenderStateNode* rNode;
public:
    RenderStateHandler(RenderStateNode* rNode) : rNode(rNode) {}
    void Handle(KeyboardEventArg arg) {
        if (rNode == NULL) {
            logger.info << "ERROR NO RenderStateNode found!" << logger.end;
            return;
        }
        switch (arg.sym) {
        case KEY_F1: rNode->ToggleOptions(RenderStateNode::RENDER_WIREFRAMED);   break;
        case KEY_F2: rNode->ToggleOptions(RenderStateNode::RENDER_TEXTURES);     break;
        case KEY_F3: rNode->ToggleOptions(RenderStateNode::RENDER_NORMALS);      break;
        case KEY_F4: rNode->ToggleOptions(RenderStateNode::RENDER_SHADERS);      break;
        case KEY_F5: rNode->ToggleOptions(RenderStateNode::RENDER_BACKFACES);    break;
        case KEY_F6: rNode->ToggleOptions(RenderStateNode::RENDER_HARD_NORMAL);  break;
        case KEY_F7: rNode->ToggleOptions(RenderStateNode::RENDER_BINORMALS);    break;
        case KEY_F8: rNode->ToggleOptions(RenderStateNode::RENDER_TANGENTS);     break;
        default: break;
        }
    }

    void BindToEventSystem() {
        Listener<RenderStateHandler, KeyboardEventArg>* rStateListener
            = new Listener<RenderStateHandler, KeyboardEventArg> (*this, &RenderStateHandler::Handle);
        IKeyboard::keyUpEvent.Add(rStateListener);
    }
};

#endif
