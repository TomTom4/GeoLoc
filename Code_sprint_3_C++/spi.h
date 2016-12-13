#ifndef _SPI_H
#define _SPI_H

#define SPI_DATA_SIZE 20+1
#define SPI_CMD_SIZE 10

class Spi
{
private:
  char table_spi[SPI_CMD_SIZE][SPI_DATA_SIZE];
  char data_spi_RW[SPI_DATA_SIZE];
  float mesure1,mesure2;
public:
  Spi();
  void spiCopyCmd(int cmd);
  int spiDataRW(char* data, int lenght);
  int spiPrintRW(void);
  float spiGetMesure1();
  float spiGetMesure2();
  void spiPrint(void);
};

#endif
