#ifndef DICTCC_DESV_INCLUDED
#define DICTCC_DESV_INCLUDED

// STD
#include <sstream>

// Dictcc API
#include "dict_int.h"

namespace dictcc
{
  class desv : public dict
  {
    // TODO: Implement specifics of the language here.
    private:
      bool noun(const std::ostringstream& req_answer, str_list_t& res);
    public:
      desv();
      ~desv()
      {}
  };
} // namespace dictcc

#endif // DICTCC_DESV_INCLUDED
