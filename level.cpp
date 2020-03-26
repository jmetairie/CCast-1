
#include <fstream>
#include <string>

#include "misc.h"
#include "level.h"



Level::Level() {
  this->height = 0 ;
  this->width = 0 ;
  this->array = NULL ;
}

// destructor
Level::~Level()
{
  for(int i=0;i<height;i++)
  {
	delete[] this->array[i] ;
  }
  delete[] this->array ;
}

Level::Level(std::string path)
{
  load(path) ;
}


// Accessors

unsigned int Level::get_height() {
  return this->height ;
}

unsigned int Level::get_width() {
  return this->width ;
}

unsigned int** Level::get_array() {
  return this->array ;
}



// Methods
bool Level::load(std::string path) {
  std::ifstream file(path) ;
  std::string local ;
  bool ret = false ;
  if (file.is_open())
  {
	// Read Height/Width
	std::getline(file, local) ;
	this->height = std::stoi(misc::split(local,",", __MISC_LEFT__)) ;
	this->width = std::stoi(misc::split(local,",", __MISC_RIGHT__)) ;
	// Array Generation
	this->array = new unsigned int*[height] ;
	for(int i=0 ; i < this->height ; i++) { array[i] = new unsigned int[width] ; }
	int line = 0 ;
	while(std::getline(file, local) && line < this->height)
	{
	   for(int i=0;i<this->width;i++) {this->array[line][i] = int(local.at(i << 1)-'0') ; }
	   line++ ;
	}
	file.close() ;
  }
  return ret ;
}
