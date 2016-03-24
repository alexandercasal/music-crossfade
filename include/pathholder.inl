/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* METHOD      : Constructor
* DESCRIPTION : Creates an empty Path Holder
*--------------------------------------------------------*/
template <typename Identifier>
PathHolder<Identifier>::PathHolder()
{
#ifdef _DEBUG
	std::cout << "Path Holder: Constructed\n";
#endif
}

/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* METHOD      : pairToPath
* DESCRIPTION : Pairs an ID with a file path
*--------------------------------------------------------*/
template <typename Identifier>
void PathHolder<Identifier>::pairToPath(Identifier pathID, const std::string & filePath)
{
	assert(filePath.size() > 0);
	auto inserted = paths.insert(std::make_pair(pathID, filePath));
	assert(inserted.second);

#ifdef _DEBUG
	std::cout << "Path Holder: Paired ID " << (int)pathID << " to \'" << filePath << "\'\n";
#endif
}

/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* METHOD      : getPath
* DESCRIPTION : Returns file path from its ID
*--------------------------------------------------------*/
template <typename Identifier>
const std::string & PathHolder<Identifier>::getPath(Identifier pathID) const
{
	auto found = paths.find(pathID);
	assert(found != paths.end());

#ifdef _DEBUG
	std::cout << "Path Holder: Retrieving \'" << (*found).second << "\' at ID " << (int)pathID << std::endl;
#endif

	return (*found).second;
}

/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* METHOD      : releasePath
* DESCRIPTION : Removes the pair from the Path Holder
*--------------------------------------------------------*/
template <typename Identifier>
void PathHolder<Identifier>::releasePath(Identifier pathID)
{
	auto found = paths.find(pathID);
	assert(found != paths.end());

#ifdef _DEBUG
	std::cout << "Path Holder: Removed \'" << (*found).second << "\' at ID " << (int)pathID << std::endl;
#endif

	paths.erase(found);
}

/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* METHOD      : clear
* DESCRIPTION : Removes all pairs from the Path Holder
*--------------------------------------------------------*/
template <typename Identifier>
void PathHolder<Identifier>::clear()
{
	paths.clear();

#ifdef _DEBUG
	std::cout << "Path Holder: Cleared all \n";
#endif
}

/*-------------------------------------------------------
* CLASS       : PATHHOLDER
* METHOD      : isEmpty
* DESCRIPTION : Are there any pairs in the Path Holder?
*--------------------------------------------------------*/
template <typename Identifier>
bool PathHolder<Identifier>::isEmpty() const
{
	return paths.empty();
}