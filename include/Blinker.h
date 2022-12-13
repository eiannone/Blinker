#ifndef Blinker_h
#define Blinker_h

#include <Ticker.h>

enum BlinkMode { NORMAL, INVERT, SKIP_IF_ON };

class Blinker
{
public:
    
    Blinker(const uint8_t pin, BlinkMode mode = NORMAL) : _pin(pin), _mode(mode) {};
    ~Blinker() {};
    void start(uint32_t ms_on, uint32_t ms_off, size_t repeat = 0);
    void stop();
    void blink();
    void once(uint32_t ms);
    bool isActive();

private:
    uint8_t _pin;
    BlinkMode _mode;
    uint8_t _livFinale = 0;
    Ticker _t_blink;
    int _remaining = 0;
    size_t _ms_on;
    size_t _ms_off;
};

#endif