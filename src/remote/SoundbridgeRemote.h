#ifndef SoundbridgeRemote_h
#define SoundbridgeRemote_h

#include "remote/IRRemote.h"

class SoundbridgeRemote : public IRRemote {
    private:
        static const uint16_t CMD_POWER = 0x16;
        static const uint16_t CMD_BRIGHTNESS = 0x42;
        static const uint16_t CMD_HOME = 0x17;
        static const uint16_t CMD_SEARCH = 0x18;
        static const uint16_t CMD_BACK = 0x15;
        static const uint16_t CMD_UP = 0x12;
        static const uint16_t CMD_LEFT = 0x10;
        static const uint16_t CMD_OK = 0x14;
        static const uint16_t CMD_RIGHT = 0x11;
        static const uint16_t CMD_DOWN = 0x13;
        static const uint16_t CMD_PREVIOUS = 0x1B;
        static const uint16_t CMD_PLAY = 0x19;
        static const uint16_t CMD_NEXT = 0x1A;
        static const uint16_t CMD_PAUSE = 0x1C;
        static const uint16_t CMD_INCREASE = 0x40;
        static const uint16_t CMD_SHUFFLE = 0x1E;
        static const uint16_t CMD_PLUS = 0x1D;
        static const uint16_t CMD_DECREASE = 0x41;
        static const uint16_t CMD_CYCLE = 0x1F;
        static const uint16_t MODE_NORMAL = 0;
        static const uint16_t MODE_TIME = 1;

        void handleCommand(uint8_t protocol, uint16_t command, bool repeated) override {
            if (protocol == 2) { // P=NEC A=0x906F
                if (!repeated) {
                    handleNonRepeatableKey(command);
                }
                handleRepeatableKey(command);
            }
        }
        
        void handleRepeatableKey(uint16_t key) {
            switch(key) {
                case CMD_UP:
                    controller->increaseParam();
                    break;
                case CMD_DOWN:
                    controller->decreaseParam();
                    break;
                case CMD_LEFT:
                    controller->selectPreviousFx();
                    break;
                case CMD_RIGHT:
                    controller->selectNextFx();
                    break;
                case CMD_DECREASE:
                    controller->decreaseBrightness();
                    break;
                case CMD_INCREASE:
                    controller->increaseBrightness();
                    break;
            }
        };

        void handleNonRepeatableKey(uint16_t key) {
            switch(key) {
                case CMD_HOME:
                    controller->selectFx(0);
                    break;
                case CMD_PLAY:
                    controller->play();
                    break;
                case CMD_POWER:
                    controller->stop();
                    break;
                case CMD_CYCLE:
                    controller->sequential();
                    break;
                case CMD_SHUFFLE:
                    controller->shuffle();
                    break;
                case CMD_BACK:
                    controller->reset();
                    break;
                case CMD_PAUSE:
                    controller->pause();
                    break;
                case CMD_PREVIOUS:
                    controller->selectPreviousFx();
                    break;
                case CMD_NEXT:
                    controller->selectNextFx();
                    break;
                case CMD_LEFT:
                    // controller->prevParam();
                    break;
                case CMD_RIGHT:
                    // controller->nextParam();
                    break;
                case CMD_SEARCH:
                    controller->toggleInput();
                    break;
                case CMD_OK:
                    controller->reset();
                    break;
            }
        }

    public:
        SoundbridgeRemote(Controller *controller) : IRRemote(controller) {};
};

#endif
