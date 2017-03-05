#pragma once

#include <KAI/Core/Value.h>
#include <KAI/Core/Process.h>
#include <KAI/Core/Registry.h>

KAI_BEGIN

///
/// Badly named and or scoped. This is just needed for Language systems.
///
struct ProcessCommon : Process
{
	template <class T>
	Value<T> New()
	{
		return _reg->New<T>();
	}

	template <class T>
	Value<T> New(const T& val)
	{
		return _reg->New<T>(val);
	}

	ProcessCommon() { }
	ProcessCommon(Registry &r) : _reg(&r) { }

protected:
	Registry *_reg = 0;
};

KAI_END
