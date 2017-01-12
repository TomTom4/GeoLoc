#ifndef DEF_NAVIGATION
#define DEF_NAVIGATION


class Navigation{

	public:
		//methodes
		static Navigation *instance();
	private:
		//Constructeur
		Navigation();
		//attributs
		static Navigation *s_instance;
	
};

#endif
