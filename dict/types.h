#ifndef DICTCC_TYPES_INCLUDED
#define DICTCC_TYPES_INCLUDED
// STD
#include <string>
#include <utility>
#include <functional>
#include <vector>
// Dictcc API
//#include "dict.h"

namespace dictcc
{
  /*! \brief List of words in one language.
   */
  typedef std::vector<std::string> str_list_t;
  /*! \brief Pair of two string lists resulting from a search.
   */
  typedef std::pair<str_list_t, str_list_t> search_t;
  /*! \brief Shared pointer to search_t.
   */
  typedef std::shared_ptr<search_t> search_ptr_t;
  /*! \brief Supported language pairs.
   */
  typedef enum
  {
    DESV,
    DEEN
  } lang_t;
} // namespace dictcc

#endif // DICTCC_TYPES_INCLUDED
