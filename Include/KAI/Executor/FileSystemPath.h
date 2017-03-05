#pragma once

#include <boost/filesystem/path.hpp>
#include <KAI/Stream.h>

KAI_BEGIN

typedef ::boost::filesystem::path FileSystemPath;

///@{ Good example of adapting an external class to be a KAI system type
StringStream& operator<<(StringStream &, FileSystemPath const &);
StringStream& operator>>(StringStream &, FileSystemPath &);
BinaryStream& operator<<(BinaryStream &, FileSystemPath const &);
BinaryStream& operator>>(BinaryStream &, FileSystemPath &);

KAI_TRAITS(
	FileSystemPath,
	Number::FilesystemPath,
	Properties::Streaming | Properties::Relational
)
///@}

KAI_END
