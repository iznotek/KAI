#pragma once

#include <KAI/Language/Common/LexerCommon.h>
#include "Tau/TauToken.h"

TAU_BEGIN

struct TauLexer : LexerCommon<TauTokenEnumType>
{
	typedef LexerCommon<TauTokenEnumType> Parent;
	typedef TokenBase<TauTokenEnumType> TokenNode;

	TauLexer(const char *text, Registry &r) : Parent(text, r) { }

	virtual void AddKeyWords();
	virtual bool NextToken();
	virtual void Terminate();
};

TAU_END

