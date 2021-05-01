#pragma once


//
// �g�[�N��
struct Token
{
  enum Type
  {
    Number,
    String,
    Char,
    Ident,
    Operator
  };

  Type type = Number;
  std::string str;

  Object obj;
  size_t srcpos = 0;

  Token()
  {
  }

  Token(Token const& tok);

  Token& operator = (Token const& tok);

  [[noreturn]]
  void Error(std::string const& msg);
};
