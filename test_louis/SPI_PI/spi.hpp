#ifndef SPI_HPP
#define SPI_HPP

class Spi /*:: public Singleton*/
{
public:
  Spi(Car* voit);
  void readWriteData();
  void clearString();
  void addDataString();
  void extractUsSensor(int offset_string);
  void extractDataString();
  void extractEncodeur();
  void majCar();

private:
  unsigned char lenght_string;
  unsigned char* string_spi;
  Car* voiture;
};

#endif
