#pragma once

class CBattleFlag
{
public:
    CBattleFlag(void);
    ~CBattleFlag(void);

    void RegisterTexture();
    void UnRegisterTexture();
    void Render(int x, int y, short shFlag);

private:
    int m_nGuardTexture;
    int m_nAttackTexture;
};
