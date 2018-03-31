#ifndef DICTCC_DESV_INCLUDED
#define DICTCC_DESV_INCLUDED

// Dictcc API
#include "dict.h"

namespace dictcc
{
  class desv : public dict
  {
    // TODO: Implement specifics of the language here.
    public:
      desv();
      ~desv()
      {}
  };

  desv::desv()
  {
    d_suburl = "desv";
  }

} // namespace dictcc

#endif // DICTCC_DESV_INCLUDED
