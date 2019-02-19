#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "gpio.h"


int main(){

  uart_init();

    // Configure LED Matrix
  for(int i = 4; i <= 15; i++){
    GPIO->DIRSET = (1 << i);
    GPIO->OUTCLR = (1 << i);
  }

  // Configure buttons
  GPIO->PIN_CNF[17] = 0;
  GPIO->PIN_CNF[26] = 0;

  ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }
    return count;
  }

  iprintf("Norway has %d counties.\n\r", 18);


  while(1){
    if(!(GPIO->IN & (1<<26))){    //sjekker om B er trykket
      uart_send('B');
    }
    if(!(GPIO->IN & (1<<17))){    //sjekker om A er trykket
      uart_send('A');
    }
    if(uart_read() != '\0'){
      if(!(GPIO->IN & (1<<13))){
        for(int i=13; i <=15; i++){
  				GPIO->OUTSET=(1<<i);		//turn off LED matrix if it is.
  			}
      } else{
          for(int i = 13; i <= 15; i++){
            GPIO->OUTCLR = (1 << i);	//turn on LED matrix if it is.
          }
        }
    }
  }
  return 0;
}
