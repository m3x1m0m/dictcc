#ifndef DICTCC_CREATOR_INCLUDED
#define DICTCC_CREATOR_INCLUDED

// Dictcc API
#include "dict_int.h"
#include "desv.h"
#include "deen.h"
#include "denl.h"
#include "types.h"
#include "exceptions.h"

namespace dictcc
{
  class creator
  {
    private:
      creator(){}
      ~creator(){}

    public:
      static std::shared_ptr<dict> create(const std::string langs)
      {
        lang_t l = dict::str2langs(langs);
        // TODO: Add new languages here
        switch (l) {
          case DESV:
            return std::make_shared<desv>();
          case DEEN:
            return std::make_shared<deen>();
          case DENL:
            return std::make_shared<denl>();
        default:
          throw(dict_lang_error(__FILE__, __LINE__));
      }
    }
  };
} // namespace dictcc

#endif // DICTCC_DESV_INCLUDED
