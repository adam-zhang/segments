int GetEncodeerClsid(const TCHAR* format, CLSID *pClsid)
{
	UINT num = 0, size = 0;
	int ret = -1;
	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return ret;
	Gdiplus::ImageCodecInfo* pImageCodecInfo = (Gdiplus::ImageCodecInfo*)malloc(size);
	if (pImageCodecInfo == nullptr)
		return ret;
	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);
	for (UINT i = 0; i < num; ++i)
	{
		if (_tcscmp(pImageCodecInfo[i].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[i].Clsid;
			ret = 1;
			break;
		}
	}
	free(pImageCodecInfo);
	return ret;
}

