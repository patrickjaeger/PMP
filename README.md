#PMP
## Set up programmable air
1. Follow steps on https://github.com/Programmable-Air/Code
2. Upload PMP code

## Use 
1. Connect power to programmable-air; the LEDs will glow red
2. Push the blue button to calibrate the atmosphric pressure; the LEDs will turn orange
3. Push the blue button again to open all valves; the LEDs will turn yellow
    - Opening the valves prevents pressure build-up in the system while connecting tubes
    - The valves become hot after prolonged disengagement, therefore they are programmed to close automatically after 30 seconds
4. Connect tube to the microplate and push the blue button again to close the valves; the LEDs will turn green
5. Push the RED button to activate the pump

## Tuning the pump protocol
To alter the target pressure change the value of the variable 'pressureGain' in the PMP_main file
(target_pressure = atmospheric_pressure * pressure_gain)

