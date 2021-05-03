#pragma once

class Program
{
  static Program* instance;

  std::vector<Object> variables;
  std::string source;

  Tokenizer* tokenizer;
  ParserCore* parser;

  AST::Stmt* prs_result;

  friend class AST_Runner;

public:
  Program();

  void OpenFile(std::string const& path);

  void Tokenize();
  void Parse();

  Object Run();

  [[noreturn]]
  static void Error(Token const& tok, std::string const& msg);
};
