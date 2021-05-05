#include "main.h"

bool AST::Expr::operator == (AST::Expr* ast) const
{
  if( !ast )
    return false;

  if( ast->type != type )
    return false;

  switch( type )
  {
  case Immidiate:
    return token->obj.equal(ast->token->obj);

  case Variable:
    return varIndex == ast->varIndex;

  case Callfunc:
  {
    if( token->str != ast->token->str )
      return false;

    if( ((AST::Callfunc*)this)->args.size() != ((AST::Callfunc*)ast)->args.size() )
      return false;

    for( size_t i = 0; i < ((AST::Callfunc*)this)->args.size(); i++ )
      if( ((AST::Callfunc*)this)->args[i] != ((AST::Callfunc*)ast)->args[i] )
        return false;

    return true;
  }

  case Array:
  {
    if( ((AST::Array*)this)->elems.size() != ((AST::Array*)ast)->elems.size() )
      return false;

    for( size_t i = 0; i < ((AST::Array*)this)->args.size(); i++ )
      if( ((AST::Array*)this)->elems[i] != ((AST::Array*)ast)->elems[i] )
        return false;

    return true;
  }

  default:
    return left == ast->left && right == ast->right;
  }

  return false;
}