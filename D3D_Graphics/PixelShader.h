#pragma once
#include "Shader.h"

class PixelShader :
    public Shader
{
public:
    ComPtr<ID3D11PixelShader> m_pPixelShader;
public:
    virtual bool CompileShader(wstring filename=L"PixelShader");
    virtual bool SetShader(wstring filename);
};

