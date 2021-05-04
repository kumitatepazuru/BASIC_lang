#include "main.h"

Object AST_Runner::Run_Expr(AST::Expr* ast)
{
  if( !ast )
    return { };

  switch( ast->type )
  {
  case AST::Expr::Immidiate:
    return ast->token->obj;

  case AST::Expr::Variable:
  {
    auto& var = Program::instance->variables[ast->varIndex];
    var.var_ptr = &var;
    return var;
  }

  default:
  {
    auto left = Run_Expr(ast->left);
    auto right = Run_Expr(ast->right);

    switch( ast->type )
    {
    case AST::Expr::Add:
      left.v_int += right.v_int;
      break;

    case AST::Expr::Sub:
      left.v_int -= right.v_int;
      break;

    case AST::Expr::Mul:
      left.v_int *= right.v_int;
      break;

    case AST::Expr::Div:
      left.v_int /= right.v_int;
      break;

    }

    return left;
  }
  }

  return { };
}

void Instruction(AST::Instruction* ast)
{
  auto const& name = ast->name;
  std::vector<Object> args;

  for( auto&& i : ast->args )
    args.emplace_back(AST_Runner::Run_Expr(i));

  if( name == "print" )
  {
    for( auto&& i : args )
      std::cout << i.to_string();

    std::cout << '\n';
    return;
  }

  Program::Error(*ast->token, "undefined instruction");
}

Object AST_Runner::Run_Stmt(AST::Stmt* ast)
{
  if( !ast )
    return { };

  switch( ast->type )
  {
  case AST::Stmt::Block:
  {
    Object obj;

    alart;

    for( auto&& i : ((AST::Block*)ast)->list )
      obj = Run_Stmt(i);

    return obj;
  }

  case AST::Stmt::Assign:
  {
    auto var = Run_Expr(((AST::Assign*)ast)->var);
    auto value = Run_Expr(((AST::Assign*)ast)->value);

    alart;
    return *(var.var_ptr) = value;
  }

  case AST::Stmt::Instruction:
  {
    Instruction(reinterpret_cast<AST::Instruction*>(ast));
    break;
  }

  case AST::Stmt::If:
  {
    for( auto&& pair : ((AST::If*)ast)->pairs )
    {
      alart;
      auto cond = Run_Expr(std::get<0>(pair));

      if( cond.eval() )
      {
        return Run_Stmt(std::get<1>(pair));
      }
    }

    break;
  }

  case AST::Stmt::For:
    break;

  case AST::Stmt::While:
    break;

  default:
    return Run_Expr(ast->expr);


  }

  return { };
}



