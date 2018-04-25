
from machine import Pin
from machine import ADC

def main():

    led = Pin(2, Pin.OUT)
    adc = ADC(0)

    while True:

        analog_value = adc.read()

        if analog_value>500:
            led.off()

        else:
            led.on()



if __name__ == '__main__':
    main()
