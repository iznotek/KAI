#pragma once

#include <KAI/Core/Config/Base.h>
#include <KAI/Core/Handle.h>
#include <KAI/Core/Constness.h>

KAI_BEGIN

/// Used to make a new Object
struct ObjectConstructParams
{
	const ClassBase *class_base;
	Registry *registry;
	Handle handle;
	Constness constness;

	ObjectConstructParams() : class_base(0), registry(0) { }
	ObjectConstructParams(Registry *, const ClassBase *, Handle, Constness = Constness::Mutable);
	ObjectConstructParams(const Object &, Constness);
	ObjectConstructParams(const StorageBase *);
	ObjectConstructParams(StorageBase *);
};

KAI_END
