#include <iostream>
#include "dict.h"

int main(int argc, char **argv)
{
  setlocale(LC_ALL, "");
  int c;
  char* lang_chr = nullptr;
  char* search_chr = nullptr;
  int nwords = -1;
  // TODO: Add new languages here.
  std::ostringstream langs;
  langs << "      DESV"                       << std::endl
        << "      DEEN"                       << std::endl;
  // Help stringstream
  std::ostringstream help;
  help  << "dictcc [OPTION] [ARGUMENT]"       << std::endl
        << "-h  Print this help message."     << std::endl
        << "-l  Specify language."            << std::endl
        << "    Currently supported:"         << std::endl
        << langs.str()
        << "-s  Word to search for."          << std::endl
        << "-n  Number of words to be printed"<< std::endl;
  // Settings getopt.
  opterr = 0;
  // Get arguments.
  while ( (c = getopt (argc, argv, "hl:s:n:") ) != -1) {
    switch (c)
    {
      case 'h':
        std::cout << help.str();
        exit(EXIT_SUCCESS);
      case 'l':
        lang_chr = optarg;
        break;
      case 's':
        search_chr = optarg;
        break;
      case 'n':
        nwords = std::stol(optarg);
        break;
      case '?':
        if (isprint (optopt))
          std::cerr << "Unknown option " << optopt << std::endl;
        else
          std::cerr << "Unknown option character." << std::endl;
        exit(EXIT_FAILURE);
      default:
        abort ();
      }
    }
  // Sanity checks.
  if (argc < 2) {
    std::cout << "Please use this CLI the following way.\n" << std::endl;
    std::cout << help.str();
    exit(EXIT_FAILURE);
  }
  if (lang_chr == nullptr) {
    std::cerr << "Language has to specified." << std::endl;
    exit(EXIT_FAILURE);
  }
  if (search_chr == nullptr) {
    std::cerr << "String to search for has to be specified." << std::endl;
    exit(EXIT_FAILURE);
  }
  // Make new didctionary and search.
  std::string lang(lang_chr);
  std::shared_ptr<dictcc::dict> dictionary = nullptr;
  dictcc::search_ptr_t result;
  try {
    dictionary = dictcc::creator::create(lang);
    result = dictionary->search(search_chr);
  } catch (const dictcc::dict_exception& e) {
    std::cout << "Unfortunately something went wrong. We are very sorry about that :(" << std::endl
              << "See below for further information on the error occured."  << std::endl
              << e.what()                                                   << std::endl;
    exit(EXIT_FAILURE);
  }
  // A search returns a pair of word lists.
  int max_len = 0;
  // Find longest strting for formatting purposes.
  for (const std::string& str: result->first) {
    if (dictcc::dict::actual_size(str) > max_len) {
      max_len = dictcc::dict::actual_size(str);
    }
  }
  // Default number of words to be printed is 8.
  if (nwords < 0) {
    nwords = (result->first).size() > 8 ? nwords = 8 : nwords = (result->first).size();
  }
  // Avoid segmentation fault.
  if (nwords > (result->first).size()) {
    nwords = (result->first).size();
  }
  // Print on console.
  for (int i = 0; i < nwords; i++) {
    std::cout << (result->first)[i];
    for (int j=0; j < ( max_len - dictcc::dict::actual_size( (result->first)[i] ) + 10); j++) {
      std::cout << ".";
    }
    std::cout << (result->second)[i] << std::endl;
  }
}
