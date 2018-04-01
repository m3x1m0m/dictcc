#ifndef DICTCC_DEEN_INCLUDED
#define DICTCC_DEEN_INCLUDED

// STD
#include <sstream>
// Boost
// Dictcc API
#include "dict_int.h"

namespace dictcc
{
  class deen : public dict
  {
    // TODO: Implement specifics of the language here.
    private:
      bool noun(const std::ostringstream& req_answer, str_list_t& res);
    public:
      deen();
      ~deen()
      {}
  };
} // namespace dictcc

#endif // DICTCC_DEEN_INCLUDED
