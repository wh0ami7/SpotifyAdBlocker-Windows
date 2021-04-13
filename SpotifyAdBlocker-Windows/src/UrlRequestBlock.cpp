#include "pch.h"
#include "redirection.h"
#include "UrlRequestBlock.h"
#include "stubs.h"
#include <regex>
#include <vector>
#include <stdexcept>
#include <ranges>
#include <string_view>

#ifdef _DEBUG
#include <cstdio>
#endif


template<typename T>
void InitAddress(T& fncAddr, HMODULE hModule, LPCSTR fncName)
{
	fncAddr = (T)GetProcAddress(hModule, fncName);
	if (fncAddr == NULL)
	{
		throw std::runtime_error("Invalid Address");
	}
}

extern "C" {

	PCEF_URLREQUEST_CREATE_T 			original_cef_url_request_create = NULL;
	PCEF_STRING_USERFREE_UTF16_FREE_T 	original_cef_string_user_free_utf_free = NULL;

	
	static std::vector<std::wstring> black_list = {
		L"https://spclient.wg.spotify.com/ads/", // ads
		L"https://spclient.wg.spotify.com/ad-logic/", // ads
		L"https://spclient.wg.spotify.com/gabo-receiver-service/", // tracking
	};

	bool IsBlackListed(const std::wstring_view& url)
	{
		auto is_prefix = [&](const std::wstring_view& pattern) {
			auto res = std::ranges::mismatch(pattern, url);
			return res.in1 == pattern.end();
		};
		return !std::ranges::empty(black_list | std::views::filter(is_prefix));
	}


	void Init(HMODULE hModule)
	{
		InitAddress(original_cef_url_request_create, hModule, "cef_urlrequest_create");
		InitAddress(original_cef_string_user_free_utf_free, hModule, "cef_string_userfree_utf16_free");
	}

	cef_urlrequest_t *
	_cef_urlrequest_create(
	cef_request_t * request,
	cef_urlrequest_client_t * client,
	cef_request_context_t * request_context)
	{
		cef_string_userfree_utf16_t url_utf16 = request->get_url(request);
		auto url = std::wstring(url_utf16->length, '0');
		for (unsigned int i = 0; i < url_utf16->length; i++) url[i] = *(url_utf16->str + i);
		original_cef_string_user_free_utf_free(url_utf16);	

		if (IsBlackListed(url)){

	#ifdef _DEBUG
			FILE* file;
			fopen_s(&file, "log.txt", "a");
			if (file)
			{
				fseek(file, 0, SEEK_END);
				fwprintf(file, (L"[-] cef_urlrequest_create : " + url + L"\n").c_str());
				fclose(file);
			}
	#endif

			return NULL;
		}

	#ifdef _DEBUG
		FILE* file;
		fopen_s(&file, "log.txt", "a");
		if (file)
		{
			fseek(file, 0, SEEK_END);
			fwprintf(file, (L"[+] cef_urlrequest_create : " + url+ L"\n").c_str());
			fclose(file);
		}
	#endif

		return original_cef_url_request_create(request, client, request_context);
	}
}
