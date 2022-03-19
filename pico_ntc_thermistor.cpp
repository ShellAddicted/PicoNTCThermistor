#include "pico_ntc_thermistor.h"

NTCThermistor::NTCThermistor(uint8_t pin, uint32_t known_resistor, float b, float rb, float tb, uint8_t samples_n) {
    if (pin < 26 || pin > 29) {
        throw NTCThermistorInvalidPin();
    }

    this->pin = pin;
    this->known_resistor = known_resistor;
    this->samples_n = samples_n;
    this->adc_ch = pin - 26;
    this->b = b;
    this->rb = rb;
    this->tb = c2k(tb);

    adc_gpio_init(this->pin);
}

float NTCThermistor::getResistanceFromTempC(float temp_c) {
    float t = this->c2k(temp_c);
    return rb * (pow(M_E, (b / t - b / tb)));
}

float NTCThermistor::getTempCFromResistance(float r) {
    float t = 1 / ((1 / tb) + (log(r / rb) / b));
    return this->k2c(t);
}

float NTCThermistor::readTempC() {
    uint32_t result = 0;
    adc_select_input(this->adc_ch);
    if (this->samples_n == 0) {
        result = adc_read();
    } else {
        for (int i = 0; i < this->samples_n; i++) {
            result += adc_read();
            sleep_ms(1);
        };
        result /= this->samples_n;
    }
    float resistance = this->known_resistor / (4095.0f / result - 1);
    return getTempCFromResistance(resistance);
}

float NTCThermistor::k2c(float k) { return (k - this->K); }

float NTCThermistor::c2k(float c) { return (c + this->K); }