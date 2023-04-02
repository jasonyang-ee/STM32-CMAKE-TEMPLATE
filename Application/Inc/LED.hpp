#ifndef CORE_INC_LED
#define CORE_INC_LED

#include "main.h"

/**
 * @brief Construct a new LED::led object
 * @param level Set britness % relative to PWM period value. 1000 is good
 * @param scale Set global dimmer for level.
 * @param freq Optional: Set external interrupt frequency.
 * @warning setPort(&htimX->CCRX) is required to run.
 *
 */
class LED {
   public:
    LED(int32_t, int32_t);
    LED(int32_t, int32_t, uint16_t);
    virtual ~LED();

    void setPort(__IO uint32_t *);
    void setScale(int32_t);
    void setLevel(int32_t);
    void addLevel(int32_t);

    void on();
    void off();
    void toggle();
    void setState(bool);

    void scheduler();

    void breath();
    void blink();
    void rapid();

   private:
    void applyCCR();
    void zeroCCR();
    bool getActiveModeState();
    void activeModeOff();

    // Setting
    __IO uint32_t *m_CCR;         // Ex: htim3.Instance->CCR2 for Timer3 Channel2
    int32_t m_level{0};           // light level
    int32_t m_scale{1};           // light scale
	uint16_t m_ext_freq{0};
	uint16_t m_schedule{0};

    // Time Based for 20Hz Scheduling
    bool m_breath_toggle{0};
    bool m_blink_toggle{0};
    bool m_rapid_toggle{0};

    uint16_t m_blink_timer{0};
    uint16_t m_rapid_timer{0};

    uint8_t m_breath_itr{0};
    uint16_t m_breath[25] = {0,   50,  100, 170, 290, 430, 600, 690, 770, 830, 910, 970, 990,
                             990, 840, 700, 550, 450, 370, 290, 230, 190, 160, 100, 60};
};

#endif /* CORE_INC_LED */
