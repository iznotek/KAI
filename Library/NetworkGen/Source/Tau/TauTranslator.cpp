#include <boost/lexical_cast.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include "KAI/Core/BuiltinTypes.h"
#include "KAI/Executor/Executor.h"
#include "Tau/Tau.h"
#include "Tau/TauTranslator.h"


TAU_BEGIN

#pragma warning (disable:4063)

//void TauTranslator::TranslateToken(AstNodePtr node)
//{
//	switch (node->GetToken().type)
//	{
//	case TokenEnum::While:
//		TranslateWhile(node);
//		return;
//
//	case TokenEnum::DivAssign:
//		TranslateBinaryOp(node, Operation::DivEquals);
//		return;
//
//	case TokenEnum::MulAssign:
//		TranslateBinaryOp(node, Operation::MulEquals);
//		return;
//
//	case TokenEnum::MinusAssign:
//		TranslateBinaryOp(node, Operation::MinusEquals);
//		return;
//
//	case TokenEnum::PlusAssign:
//		TranslateBinaryOp(node, Operation::PlusEquals);
//		return;
//
//	case TokenEnum::Assign:
//		TranslateBinaryOp(node, Operation::Store);
//		return;
//
//	case TokenEnum::Lookup:
//		AppendOp(Operation::Lookup);
//		return;
//
//	case TokenEnum::Self:
//		AppendOp(Operation::This);
//		return;
//
//	case TokenEnum::NotEquiv:
//		TranslateBinaryOp(node, Operation::NotEquiv);
//		return;
//
//	case TokenEnum::Equiv:
//		TranslateBinaryOp(node, Operation::Equiv);
//		return;
//
//	case TokenEnum::Less:
//		TranslateBinaryOp(node, Operation::Less);
//		return;
//
//	case TokenEnum::Greater:
//		TranslateBinaryOp(node, Operation::Greater);
//		return;
//
//	case TokenEnum::GreaterEquiv:
//		TranslateBinaryOp(node, Operation::GreaterOrEquiv);
//		return;
//
//	case TokenEnum::LessEquiv:
//		TranslateBinaryOp(node, Operation::LessOrEquiv);
//		return;
//
//	case TokenEnum::Minus:
//		TranslateBinaryOp(node, Operation::Minus);
//		return;
//
//	case TokenEnum::Plus:
//		TranslateBinaryOp(node, Operation::Plus);
//		return;
//
//	case TokenEnum::Mul:
//		TranslateBinaryOp(node, Operation::Multiply);
//		return;
//
//	case TokenEnum::Divide:
//		TranslateBinaryOp(node, Operation::Divide);
//		return;
//
//	case TokenEnum::Or:
//		TranslateBinaryOp(node, Operation::LogicalOr);
//		return;
//
//	case TokenEnum::And:
//		TranslateBinaryOp(node, Operation::LogicalAnd);
//		return;
//
//	case TokenEnum::Int:
//		Append(_reg.New<int>(boost::lexical_cast<int>(node->GetTokenText())));
//		return;
//
//	case TokenEnum::Float:
//		Append(_reg.New<float>(boost::lexical_cast<float>(node->GetTokenText())));
//		return;
//
//	case TokenEnum::String:
//		Append(_reg.New<String>(node->Text()));
//		return;
//
//	case TokenEnum::Ident:
//		Append(_reg.New<Label>(Label(node->Text())));
//		return;
//
//	case TokenEnum::Yield:
//		//for (auto ch : node->Children)
//		//	Translate(ch);
//		//AppendNewOp(Operation::PushContext);
//		TAU_NOT_IMPLEMENTED();
//		return;
//
//	case TokenEnum::Return:
//		for (auto ch : node->GetChildren())
//			TranslateNode(ch);
//		AppendOp(Operation::Return);
//		return;
//	}
//
//	Fail("Unsupported node %s", node->ToString().c_str());
//	TAU_NOT_IMPLEMENTED();
//}
//
//void TauTranslator::TranslateBinaryOp(AstNodePtr node, Operation::Type op)
//{
//	TranslateNode(node->GetChild(0));
//	TranslateNode(node->GetChild(1));
//
//	AppendNew<Operation>(Operation(op));
//}
//
//void TauTranslator::TranslateNode(AstNodePtr node)
//{
//	if (!node)
//	{
//		Failed = true;
//		return;
//	}
//
//	switch (node->GetType())
//	{
//	case AstEnum::IndexOp:
//		TranslateBinaryOp(node, Operation::Index);
//		return;
//
//	case AstEnum::GetMember:
//		TranslateBinaryOp(node, Operation::GetProperty);
//		return;
//
//	case AstEnum::TokenType:
//		TranslateToken(node);
//		return;
//
//	case AstEnum::Assignment:
//		// like a binary op, but argument order is reversed
//		TranslateNode(node->GetChild(1));
//		TranslateNode(node->GetChild(0));
//		AppendNew<Operation>(Operation(Operation::Store));
//		return;
//
//	case AstEnum::Call:
//		TranslateCall(node);
//		return;
//
//	case AstEnum::Conditional:
//		TranslateIf(node);
//		return;
//
//	case AstEnum::Block:
//		PushNew();
//		for (auto st : node->GetChildren())
//			TranslateNode(st);
//		Append(Pop());
//		return;
//
//	case AstEnum::List:
//		for (auto ch : boost::adaptors::reverse(node->GetChildren()))
//			TranslateNode(ch);
//		AppendNew<int>(node->GetChildren().size());
//		//AppendNewOp(Operation::ToArray);
//		TAU_NOT_IMPLEMENTED();
//		return;
//
//	case AstEnum::For:
//		TranslateFor(node);
//		return;
//
//	case AstEnum::Function:
//		TranslateFunction(node);
//		return;
//
//	case AstEnum::Program:
//		for (auto e : node->GetChildren())
//			TranslateNode(e);
//		return;
//	}
//
//	Fail("Unsupported node %s", node->ToString().c_str());
//	TAU_NOT_IMPLEMENTED();
//}
//
//void TauTranslator::TranslateBlock(AstNodePtr node)
//{
//	for (auto st : node->GetChildren())
//		TranslateNode(st);
//}
//
//void TauTranslator::TranslateFunction(AstNodePtr node)
//{
//	// child 0: ident
//	// child 1: args
//	// child 2: block
//	AstNode::ChildrenType const &ch = node->GetChildren();
//
//	// write the body
//	PushNew();
//	for (auto b : ch[2]->GetChildren())
//		TranslateNode(b);
//
//	// add the args
//	auto cont = Pop();
//	for (auto a : ch[1]->GetChildren())
//		cont->AddArg(Label(a->GetTokenText()));
//
//	// write the name and store
//	Append(cont);
//	AppendNew(Label(ch[0]->Text()));
//	AppendOp(Operation::Store);
//}
//
//void TauTranslator::TranslateCall(AstNodePtr node)
//{
//	typename AstNode::ChildrenType const &children = node->GetChildren();
//	for (auto a : children[1]->GetChildren())
//		TranslateNode(a);
//
//	TranslateNode(children[0]);
//	if (children.size() > 2 && children[2]->GetToken().type == TokenEnum::Replace)
//		AppendNew(Operation(Operation::Replace));
//	else
//		AppendNew(Operation(Operation::Suspend));
//}
//
//void TauTranslator::TranslateIf(AstNodePtr node)
//{
//	typename AstNode::ChildrenType const &ch = node->GetChildren();
//	bool hasElse = ch.size() > 2;
//	TranslateNode(ch[0]);
//	if (hasElse)
//		TranslateNode(ch[2]);
//
//	TranslateNode(ch[1]);
//	AppendOp(hasElse ? Operation::IfThenSuspendElseSuspend : Operation::IfThenSuspend);
//}
//
//void TauTranslator::TranslateFor(AstNodePtr node)
//{
//	AppendOp(Operation::None);
//}
//
//void TauTranslator::TranslateWhile(AstNodePtr node)
//{
//	AppendOp(Operation::None);
//}

TAU_END
