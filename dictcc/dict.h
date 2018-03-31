// STD
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <functional>
#include <vector>
// Curl
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
// Boost
#include <boost/algorithm/string.hpp>
// Dictcc API
#include "types.h"
#include "exceptions.h"

#ifndef DICTCC_DICT_INCLUDED
#define DICTCC_DICT_INCLUDED

namespace dictcc
{
  /*! \brief Base dictionary class.
   */
  class dict
  {
    protected:
      static const std::string URL_HTTPS;
      static const std::string URL_REST;
      static const std::string QUERYA;
      static const std::string QUERYB;
      static const std::string QUERYC;
      static const std::string SEPERATOR;

    protected:
      /*! \brief Word list corresponding to one language.
       */
      word_list_t d_wordsl0;
      /*! \brief Word list corresponding to one language.
       */
      word_list_t d_wordsl1;
      curlpp::Easy d_request;
      curlpp::Cleanup d_cleaner;
      lang_t d_langs;
      std::string d_suburl;

    protected:
      void parse_answer(const std::ostringstream& os, const std::string& query, word_list_t& vec);

    protected:
      dict(){}

    public:
      static dict* create(const std::string langs);
      virtual ~dict(){}

    public:
      search_t search(std::string word);
      static std::string langs2str(const lang_t& lt);
      static lang_t str2langs(const std::string& str);
  };

  const std::string dict::URL_HTTPS = "https://";
  const std::string dict::URL_REST = ".dict.cc/?s=";
  const std::string dict::QUERYA = "c1Arr = new Array";
  const std::string dict::QUERYB = "c2Arr = new Array";
  const std::string dict::QUERYC = ");";
  const std::string dict::SEPERATOR = "\",\"";

  void dict::parse_answer(const std::ostringstream& os, const std::string& query, word_list_t& vec)
  {
    std::string page = os.str();
    auto lstart = page.find(query);
    auto lend = page.find(QUERYC, lstart);
    // No results found -> throw an exception
    if(lstart == -1)
      throw(dict_no_results(__FILE__, __LINE__));
    lstart += query.size();
    // Scroll to the first character
    while( (page[lstart] == '\"') ||  (page[lstart] == ',') || (page[lstart] == '(') )
      lstart++;
    // Scroll to the last character
    while( (page[lstart] == '\"') ||  (page[lstart] == ',') || (page[lstart] == '(') )
      lend--;
    // Get the line.
    std::string line = page.substr(lstart, lend-lstart);
    // Split it.
    boost::split(vec, line, boost::is_any_of(SEPERATOR), boost::token_compress_on);
    // Last element is always empty.
    vec.pop_back();
    // Make sure, that the string termination is present.
    for (std::string& str : vec) {
      if (str[str.size()-1] != '\0' ) {
        str.append("\0");
      }
    }
  }

  search_t dict::search(std::string word)
  {
    std::ostringstream answer;
    // Perform HTTP request with SSL below.
    try {
      std::string dict_req = URL_HTTPS + d_suburl + URL_REST + word;
      curlpp::options::Url url(dict_req);
      d_request.setOpt(url);
      answer << d_request;
    } catch(curlpp::RuntimeError &e) {
      std::ostringstream ss;
      ss << e.what() << "(curlpp::RuntimeError).";
      throw(dict_libcurl_error(__FILE__, __LINE__, ss.str()));
    } catch(curlpp::LogicError &e) {
      std::ostringstream ss;
      ss << e.what() << "(curlpp::LogicError).";
      throw(dict_libcurl_error(__FILE__, __LINE__, ss.str()));
    }
    // Convert request into word lists language one and language two respectively.
    try {
      parse_answer(answer, QUERYA, d_wordsl0);
      parse_answer(answer, QUERYB, d_wordsl1);
    } catch (dict_no_results& e) {
      // The parsing might go wrong.
      e << std::string("Could not find ") + std::string("\"") + word + std::string("\".");
      throw;
    }
    // Return a pair of references
    return std::make_pair(&d_wordsl0, &d_wordsl1);
  }

  inline std::string dict::langs2str(const lang_t& lt)
  {
    // TODO: Add new languages here.
    std::vector<std::string> str = {"DESV", "DEEN"};
    if (lt >= str.size()) {
      throw(dict_lang_error(__FILE__, __LINE__));
    }
    return str[lt];
  }

  inline lang_t dict::str2langs(const std::string& str)
  {
    if (str == "DESV") {
      return DESV;
    } else if ( str == "DEEN") {
      return DEEN;
    } else {
      throw(dict_lang_error(__FILE__, __LINE__));
    }
  }

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

  dict* dict::create(const std::string langs)
  {
    lang_t l = str2langs(langs);
    // TODO: Add new languages here
    switch (l) {
      case DESV:
        return new desv;
        break;
      default:
        throw(dict_lang_error(__FILE__, __LINE__));
    }
  }
} // namespace dictcc

#endif // DICTCC_DICT_INCLUDED
