// Toggle render state
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_SIMPLE_RENDER_STATE_HANDLER_H_
#define _OE_SIMPLE_RENDER_STATE_HANDLER_H_

#include <Core/IListener.h>
#include <Devices/IKeyboard.h>
#include <Scene/RenderStateNode.h>

namespace OpenEngine{
namespace Utils {

using Scene::RenderStateNode;
using Core::IListener;
using namespace Devices;

class SimpleRenderStateHandler : public IListener<Devices::KeyboardEventArg> {
private:
    RenderStateNode* rsn;
public:
    SimpleRenderStateHandler(RenderStateNode* rsn) : rsn(rsn)  {
    }
    virtual ~SimpleRenderStateHandler() {}

    void SetRenderStateNode(RenderStateNode* rsn) {
        this->rsn = rsn;
    }

    void Handle(KeyboardEventArg arg) {
        if (rsn == NULL) {
            logger.warning << "No RenderStateNode in RenderStateHandler." << logger.end;
            return;
        }

        if (arg.type == EVENT_PRESS) {
            RenderStateNode::RenderStateOption opt = rsn->GetEnabled();
            switch(arg.sym) {
            case KEY_1: rsn->ToggleOption(RenderStateNode::LIGHTING); break;
            case KEY_2: rsn->ToggleOption(RenderStateNode::WIREFRAME); break;
            case KEY_3: rsn->ToggleOption(RenderStateNode::TEXTURE); break;
            case KEY_4: rsn->ToggleOption(RenderStateNode::SHADER); break;
            case KEY_5: rsn->ToggleOption(RenderStateNode::COLOR_MATERIAL); break;
            case KEY_6: rsn->ToggleOption(RenderStateNode::SOFT_NORMAL); break;
            case KEY_7: rsn->ToggleOption(RenderStateNode::HARD_NORMAL); break;
            case KEY_8: rsn->ToggleOption(RenderStateNode::BACKFACE); break;
            default:break;
            } 
            // Print status if any change.
            if (rsn->GetEnabled() != opt) {
                logger.info << rsn->ToString() << logger.end;
            }
        }
    }
};

} // NS Utils
} // NS OpenEngine

#endif //_OE_SIMPLE_RENDER_STATE_HANDLER_H_
