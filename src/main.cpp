#include "my_parser.h"
#include <iostream>

using namespace std;

int main(int argc,char **argv)
{
  if(argc != 2)
    {
      cout << "Usage is : demo_xml_parser.exe <xml_file>" << endl ;
      exit(-1);
    }

  my_parser l_parser(argv[1]);
  l_parser.parse();
}

//EOF
