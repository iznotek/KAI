#pragma once

#include <boost/filesystem.hpp>

#include <KAI/Stream.h>

KAI_BEGIN

StringStream& operator<<(StringStream &, boost::filesystem::path const &);
StringStream& operator>>(StringStream &, boost::filesystem::path &);
BinaryStream& operator<<(BinaryStream &, boost::filesystem::path const &);
BinaryStream& operator>>(BinaryStream &, boost::filesystem::path &);

KAI_TRAITS(
	boost::filesystem::path,
	Number::FilesystemPath,
	Properties::Streaming | Properties::Relational
)

KAI_END
