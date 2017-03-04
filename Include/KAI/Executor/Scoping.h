#pragma once

KAI_BEGIN

///
/// Used to manage name resolution for fetching and storing values.
///
/// Deals wth local scope in context of a Context within a Continuation,
/// as well as searching up the Contexts as needed, as well as searching
/// the Tree if relative or absolute pathnames are provided.
///
/// ***Note that this implies that the location of scripts on disk controls
/// their lookup results***.
///
struct Scoping
{
	/// The 'global scope' for names. This is analogous to a filesystem.
	Pointer<Tree> Tree;
	
	/// A virtual machine state.
	Pointer<Executor> Executor;

	///{@ Store a new value.
	/// If the referenced object already exists, this becomes a type-safe
	/// assignment operation.
	Object Set(Object const &ident, Object const &value) const;
	Object Set(Label const &, Object const &) const;
	Object Set(Pathname const &, Object const &) const;
	///@}

	///{@ Assign a value to an existing object. This is type-safe.
	Object Assign(Object const &ident, Object const &value) const;
	Object Assign(Label const &, Object const &) const;
	Object Assign(Pathname const &, Object const &) const;
	///@}

	///@{ Get the value associated with an identifier
	Object Get(Object const &ident) const;
	Object Get(Label const &) const;
	Object Get(Pathname const &) const;
	///@}
};

KAI_END
