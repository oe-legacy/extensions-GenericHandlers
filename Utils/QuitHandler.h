#ifndef _QUIT_HANDLER_H_
#define _QUIT_HANDLER_H_

#include <Devices/Symbols.h>
#include <Devices/IKeyboard.h>

using namespace OpenEngine::Devices;

/**
 * Quit handler.
 *
 * This is an example of a keyboard listener.
 * Every time the a key is released a key (UP) event is sent to the
 * handle method. If the key symbol is escape it quits the application.
 */
class QuitHandler {
public:
    void HandleQuit(KeyboardEventArg arg) {
        if (arg.sym == KEY_ESCAPE) {
            IGameEngine::Instance().Stop();
        }
    }
    
    void BindToEventSystem() {
        Listener<QuitHandler, KeyboardEventArg>* quit_l
            = new Listener<QuitHandler, KeyboardEventArg>
	  (*this, &QuitHandler::HandleQuit);
        IKeyboard::keyUpEvent.Add(quit_l);
    }
};
 
#endif
