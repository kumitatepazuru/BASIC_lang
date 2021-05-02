#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <functional>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;


struct Token;
using ErrorInfo = std::pair<Token, std::string>;


template <class T, class F, class... Args>
int find_vector(std::vector<T>& vec, F compare, Args ...args)
{
  for( int i = 0; i < vec.size(); i++ )
    if( compare(vec[i], args...) )
      return i;

  return -1;
}


struct Object
{
  enum Type
  {
    Int,
    Float,
    Char,
    Array,
    Pointer
  };

  Type type;
  std::string name;

  int v_int;
  float v_float;
  char v_char;
  std::vector<Object> list;

  Object* var_ptr;

  Object(Type type = Int);

  Object& operator = (Object const& obj);

  std::string to_string() const;

  static void Clear(Object& obj);

  bool is_string() const;
  bool eval() const;
};

//
// トークン
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
  
  Token() { }
  Token(Token const& tok);
  
  Token& operator = (Token const& tok);
  
  
};

class AST
{
public:
  enum Type
  {
    Add,
    Sub,
    Mul,
    Div,
    Immidiate
  };
  
  AST* lhs = nullptr;
  AST* rhs = nullptr;
  Token* tok = nullptr;
  
  int varIndex = 0;
  
  AST(Type type) :type(type) { }
  
  AST(Type type, AST* lhs, AST* rhs, Token* tok = nullptr)
    :type(type), lhs(lhs), rhs(rhs), tok(tok)
  {
    
  }
};

class AST_Block : public AST
{
public:
  std::vector<AST_Block*> list;

  Object Run();
};

class AST_If : public AST
{
public:
  AST* cond;
  AST_Block* if_true;
  AST_Block* if_false;
};

class AST_While : public AST
{
public:
  AST* condition;
  AST_Block* stmt;
};
 


class Tokenizer
{
  std::string const& source;
  size_t position;

  bool check() const;
  char peek() const;
  bool match(std::string const&) const;
  void next(int n = 1);
  void pass_space();

public:
  explicit Tokenizer(std::string const& src);

  std::vector<Token> Tokenize();


};

class ParserCore
{
  std::vector<Token> tokens;
  size_t index;
  
  Token& get_tok();

  bool check();
  bool match(std::string const&);
  bool consume(std::string const&);
  void expect(std::string const&);
  void next();

public:

  void Initialize(std::vector<Token>&&);

  AST* Primary();
  AST* Mul();
  AST* Add();
  AST* Expr();

  AST_If* Parse_if();


  AST_Block* Parse();


};

class Program
{
  std::vector<Object> variables;
  std::string source;

  Tokenizer *tokenizer;
  ParserCore *parser;

public:

  Program();

  void OpenFile(std::string const& path);

  void Tokenize();
  void Parse();

  Object Run() const;

  [[noreturn]]
  static void Error(Token const& tok, std::string const& msg);



};


