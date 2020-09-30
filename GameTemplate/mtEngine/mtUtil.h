
#pragma once

#ifndef _MTUTIL_H_
#define _MTUTIL_H_

#include <string.h>

namespace mtEngine
{
	class CUtil {
	public:
		/*!
		 * @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
		 �p��
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
		* @brief	�����񂩂�32bit�̃n�b�V���l���쐬�B
		�n�b�V���l�@���@���������A������萔���̂ق�������
		���{��
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