/*
* Copyright (c) 2016, Wind River Systems, Inc.
*
* Redistribution and use in source and binary forms, with or without modification, are
* permitted provided that the following conditions are met:
*
* 1) Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2) Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation and/or
* other materials provided with the distribution.
*
* 3) Neither the name of Wind River Systems nor the names of its contributors may be
* used to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <mraa.h>

#define LED	13	/* GPIO pin of the on board LED */
#define BUTTON	3       /* GPIO pin with push button */

int main(int argc, char** argv)
{
    mraa_platform_t platform;                /* Type of platform we are on */
    mraa_gpio_context gpio_led = NULL;       /* LED GPIO descriptor */
    mraa_gpio_context gpio_button = NULL;    /* BUTTON GPIO descriptor */
    mraa_aio_context adc_a0 = NULL;          /* Analog-Digital descriptor */
    uint32_t adc_val;                       /* ADC value */
    float delay;                             /* Delay between blinks */
    int ledstate = 0;                        /* LED state, 0=off, 1=on */


    /*
     * Print banner.
     */
     platform = mraa_get_platform_type();
     fprintf(stdout, "MRAA C Demonstration\n");
     fprintf(stdout, "LIBMRAA Version: %s\n", mraa_get_version());
     fprintf(stdout, "Board: %s\n", mraa_get_platform_name());

     /*
      * Check that we are running on the correct board
      */
     platform = mraa_get_platform_type();
     if (platform != MRAA_INTEL_GALILEO_GEN2)
        {
        fprintf(stderr, "ERROR: This program is for a Intel Galileo Gen 2 Board\n");
        exit (-1);
        }

    /*
     * Initialize the LED gpio pin and set it as an output
     */
    gpio_led = mraa_gpio_init(LED);
    if (gpio_led == NULL)
        {
        fprintf(stderr, "Could not initialize LED gpio\n");
        exit (-1);
        }
    mraa_gpio_dir(gpio_led, MRAA_GPIO_OUT);

    /*
     * Initialize the Button gpio pin and set it as an input
     */
     gpio_button = mraa_gpio_init(BUTTON);
     if (gpio_button == NULL)
         {
         fprintf(stderr, "Could not initialize BUTTON gpio\n");
         }
    mraa_gpio_dir(gpio_button, MRAA_GPIO_IN);

    /*
     * Initialize the Analog-Digital converter channel 0
     */

    adc_a0 = mraa_aio_init(0);
    if (adc_a0 == NULL)
        {
        fprintf(stderr, "Failed to initalize ADC channel A0\n");
        exit (-1);
        }

    printf("Vary the rate of blink by turning the poteniometer on A0\n");
    printf("Exit the program by pressing the button on D%d\n\n", BUTTON);

    /*
     * Run the loop until the BUTTON is held down.
     * Each time through the loop, read the potentiometer on A0 and
     * adjust the blink rate.
     */
    while (1)
        {
        if (mraa_gpio_read(gpio_button) == 1)
            break;

        if (adc_a0 != NULL)
            {
            adc_val = mraa_aio_read(adc_a0);
            /* fprintf(stdout, "ADC A0 = %d\n", adc_val); */
            if (adc_val != 0)
                delay = 1000000 * ((float)adc_val/1024);
            else
                delay = 1000000 * (1/1024);
            }

        ledstate = !ledstate;

        mraa_gpio_write(gpio_led, ledstate);

        usleep((long)delay);
        }

    /*
     * Clean up and exit
     */
    (void)mraa_gpio_close(gpio_led);
    (void)mraa_gpio_close(gpio_button);
    (void)mraa_aio_close(adc_a0);

    exit(0);
}
