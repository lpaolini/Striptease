#ifndef Remote_h
#define Remote_h

#include <Arduino.h>
#include "Controller.h"
#include "Timer.h"

#define IRMP_PROTOCOL_NAMES             1

#include <irmp.c.h>

class Remote {
    private:
        IRMP_DATA irmp_data;

    protected:
        Controller *controller;
        virtual void handleCommand(uint8_t protocol, uint16_t command, bool repeated) = 0;

    public:
        Remote(Controller *controller) {
            this->controller = controller;
        }
        
        void setup() {
            irmp_init();
            irmp_irsnd_LEDFeedback(true);
            Serial.print("Supported IR protocols: ");
            irmp_print_active_protocols(&Serial);
            Serial.println();
        }

        void loop() {
            if (irmp_get_data(&irmp_data)) {
                // irmp_result_print(&irmp_data);
                uint8_t protocol = irmp_data.protocol;
                uint16_t command = irmp_data.command;
                bool repeated = irmp_data.flags & IRMP_FLAG_REPETITION;
                handleCommand(protocol, command, repeated);
            }
        }
};

#endif
