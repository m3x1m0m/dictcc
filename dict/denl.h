#ifndef DICTCC_DENL_INCLUDED
#define DICTCC_DENL_INCLUDED

// STD
#include <sstream>
// Boost
// Dictcc API
#include "dict_int.h"

namespace dictcc
{
  class denl : public dict
  {
    // TODO: Implement specifics of the language here.
    private:
      bool noun(const std::ostringstream& req_answer, str_list_t& res);
    public:
      denl();
      ~denl()
      {}
  };
} // namespace dictcc

#endif // DICTCC_DENL_INCLUDED
