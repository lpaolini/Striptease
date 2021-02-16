#ifndef MyStage_h
#define MyStage_h

#include "AudioSensor.h"
#include "JoinedStrip.h"
#include "PhysicalStrip.h"
#include "ReversedStrip.h"
#include "Stage.h"
#include "State.h"
#include "SubStrip.h"

class MyStage : public Stage {
    private:
        const static uint16_t STRIP_LEFT_COUNT = 192;
        const static uint16_t STRIP_LEFT_DENSITY = 144;
        const static uint8_t STRIP_LEFT_PIN = CH1_PIN;

        const static uint16_t STRIP_RIGHT_COUNT = 192;
        const static uint16_t STRIP_RIGHT_DENSITY = 144;
        const static uint8_t STRIP_RIGHT_PIN = CH2_PIN;

        const static uint16_t STRIP_TOP_COUNT = 169;
        const static uint16_t STRIP_TOP_DENSITY = 60;
        const static uint8_t STRIP_TOP_PIN = CH6_PIN;
        
        // const static uint16_t STRIP_XMASTREE_COUNT = 240;
        const static uint16_t STRIP_XMASTREE_COUNT = 192;
        const static uint16_t STRIP_XMASTREE_DENSITY = 60;
        const static uint8_t STRIP_XMASTREE_PIN = CH3_PIN;

        const static uint8_t MAX_WATTS = 150;
        
        CRGBArray<STRIP_LEFT_COUNT> leftArray;
        CRGBArray<STRIP_RIGHT_COUNT> rightArray;
        CRGBArray<STRIP_TOP_COUNT> topArray;
        CRGBArray<STRIP_XMASTREE_COUNT> xmasTreeArray;

    public:
        MyStage(AudioSensor *audioSensor, State *state);
};

#endif
