
#pragma once

#ifndef _MTUTIL_H_
#define _MTUTIL_H_

#include <string.h>

namespace mtEngine
{
	class CUtil {
	public:
		/*!
		 * @brief	文字列から32bitのハッシュ値を作成。
		 英字
		 */
		static int MakeHash(const char* string)
		{
			if (string == nullptr) {
				return 0;
			}
			int hash = 0;
			int l = (int)strlen(string);
			for (int i = 0; i < l; i++) {
				hash = hash * 37 + string[i];
			}
			return hash;
		}

		/*!
		* @brief	文字列から32bitのハッシュ値を作成。
		ハッシュ値　＝　メモリ小、文字より数字のほうが早い
		日本語
		*/
		static int MakeHash(const wchar_t* string)
		{
			if (string == nullptr) {
				return 0;
			}
			int hash = 0;
			int l = (int)wcslen(string);
			for (int i = 0; i < l; i++) {
				hash = hash * 37 + string[i];
			}
			return hash;
		}
	};


}

#endif // _TKUTIL_H_