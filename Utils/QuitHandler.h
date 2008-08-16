#ifndef _QUIT_HANDLER_H_
#define _QUIT_HANDLER_H_

#include <Core/IEngine.h>
#include <Devices/Symbols.h>
#include <Devices/IKeyboard.h>

using OpenEngine::Core::IEngine;
using namespace OpenEngine::Devices;

namespace OpenEngine {
namespace Utils {

/**
 * Quit handler.
 *
 * This is an example of a keyboard listener.
 * Every time the a key is released a key (UP) event is sent to the
 * handle method. If the key symbol is escape it quits the game.
 */
class QuitHandler : public IListener<KeyboardEventArg> {
    IEngine& engine;
public:
    QuitHandler(IEngine& engine) : engine(engine) {}
    void Handle(KeyboardEventArg arg) {
        if (arg.sym == KEY_ESCAPE)
            engine.Stop();
    }
};
 
} // NS Utils
} // NS OpenEngine

#endif // NS _QUIT_HANDLER_H_
