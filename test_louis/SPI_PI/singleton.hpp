#ifndef SINGLETON_HPP
#define SINGLETON_HPP

class Singleton
{
private:
  Singleton(); // Private constructor
public:
  static Singleton* getInstance();
};


#endif
