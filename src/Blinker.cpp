#include <Arduino.h>
#include "Blinker.h"

void Blinker_ticker(Blinker* blinker)
{
    blinker->blink();
}

void Blinker::start(uint32_t ms_on, uint32_t ms_off, size_t repeat)
{
    if (isActive()) stop();
    if (_mode == SKIP_IF_ON && digitalRead(_pin) == HIGH) return;

    _remaining = (repeat > 0)? repeat*2 : -1;    
    _ms_on = ms_on;
    _ms_off = ms_off;
    
    _livFinale = (_mode == INVERT)? digitalRead(_pin) : LOW;
    pinMode(_pin, OUTPUT);    
    if (_mode != INVERT) {
        digitalWrite(_pin, HIGH);
        _remaining--;
    }    
    _t_blink.once_ms(ms_on, Blinker_ticker, this);
}

void Blinker::blink()
{
    if (_remaining > 0) --_remaining;
    if (_remaining == 0) {
        _t_blink.detach();
        digitalWrite(_pin, _livFinale);
        return;
    }    
    uint8_t level = digitalRead(_pin);
    digitalWrite(_pin, !level);
    _t_blink.once_ms(level? _ms_on : _ms_off, Blinker_ticker, this);
}

void Blinker::stop()
{
    _t_blink.detach();
    _remaining = 0;
    digitalWrite(_pin, _livFinale);
}

void Blinker::once(uint32_t ms)
{
    start(ms, ms, 1);
}

bool Blinker::isActive()
{
    return _remaining > 0 || _t_blink.active();
}