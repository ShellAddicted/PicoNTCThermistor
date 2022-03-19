#include <cmath>
#include <string>

#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"

class NTCThermistorBaseException : public std::exception {
   protected:
    std::string _msg;

   public:
    NTCThermistorBaseException(std::string message = "Exception occurred") { _msg = message; };
    virtual const char* what() const throw() { return _msg.c_str(); }
};

class NTCThermistorInvalidPin : public NTCThermistorBaseException {
   public:
    NTCThermistorInvalidPin(std::string message = "Only pins 26-27-28-29 are allowed.") : NTCThermistorBaseException(message){};
};

class NTCThermistor {
   protected:
    const float K = 273.15;
    const float conversion_factor = 3.3f / (1 << 12);

    uint8_t pin = 0;
    uint32_t known_resistor = 0;
    uint8_t samples_n = 0;
    uint8_t adc_ch = 0;
    float b = 0;
    float rb = 0;
    float tb = 0;

    float c2k(float c);
    float k2c(float k);

   public:
    NTCThermistor(uint8_t pin, uint32_t known_resistor = 10000, float b = 3950, float rb = 100000, float tb = 25,
                  uint8_t samples_n = 0);
    float getResistanceFromTempC(float temp_c);
    float getTempCFromResistance(float r);
    float readTempC();
};
