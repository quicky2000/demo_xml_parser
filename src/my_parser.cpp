#include "my_parser.h"

#include <iostream>
#include <fstream>
#include <assert.h>

my_parser::my_parser(const std::string & p_name):
  m_name(p_name),
  m_parser(XML_ParserCreate(NULL)),
  m_depth(0)
{
  if (!m_parser)
    {
      std::cout << "Couldn't allocate memory for parser" << std::endl ;
      exit(-1);
    }

  XML_SetUserData(m_parser,this);
  XML_SetElementHandler(m_parser,start, end);
}

void my_parser::parse(void)
{
  std::ifstream l_file(m_name.c_str());
  if(!l_file)
    {
      std::cout << "ERROR : Could not open file \"" << m_name << "\"" << std::endl ;
      exit(-1);
    }
  const uint32_t l_size = 10;
  char l_buf[l_size];
  bool l_end = false;
  while(! (l_end = l_file.eof()))
    {
      l_file.read(l_buf,l_size);
      if (! XML_Parse(m_parser, l_buf,l_file.gcount(),l_end))
	{
	  std::cout << "ERROR : Parse error at line " << XML_GetCurrentLineNumber(m_parser) << " :" << XML_ErrorString(XML_GetErrorCode(m_parser)) << std::endl;
	  exit(-1);
	}
    }
  l_file.close();
  std::cout << "PARSE SUCCESSFULL" << std::endl ;
}

void my_parser::start(void *data, const char *el, const char **attr)
{
  my_parser *l_parser = static_cast<my_parser*>(data);
  assert(l_parser);
  l_parser->start_element(el);
  for (uint32_t i = 0; attr[i]; i += 2)
    {
      l_parser->get_attribute(attr[i],attr[i+1]);
    }
}

void my_parser::end(void *data, const char *el)
{
  my_parser *l_parser = static_cast<my_parser*>(data);
  assert(l_parser);
  l_parser->end_element(el);
}

void my_parser::start_element(const std::string & p_name)
{
  for(uint32_t l_index= 0 ; l_index < m_depth;++l_index)
    {
      std::cout << "  " ;
    }
  std::cout << "Starting element \"" << p_name << "\"" << std::endl ;
  ++m_depth;
}

void my_parser::end_element(const std::string & p_name)
{
  --m_depth;
  for(uint32_t l_index= 0 ; l_index < m_depth;++l_index)
    {
      std::cout << "  " ;
    }
  std::cout << "Ending element \"" << p_name << "\"" << std::endl ;
}

void my_parser::get_attribute(const std::string & p_name,const std::string & p_value)
{
  for(uint32_t l_index= 0 ; l_index < m_depth;++l_index)
    {
      std::cout << "  " ;
    }
  std::cout << "attribute[\"" << p_name << "\"] = \"" << p_value << "\"" << std::endl;
}

//EOF
