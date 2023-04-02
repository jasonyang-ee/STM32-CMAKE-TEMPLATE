#include "LED.hpp"

LED::LED(int32_t level, int32_t scale) {
    m_level = level;
    m_scale = scale;
}

LED::LED(int32_t level, int32_t scale, uint16_t freq) {
    m_level = level;
    m_scale = scale;
    m_ext_freq = freq;
}

LED::~LED() { zeroCCR(); }

/**
 * @brief Initialize with Timer PWM CCR register address reference.
 * @param port Timer PWM CCR register.
 * @note Must use after HAL_TIM_PWM_Start().
 * @note Timer_1 Channel_3: setPort(&htim1.Instance->CCR3)
 */
void LED::setPort(__IO uint32_t *CCR) { m_CCR = CCR; }

/**
 * @brief Turn on LED
 *
 */
void LED::on() { setState(1); }

/**
 * @brief Turn off LED
 *
 */
void LED::off() { setState(0); }

/**
 * @brief Toggle LED on/off state
 *
 */
void LED::toggle() {
    if (*m_CCR > 0)
        zeroCCR();
    else
        applyCCR();
}

/**
 * @brief Programmable On/Off setter.
 * @param state on=true, off=false
 */
void LED::setState(bool state) {
    activeModeOff();
    if (state)
        applyCCR();
    else
        zeroCCR();
}

/**
 * @brief Set brightness dimming scale.
 * @param value division value
 */
void LED::setScale(int32_t value) {
    if (getActiveModeState())
        m_scale = value;
    else {
        m_scale = value;
        applyCCR();
    }
}

/**
 * @brief Set brightness max level.
 *
 * @param value max to be PWM period value
 */
void LED::setLevel(int32_t value) {
    if (getActiveModeState())
        m_level = value;
    else {
        m_level = value;
        applyCCR();
    }
}

/**
 * @brief Increase or Decrease current level
 *
 * @param value supports both positive and negative int32_t
 */
void LED::addLevel(int32_t value) {
    if (value > 0) {
        if ((m_level + value) < 1000)
            m_level += value;
        else {
            m_level = 1000;
        }
    } else if (value < 0) {
        {
            if ((m_level + value) > 0)
                m_level += value;
            else {
                m_level = 0;
            }
        }
    }
    if (!getActiveModeState()) on();
}

/**
 * @brief Use in timer interrupt to allow active mode, breath, blink, etc..
 *
 * @note Timer interrupt frequency is set during object initializaiton.
 */
void LED::scheduler() {
	// Supporting both thread or timer interrupt active mode schedule for consistant 20Hz
    if (m_ext_freq != 0) ++m_schedule %= (m_ext_freq/20);

	// Active mode schedule logic
    if (m_schedule == 0) {
        if (m_breath_toggle) {
            if (++m_breath_itr < 25)
                m_level = m_breath[m_breath_itr];
            else
                m_breath_itr = 0;

            *m_CCR = m_level / m_scale;
        }

        // Slow Blinking LED Logic
        else if (m_blink_toggle) {
            if (m_blink_timer > 5) {
                toggle();
                m_blink_timer = 0;
            } else
                m_blink_timer++;
        }

        // Fast Blinking LED Logic
        else if (m_rapid_toggle) {
            if (m_rapid_timer > 1) {
                toggle();
                m_rapid_timer = 0;
            } else
                m_rapid_timer++;
        }
    }
}

/**
 * @brief Start breathing effect.
 *
 * LED breathing turn on. The brightness will change based on scheduler().
 */
void LED::breath() {
    activeModeOff();
    zeroCCR();
    m_breath_toggle = true;
}

/**
 * @brief Start slow blinking.
 *
 * LED blinking turn on. The on/off will change based on scheduler().
 */
void LED::blink() {
    activeModeOff();
    zeroCCR();
    m_blink_toggle = true;
}

/**
 * @brief Start fast blinking.
 *
 * Led blinking turn on. The on/off will change based on scheduler().
 */
void LED::rapid() {
    activeModeOff();
    zeroCCR();
    m_rapid_toggle = true;
}

// Private Functions

void LED::applyCCR() { *m_CCR = m_level / m_scale; }

void LED::zeroCCR() { *m_CCR = 0; }

bool LED::getActiveModeState() {
    return (m_breath_toggle || m_blink_toggle || m_rapid_toggle);
}

void LED::activeModeOff() {
    m_breath_toggle = false;
    m_blink_toggle = false;
    m_rapid_toggle = false;
}
