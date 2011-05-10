#include <expat.h>
#include <string>
#include <stdint.h>


class my_parser
{
public:
  static void start(void *data, const char *el, const char **attr);
  static void end(void *data, const char *el);
  
  my_parser(const std::string & p_name);
  void parse(void);
private:
  void start_element(const std::string & p_name);
  void get_attribute(const std::string & p_name,const std::string & p_value);
  void end_element(const std::string & p_name);
  
  std::string m_name;
  XML_Parser m_parser;
  uint32_t m_depth;
};
