#include <string>
#include <sstream>

#ifndef DICTCC_EXCEPTIONS_INCLUDED
#define DICTCC_EXCEPTIONS_INCLUDED

namespace dictcc
{
  /*! \brief Exception class to be thrown if there is a general problem with the dictionary.
   */
  class dict_exception : public std::exception
  {
    private:
      std::string d_file;
      int d_line;

    protected:
      std::string d_msg;

    public:
      dict_exception(const std::string file, const int line, const std::string msg)
        : d_msg(msg), d_file(file), d_line(line)
      {
        std::ostringstream os;
        os << d_file << ": " << d_line << ": " << d_msg;
        d_msg = os.str();
      }
      /*! \brief Get the exception identifier.
      */
      const char* what() const noexcept
      {
        return d_msg.c_str();
      };
      /*! \brief Get the naked file where the exception happened.
      */
      std::string file() const noexcept {return d_file;}
      /*! \brief Get line where the exception happened.
      */
      int line() const noexcept {return d_line;}
  };

  /*! \brief Exception class to be thrown if no results have been found for a search.
   */
  class dict_no_results : public dict_exception
  {
    public:
      dict_no_results(const std::string file, const int line, const std::string msg = "")
        : dict_exception(file, line, msg) {}
      /*! \brief Change message content of a exception, that has been thrown.
       */
      void operator<<(const std::string& new_msg) noexcept
      {
        this->d_msg += new_msg;
      }
  };

  /*! \brief Exception class to be thrown if there is a libcurl issue.
   */
  class dict_libcurl_error : public dict_exception
  {
    public:
      dict_libcurl_error(const std::string file, const int line, const std::string msg)
        : dict_exception(file, line, msg) {}
  };

  /*! \brief Exception class to be thrown if there is a libcurl issue.
   */
  class dict_lang_error : public dict_exception
  {
    public:
      dict_lang_error(const std::string file, const int line, const std::string msg = "Language is not supported.")
        : dict_exception(file, line, msg) {}
  };

} // namespace dictcc

#endif // DICTCC_EXCEPTIONS_INCLUDED
