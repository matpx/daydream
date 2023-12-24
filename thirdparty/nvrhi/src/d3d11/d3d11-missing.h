#pragma once

#define D3D_SET_OBJECT_NAME_N_A(pObject, Chars, pName) (pObject)->SetPrivateData(WKPDID_D3DDebugObjectName, Chars, pName)

typedef
enum D3D11_FILTER_REDUCTION_TYPE
{
    D3D11_FILTER_REDUCTION_TYPE_STANDARD	= 0,
    D3D11_FILTER_REDUCTION_TYPE_COMPARISON	= 1,
    D3D11_FILTER_REDUCTION_TYPE_MINIMUM	= 2,
    D3D11_FILTER_REDUCTION_TYPE_MAXIMUM	= 3
} 	D3D11_FILTER_REDUCTION_TYPE;