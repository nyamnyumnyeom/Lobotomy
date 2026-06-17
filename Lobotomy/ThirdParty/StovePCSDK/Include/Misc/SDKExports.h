#pragma once

/*!
    * @file     SDKExports.h
    * \korean
    * @brief    DLL Export의 define 정의입니다.
    * \endkorean
    * \english
    * @brief    Define definition of DLL Export.
    * \endenglish
*/

#ifdef DLL_EXPORTS
#define SDK_EXPORTS  __declspec(dllexport)   
#else
#define SDK_EXPORTS  __declspec(dllimport)   
#endif