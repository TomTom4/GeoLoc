#ifndef SPI_H
#define SPI_H


/* DECLARATIONS GLOBALES */
//extern const int SPI_DATA_SIZE;
extern char data_spi_RW[10/*SPI_DATA_SIZE*/];

int spiDataRW(char* data, int lenght);
int spiPrintRW(void);

#endif
