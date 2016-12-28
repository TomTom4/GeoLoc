#ifndef DEF_CONTROLER
#define DEF_CONTROLER


class Controler{
	public:
		//methodes
		static Controler *instance();
	private:
		//Constructeur
		Controler();
		//attributs
		static Controler *s_instance;
};
#endif
