#pragma once

#include <string>
#include <vector>

#include <KAI/Core/Config/Base.h>

KAI_BEGIN

///
/// I've spent far too much time wondering if:
///
/// > typedef char byte
///
/// is rational.
///
/// My current conclusion: A vector<char> is a lowest-common denominator across machines.
/// it would be *worse* to make it signed or unsigned or of a given bit-length.
///
/// As for endianess of binary represenations of multi-byte numbers across different
/// platforms: not my problem at this level of the KAI system.
///
///{@
typedef char byte;
std::vector<byte> ReadBinaryFile(const char *fileName);
bool WriteBinaryFile(const void *contents, const size_t len, const char *fileName);
bool WriteBinaryFile(std::vector<byte> const &, const char *fileName);
////@}

///
/// There is no support for wide-strings or UTF-8 anywhere in KAI.
///
/// Currently it's all ASCII. And get off my lawn.
///
/// \return Contents of the file. If the file can't be read for whatever reason, returns an empty String.
///
String ReadTextFile(const char *fileName);

///
/// Create or over-write a text file with given \param contents.
///
/// No current support for UTF-8. It's ASCII all the way down.
///
/// \returns true iff everything worked.
///
bool WriteTextFile(const char *filename, const char *contents);

KAI_END
