string applicationPath()
{
	vector<char> buffer(MAX_PATH);
	GetModuleFileNameA(NULL, &buffer[0], MAX_PATH);
	string path(&buffer[0]);
	auto index = path.rfind('\\');
	return path.substr(0, index);
}

