# PicoNTCThermistor
A C++ way to read a NTCThermistor for Raspberry Pico C/C++ SDK.

## Getting started

Download this library
```bash
mkdir lib/
cd lib/
git clone https://github.com/ShellAddicted/PicoNTCThermistor
```

adjust your `CMakeLists.txt` accordingly:
```
# Add this line before target_link_libraries()
pico_add_subdirectory(lib/PicoNTCThermistor) 

# Add PicoNTCThermistor to your target_link_libraries()
# Example: target_link_libraries(PicoTest pico_stdlib PicoNTCThermistor)
```

Example:
```
#include <iostream>
#include "pico_ntc_thermistor.h"

int main() {
    stdio_init_all();
    adc_init();

    // Pin 27 = ADC1
    // 10e3 = 10k ohm (Known resistor)
    // 3950 = B value of the thermistor (Check your datasheet)
    // 100e3 = 100k ohm (Thermistor R @ T0)
    // 25°C = T0 (Usually 25, check your datasheet)
    // 0 = num of samples (0 = Single read)
    //     Increase this to get more accurate results, if samples > 0 the samples will be averaged
    NTCThermistor ntc(27, 10e3, 3950, 100e3, 25, 0);

    while (1) {
        printf("Temperature: %f°C\n", ntc.readTempC());
        sleep_ms(1000);
    }

    return 0;
}
```
## License
This library is [MIT](https://github.com/ShellAddicted/PicoNTCThermistor/blob/master/LICENSE) licensed.