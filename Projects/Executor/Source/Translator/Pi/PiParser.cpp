#include "KAI/ExecutorPCH.h"
#include "KAI/Translator/Structure.h"
#include "KAI/Translator/Pi/PiToken.h"
#include "KAI/Translator/Pi/PiParser.h"

#include <memory>
#include <iostream>
#include <algorithm>
#include <strstream>
#include <stdarg.h>

KAI_BEGIN

void PiParser::Process(Structure st)
{
	KAI_UNUSED_1(st);
	while (!Failed && NextSingle(root))
		;
}

bool PiParser::NextSingle(AstNodePtr root)
{
	if (current == tokens.size() - 1)
		return false;

	auto tok = Current();
	switch (tok.type)
	{
	case PiTokens::CloseSquareBracket:
	case PiTokens::CloseBrace:
		Fail(Lexer::CreateErrorMessage(Current(), "%s", "Unopened compound"));
		return false;

	case PiTokens::OpenSquareBracket:
		Consume();
		return ParseArray(root);

	case PiTokens::OpenBrace:
		Consume();
		return ParseContinuation(root);

	default:
		root->Add(NewNode(Consume()));
		return true;
	}
}

//bool PiParser::Compound()
//{
//	switch (Peek().type)
//	{
//	case PiTokens::OpenBrace:
//		return ParseContinuation();
//		break;
//
//	case PiTokens::OpenSquareBracket:
//		return ParseArray();
//		break;
//	}
//
//	return false;
//}
//
bool PiParser::ParseArray(AstNodePtr root)
{
	auto node = NewNode(PiAstNodes::Array);
	while (Current().type != PiTokens::CloseSquareBracket)
	{
		if (!NextSingle(node))
		{
			Fail("Malformed Array");
			return false;
		}
	}
	Consume();

	root->Add(node);
	
	return true;
}

bool PiParser::ParseContinuation(AstNodePtr root)
{
	return false;
}


KAI_END