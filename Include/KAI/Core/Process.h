#pragma once

#include <KAI/Core/Config/Base.h>
#include <string>

KAI_BEGIN

///
/// Common to all processes. TODO: Rename to "Attempt" or something.
/// "Process" implies something over time, which this class doesn't need.
///
struct Process
{
	/// The debug trace level for this process.
	static int trace;

	mutable const bool Failed = false;
	mutable const std::string Error;

protected:
	bool Fail(const char *fmt, ...) const;
	bool Fail(const std::string &) const;
};

KAI_END
