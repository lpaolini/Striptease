#ifndef SerialRemote_h
#define SerialRemote_h

#include <Arduino.h>
#include "Controller.h"
#include "Timer.h"

class SerialRemote {
    private:
        static const unsigned char CMD_CONTINUE = 'C';
        static const unsigned char CMD_SHUFFLE = 'S';
        static const unsigned char CMD_PROGRAM = 'P';
        static const unsigned char CMD_1 = '1';
        static const unsigned char CMD_2 = '2';
        static const unsigned char CMD_3 = '3';
        static const unsigned char CMD_4 = '4';
        static const unsigned char CMD_5 = '5';
        static const unsigned char CMD_6 = '6';
        static const unsigned char CMD_7 = '7';
        static const unsigned char CMD_8 = '8';
        static const unsigned char CMD_9 = '9';
        static const unsigned char CMD_10PLUS = '.';
        static const unsigned char CMD_10 = '0';
        static const unsigned char CMD_CLEAR = 'X';
        static const unsigned char CMD_TIME = 'T';
        static const unsigned char CMD_CHECK = 'K';
        static const unsigned char CMD_REPEAT = 'R';
        static const unsigned char CMD_FADER = 'F';
        static const unsigned char CMD_PLAY = 'p';
        static const unsigned char CMD_PAUSE = ' ';
        static const unsigned char CMD_STOP = 's';
        static const unsigned char CMD_PREVIOUS = '<';
        static const unsigned char CMD_NEXT = '>';
        static const unsigned char CMD_PLUS = '=';
        static const unsigned char CMD_MINUS = '-';
        static const unsigned char CMD_BACKWARD = 'b';
        static const unsigned char CMD_FORWARD = 'f';
        static const unsigned char CMD_DECREASE_SPEED = '[';
        static const unsigned char CMD_INCREASE_SPEED = ']';
        static const unsigned char CMD_INCREASE_BRIGHTNESS = 'q';
        static const unsigned char CMD_DECREASE_BRIGHTNESS = 'a';
        static const uint8_t MODE_NORMAL = 0;
        static const uint8_t MODE_TIME = 1;

        Controller *controller;
        bool tenPlus = false;

        void handleNumericKey(int numKey) {
            int num = numKey;
            if (tenPlus) {
                num += 10;
                tenPlus = false;
            }
            controller->setParam(num);
        }

        void handleKey(unsigned char key) {
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
                    break;
                case CMD_TIME:
                    controller->cycleSpeed();
                    break;
                case CMD_CHECK:
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
                case CMD_BACKWARD:
                    break;
                case CMD_FORWARD:
                    break;
                case CMD_PLUS:
                    controller->increaseParam();
                    break;
                case CMD_MINUS:
                    controller->decreaseParam();
                    break;
                case CMD_DECREASE_SPEED:
                    controller->decreaseFxSpeed();
                    break;
                case CMD_INCREASE_SPEED:
                    controller->increaseFxSpeed();
                    break;
                case CMD_INCREASE_BRIGHTNESS:
                    controller->increaseBrightness();
                    break;
                case CMD_DECREASE_BRIGHTNESS:
                    controller->decreaseBrightness();
                    break;
            }
        }

    public:
        SerialRemote(Controller *controller) {
            this->controller = controller;
        }

        void setup() {}

        void loop() {
            if (Serial.available()) {
                handleKey(Serial.read());
            }
        }
};

#endif
