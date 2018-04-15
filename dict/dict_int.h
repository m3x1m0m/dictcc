#ifndef DICTCC_DICT_INTERFACE_INCLUDED
#define DICTCC_DICT_INTERFACE_INCLUDED

// STD
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
#include <clocale>
// Curl
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
// Boost
#include <boost/algorithm/string.hpp>
// Dictcc API
#include "types.h"
#include "exceptions.h"

namespace dictcc
{
  /*! \brief Base dictionary class.
   */
  class dict
  {
    private:
      static const std::string URL_HTTPS;
      static const std::string URL_REST;
      static const std::string QUERYA;
      static const std::string QUERYB;
      static const std::string QUERYC;
      static const std::string SEPERATOR;

    private:
      /*! \brief Translations found by the search for a string.
       */
      search_ptr_t d_translations = nullptr;
      /*! \brief Additional information e.g. different forms of a verb.
       */
      search_ptr_t d_additional = nullptr;
      curlpp::Easy d_request;
      curlpp::Cleanup d_cleaner;
      lang_t d_langs;

    private:
      void parse_answer(const std::ostringstream& req_answer, const std::string& query, str_list_t& res);
      virtual bool noun(const std::ostringstream& req_answer, str_list_t& res)=0;

    protected:
      std::string d_suburl;

    protected:
      dict();

    public:
      virtual ~dict(){}

    public:
      /*! \brief Perform a search and create a smart pointer object.
       */
      search_ptr_t search(std::string word);
      /*! \brief Make sure there are two empty word lists.
       */
      void reset_search(void);
      static std::string langs2str(const lang_t& lt);
      static lang_t str2langs(const std::string& str);
      /*! \brief Help function: Get the size of a string in chars containing multibyte characters e.g. ü.
       */
      static size_t actual_size(std::string str);
  };
} // namespace dictcc

#endif // DICTCC_DICT_INTERFACE_INCLUDED
