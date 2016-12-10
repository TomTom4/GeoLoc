#ifndef _SPI_H
#define _SPI_H

#define SPI_DATA_SIZE 10+1
#define SPI_CMD_SIZE 10

class Spi
{
private:
  char table_spi[SPI_CMD_SIZE][SPI_DATA_SIZE];
  char data_spi_RW[SPI_DATA_SIZE];
public:
  Spi();
  void spiCopyCmd(int cmd);
  int spiDataRW(char* data, int lenght);
  int spiPrintRW(void);
};

#endif
