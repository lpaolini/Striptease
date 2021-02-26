#ifndef SonyRemote_RMD420_h
#define SonyRemote_RMD420_h

#include "Remote.h"
#include "Controller.h"

class SonyRemote_RMD420 : public Remote {
    private:
        static const uint16_t CMD_CONTINUE = 0x89D;
        static const uint16_t CMD_SHUFFLE = 0x8B5;
        static const uint16_t CMD_PROGRAM = 0x89F;
        static const uint16_t CMD_1 = 0x880;
        static const uint16_t CMD_2 = 0x881;
        static const uint16_t CMD_3 = 0x882;
        static const uint16_t CMD_4 = 0x883;
        static const uint16_t CMD_5 = 0x884;
        static const uint16_t CMD_6 = 0x885;
        static const uint16_t CMD_7 = 0x886;
        static const uint16_t CMD_8 = 0x887;
        static const uint16_t CMD_9 = 0x888;
        static const uint16_t CMD_10PLUS = 0x8A7;
        static const uint16_t CMD_10 = 0x8A0;
        static const uint16_t CMD_CLEAR = 0x88F;
        static const uint16_t CMD_TIME = 0x8A8;
        static const uint16_t CMD_CHECK = 0x88D;
        static const uint16_t CMD_REPEAT = 0x8AC;
        static const uint16_t CMD_FADER = 0x8DF;
        static const uint16_t CMD_PLAY = 0x8B2;
        static const uint16_t CMD_PAUSE = 0x8B9;
        static const uint16_t CMD_STOP = 0x8B8;
        static const uint16_t CMD_PREVIOUS = 0x8B0;
        static const uint16_t CMD_NEXT = 0x8B1;
        static const uint16_t CMD_PLUS = 0x892;
        static const uint16_t CMD_BACKWARD = 0x8B3;
        static const uint16_t CMD_FORWARD = 0x8B4;
        static const uint16_t CMD_MINUS = 0x893;

        bool tenPlus = false;

        void handleCommand(uint8_t protocol, uint16_t command, bool repeated) {
            if (protocol == 1) { // P=SIRCS A=0x0)
                if (!repeated) {
                    handleNonRepeatableKey(command);
                }
                handleRepeatableKey(command);
            }
        }
        
        void handleNumericKey(int numKey) {
            int num = numKey;
            if (tenPlus) {
                num += 10;
                tenPlus = false;
            }
            controller->setParam(num);
        };
        
        void handleRepeatableKey(uint16_t key) {
            switch(key) {
                case CMD_PLUS:
                    controller->increaseBrightness();
                    break;
                case CMD_MINUS:
                    controller->decreaseBrightness();
                    break;
                case CMD_BACKWARD:
                    controller->decreaseParam();
                    break;
                case CMD_FORWARD:
                    controller->increaseParam();
                    break;
            }
        };

        void handleNonRepeatableKey(uint16_t key) {
            switch(key) {
                case CMD_CONTINUE:
                    controller->sequential();
                    break;
                case CMD_SHUFFLE:
                    controller->shuffle();
                    break;
                case CMD_PROGRAM:
                    break;
                case CMD_1:
                    handleNumericKey(1);
                    break;
                case CMD_2:
                    handleNumericKey(2);
                    break;
                case CMD_3:
                    handleNumericKey(3);
                    break;
                case CMD_4:
                    handleNumericKey(4);
                    break;
                case CMD_5:
                    handleNumericKey(5);
                    break;
                case CMD_6:
                    handleNumericKey(6);
                    break;
                case CMD_7:
                    handleNumericKey(7);
                    break;
                case CMD_8:
                    handleNumericKey(8);
                    break;
                case CMD_9:
                    handleNumericKey(9);
                    break;
                case CMD_10:
                    handleNumericKey(10);
                    break;
                case CMD_10PLUS:
                    tenPlus = true;
                    break;
                case CMD_CLEAR:
                    controller->setMode();
                    break;
                case CMD_TIME:
                    controller->cycleSpeed();
                    break;
                case CMD_CHECK:
                    controller->toggleInput();
                    break;
                case CMD_REPEAT:
                    controller->reset();
                    break;
                case CMD_FADER:
                    break;
                case CMD_PLAY:
                    controller->play();
                    break;
                case CMD_PAUSE:
                    controller->pause();
                    break;
                case CMD_STOP:
                    controller->stop();
                    break;
                case CMD_PREVIOUS:
                    controller->selectPreviousFx();
                    break;
                case CMD_NEXT:
                    controller->selectNextFx();
                    break;
            }
        }

    public:
        SonyRemote_RMD420(Controller *controller) : Remote(controller) {};
};

#endif
