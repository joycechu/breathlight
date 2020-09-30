
CC	= arm-none-linux-gnueabi-gcc 

LIBS	= -lm
CFLAGS	= -O3 -Wall -Winline -pipe

SRC	= pwm_sin.c pwm_asin.c pwm_gussian.c

OBJ	= $(SRC:.c=.o)
BINS	= $(SRC:.c=)

all:	$(BINS)

pwm_sin:	pwm_sin.o
		$(CC) -o $@ pwm_sin.o $(LIBS)

pwm_asin:	pwm_asin.o
		$(CC) -o $@ pwm_asin.o $(LIBS)

pwm_gussian:	pwm_gussian.o
		$(CC) -o $@ pwm_gussian.o $(LIBS)


.c.o:
		$(CC) -c $(CFLAGS) $< -o $@ 

.PHONY:		clean
clean:
		rm -f $(OBJ) $(BINS)

