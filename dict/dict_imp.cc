#include "dict_int.h"

namespace dictcc
{

  dict::dict()
  {
    setlocale(LC_ALL, "");
  }

  const std::string dict::URL_HTTPS = "https://";
  const std::string dict::URL_REST = ".dict.cc/?s=";
  const std::string dict::QUERYA = "c1Arr = new Array";
  const std::string dict::QUERYB = "c2Arr = new Array";
  const std::string dict::QUERYC = ");";
  const std::string dict::SEPERATOR = "\",\"";

  void dict::parse_answer(const std::ostringstream& req_answer, const std::string& query, str_list_t& res)
  {
    std::string page = req_answer.str();
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
    boost::split(res, line, boost::is_any_of(SEPERATOR), boost::token_compress_on);
    // Last element is usually empty.
    if ( *(res.end()-1) == "") {
      res.pop_back();
    }
  }

  search_ptr_t dict::search(std::string word)
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
    str_list_t l0, l1;
    try {
      parse_answer(answer, QUERYA, l0);
      parse_answer(answer, QUERYB, l1);
    } catch (dict_no_results& e) {
      // The parsing might go wrong.
      e << std::string("Could not find ") + std::string("\"") + word + std::string("\".");
      throw;
    }
    // Check if there are words without translation
    if (l0.size() != l1.size()) {
      auto min = std::min(l0.size(), l1.size());
      l0.resize(min);
      l1.resize(min);
    }
    // Make pair and make shared ptr if necessary.
    auto pair = std::make_pair(l0, l1);
    if (d_translations == nullptr) {
      d_translations = std::make_shared<search_t>(pair);
    } else {
      *d_translations = pair;
    }
    // Return a shared pointer to the pair of lists
    return d_translations;
  }

  void dict::reset_search(void)
  {
      // Initialize the word lists so they are not empty.
      str_list_t l0(1, ""), l1(1, "");
      auto pair = std::make_pair(l0, l1);
      if (d_translations != nullptr)
      {
        *d_translations = pair;
      } else {
        // Apparently, the pointer has not been initialized yet.
        d_translations = std::make_shared<search_t>(pair);
      }
  }

  std::string dict::langs2str(const lang_t& lt)
  {
    // TODO: Add new languages here.
    std::vector<std::string> str = {"DESV", "DEEN"};
    if (lt >= str.size()) {
      throw(dict_lang_error(__FILE__, __LINE__));
    }
    return str[lt];
  }

  lang_t dict::str2langs(const std::string& str)
  {
    if (str == "DESV") {
      return DESV;
    } else if ( str == "DEEN") {
      return DEEN;
    } else {
      throw(dict_lang_error(__FILE__, __LINE__));
    }
  }

  size_t dict::actual_size(std::string str)
  {
    size_t bytes_checked = 0;
    size_t actual_size = 0;
    while (bytes_checked < str.size()) {
      bytes_checked += std::mblen(&str.c_str()[bytes_checked], str.size() - bytes_checked);
      actual_size++;
    }
    return actual_size;
  }
} // namespace dictcc


