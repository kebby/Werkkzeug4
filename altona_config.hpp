/****************************************************************************/
/***                                                                      ***/
/***   Altona main configuration file.                                    ***/
/***                                                                      ***/
/****************************************************************************/
/***                                                                      ***/
/***   Please rename this file to "altona_config.hpp" and edit it to      ***/
/***   reflect your needs.                                                ***/
/***                                                                      ***/
/****************************************************************************/
/***                                                                      ***/
/***   This file is compiled in every altona application                  ***/
/***   In addition to that, makeproject parses this file by hand on       ***/
/***   every invokation.                                                  ***/
/***                                                                      ***/
/****************************************************************************/

// operator new shenanigans (one should investigate this)
#pragma warning (disable: 4595)
#pragma warning (disable: 5043)

// GCed objects don't have delete
#pragma warning (disable: 4291)  

// macro redef in shader disasm (conflict between dxsdk and windows sdk)
#pragma warning (disable: 4005)

#define sCONFIG_CODEROOT L""

#define sCONFIG_SDK_DX9           1         // Microsoft DX9 sdk installed (required for input, sound, graphics)
#define sCONFIG_SDK_DX11          1
#define sCONFIG_SDK_CG            0


#define sCONFIG_GUID {0x74F17E89,{0x915F,0x4264,0xB67A},{0xBA,0xDF,0x00,0xD5,0x32,0x5A}}

#define sCONFIG_RENDER_DX9
