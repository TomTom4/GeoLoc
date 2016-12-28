#ifndef DEF_SPI
#define DEF_SPI

class Spi{
	public:
		static Spi* instance(); 
		void spiReadWriteData();
		void spiClearString();
		void spiAddData();
		void extractData();
		void spiMajCar();
	private:
		Spi();
		static Spi *s_instance;
		unsigned char m_length_string; 
		unsigned char* m_string_spi;
		unsigned char m_beacon_rasp_start;
		unsigned char m_beacon_rasp_end;
		unsigned char m_beacon_stm_start;
		unsigned char m_beacon_stm_end;
};

#endif
