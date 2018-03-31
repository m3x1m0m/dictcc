#include <string>
#include <utility>
#include <functional>
#include <vector>

#ifndef DICTCC_TYPES_INCLUDED
#define DICTCC_TYPES_INCLUDED

namespace dictcc
{
  /*! \brief List of words in one language.
   */
  typedef std::vector<std::string> word_list_t;
  /*! \brief Pair of two word lists with corresponding word/sentence pairs (translations) resulting from a search string.
   */
  typedef std::pair<word_list_t*, word_list_t*> search_t;
  /*! \brief Supported language pairs.
   */
  typedef enum
  {
    DESV,
    DEEN
  } lang_t;
} // namespace dictcc

#endif // DICTCC_TYPES_INCLUDED
