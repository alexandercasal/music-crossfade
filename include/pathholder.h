#ifndef _PATHHOLDER_H
#define _PATHHOLDER_H
#include <map>
#include <string>
#include <cassert>
#include <iostream>

/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* DESCRIPTION : Stores and links a file path to an ID.
* METHODS     : PathHolder     - Creates an empty Path Holder
*               pairToPath     - Pairs an ID with a file path
*               getPath        - Returns file path from its ID
*               releasePath    - Removes the pair from the Path Holder
*               clear          - Removes all pairs from the Path Holder
*               isEmpty        - Are there any pairs in the Path Holder?
*--------------------------------------------------------*/
template <typename Identifier>
class PathHolder
{
public:
	PathHolder();
	void pairToPath(Identifier pathID, const std::string & filePath);
	const std::string & getPath(Identifier pathID) const;
	void releasePath(Identifier pathID);
	void clear();
	bool isEmpty() const;

private:
	std::map<Identifier, std::string> paths;
};

#include "pathholder.inl"
#endif // end _PATHHOLDER_H