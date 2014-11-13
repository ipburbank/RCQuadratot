/*
  Artificial Neural Network
*/

#ifndef NEURALNET_H
#define NEURALNET_H

#include <array>

#include "tinyxmldll.h"
#include <boost/filesystem.hpp>

#define NUMINPUTNEURONS 2
#define NUMHIDDENNEURONS 15
#define NUMHIDDENLAYERS 1
#define NUMOUTPUTNEURONS 2

using namespace std;

class ANN
{
 public:
  ANN(){};
  ~ANN(){};

  void loadXML();

  /*
  array<float, NUMOUTPUTNEURONS>
    evaluate(array<float, NUMINPUTNEURONS> input);
  */
 private:
};

#endif
