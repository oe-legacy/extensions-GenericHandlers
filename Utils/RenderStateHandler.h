#ifndef _RENDER_STATE_HANDLER_H_
#define _RENDER_STATE_HANDLER_H_

#include <Core/IListener.h>
#include <Devices/Symbols.h>
#include <Devices/IKeyboard.h>
#include <Scene/RenderStateNode.h>
#include <Logging/Logger.h>
#include <Devices/KeyboardActionMapper.h>

using namespace OpenEngine;
using namespace OpenEngine::Display;
using namespace OpenEngine::Devices;

class StateToggleActionArg {
public:
    RenderStateNode::RenderStateOption opt;
};

class RenderStateHandler : public Core::IListener<KeyboardEventArg>,
                           public Core::IListener<StateToggleActionArg> {
    class KeyboardMap : public KeyboardActionMapper<StateToggleActionArg> {
    public:
        KeyboardMap(RenderStateHandler& rh) {
            onKeyEvent(KEY_F1, EVENT_PRESS, rh);
            onKeyEvent(KEY_F2, EVENT_PRESS, rh);
            onKeyEvent(KEY_F3, EVENT_PRESS, rh);
            onKeyEvent(KEY_F4, EVENT_PRESS, rh);
            onKeyEvent(KEY_F5, EVENT_PRESS, rh);
            onKeyEvent(KEY_F6, EVENT_PRESS, rh);
            onKeyEvent(KEY_F7, EVENT_PRESS, rh);
            onKeyEvent(KEY_F8, EVENT_PRESS, rh);
        }

        StateToggleActionArg toAction(KeyboardEventArg arg) {
            StateToggleActionArg rarg;
            rarg.opt = RenderStateNode::WIREFRAME;
            
            switch (arg.sym) {
            case KEY_F1:
                rarg.opt = RenderStateNode::WIREFRAME; break;
            case KEY_F2:
                rarg.opt = RenderStateNode::TEXTURE; break;
            case KEY_F3:
                rarg.opt = RenderStateNode::SOFT_NORMAL; break;
            case KEY_F4:
                rarg.opt = RenderStateNode::SHADER; break;
            case KEY_F5:
                rarg.opt = RenderStateNode::BACKFACE; break;
            case KEY_F6:
                rarg.opt = RenderStateNode::HARD_NORMAL; break;
            case KEY_F7: 
                rarg.opt = RenderStateNode::BINORMAL; break;
            case KEY_F8:
                rarg.opt = RenderStateNode::TANGENT; break;
            default: break;
        }
        return rarg;
        }
    };


private:
    Scene::RenderStateNode& rNode;
    KeyboardMap *km;
public:
    RenderStateHandler(Scene::RenderStateNode& rNode) : rNode(rNode) {
        km = new KeyboardMap(*this);        
    }
    ~RenderStateHandler() {
        delete km;
    }

    void Handle(StateToggleActionArg arg) {
        logger.info << "hey?" << logger.end;
        rNode.ToggleOption(arg.opt);
    }

    void Handle(KeyboardEventArg arg) {
        km->Handle(arg);    
    }
};

#endif
