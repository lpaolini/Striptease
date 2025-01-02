#ifndef SonyRemote_RMD420_h
#define SonyRemote_RMD420_h

#include "remote/IRRemote.h"

class SonyRemote_RMD420 : public IRRemote {
    private:
        static const uint16_t CMD_CONTINUE = 29;
        static const uint16_t CMD_SHUFFLE = 53;
        static const uint16_t CMD_PROGRAM = 31;
        static const uint16_t CMD_1 = 0;
        static const uint16_t CMD_2 = 1;
        static const uint16_t CMD_3 = 2;
        static const uint16_t CMD_4 = 3;
        static const uint16_t CMD_5 = 4;
        static const uint16_t CMD_6 = 5;
        static const uint16_t CMD_7 = 6;
        static const uint16_t CMD_8 = 7;
        static const uint16_t CMD_9 = 8;
        static const uint16_t CMD_10PLUS = 39;
        static const uint16_t CMD_10 = 32;
        static const uint16_t CMD_CLEAR = 15;
        static const uint16_t CMD_TIME = 40;
        static const uint16_t CMD_CHECK = 13;
        static const uint16_t CMD_REPEAT = 44;
        static const uint16_t CMD_FADER = 95;
        static const uint16_t CMD_PLAY = 50;
        static const uint16_t CMD_PAUSE = 57;
        static const uint16_t CMD_STOP = 56;
        static const uint16_t CMD_PREVIOUS = 48;
        static const uint16_t CMD_NEXT = 49;
        static const uint16_t CMD_PLUS = 18;
        static const uint16_t CMD_BACKWARD = 51;
        static const uint16_t CMD_FORWARD = 52;
        static const uint16_t CMD_MINUS = 19;

        bool tenPlus = false;

        void handleCommand(uint8_t protocol, uint16_t command, bool repeated) override {
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
                    controller->toggleAudio();
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
        SonyRemote_RMD420(Controller *controller) : IRRemote(controller) {};
};

#endif
