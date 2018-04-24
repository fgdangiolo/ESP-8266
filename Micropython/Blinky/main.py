import utime
from machine import Pin


def main():
    led = Pin(2, Pin.OUT)

    while True:

        led.off()
        utime.sleep_ms(100)

        led.on()
        utime.sleep_ms(100)



if __name__ == '__main__':
    main()
