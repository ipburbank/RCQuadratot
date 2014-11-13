/**

 */

#include "neuralNet.h"

void ANN::loadXML()
{
  TiXmlDocument doc("runs/gen1/individual.xml");
  bool loadOkay = doc.LoadFile();
  if (loadOkay)
    {
      TiXmlNode* pChild;
      TiXmlText* pText;
      int t;
      
      for ( pChild = doc.FirstChild();
            pChild != 0; pChild = pChild->NextSibling()) 
	{
          t = pChild->Type();

          switch ( t )
            {
            case TiXmlNode::DOCUMENT:
              break;

            case TiXmlNode::ELEMENT:
              printf( "Element [%s]", pChild->Value() );
              //switch(pParent->Value()):
                
              break;

            case TiXmlNode::COMMENT:
              break;

            case TiXmlNode::UNKNOWN:
              break;

            case TiXmlNode::TEXT:
              break;

            case TiXmlNode::DECLARATION:
              break;
              
            default:
              break;
            }
	}
    }
  else
    {
      printf("Failed to load file");
      exit;
    }
}

/*
array<float, NUMOUTPUTNEURONS>
ANN::evaluate(array<float, NUMINTPUTNEURONS> inputs)
{
    array<float, NUMHIDDENNEURONS> hidden;
    
    //load inputs
    auto first = hidden.begin();
    auto last = hidden.end();
    while (first!=last) {
    fn (*first);
    ++first;
    }
}
*/
