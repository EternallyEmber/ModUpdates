namespace Sonic::Player
{
    inline BB_FUNCTION_PTR(const Hedgehog::Base::CSharedString&, __stdcall,
        fpCPlayerContextGetCurrentAnimationName, 0xE72CB0, CPlayerContext* This);

    inline const Hedgehog::Base::CSharedString& CPlayerContext::GetCurrentAnimationName()
    {
        return fpCPlayerContextGetCurrentAnimationName(this);
    }

    inline uint32_t pCPlayerContextChangeState = 0xE4FF30;

    inline Hedgehog::Universe::TStateMachine<CPlayerContext>::TState* fCPlayerContextChangeState(
        CPlayerContext* This, const Hedgehog::Base::CSharedString* in_pType)
    {
        Hedgehog::Universe::TStateMachine<CPlayerContext>::TState* pResult;

        __asm
        {
            mov eax, in_pType
            mov ecx, This
            call[pCPlayerContextChangeState]
            mov pResult, eax
        }

        return pResult;
    }

    inline Hedgehog::Universe::TStateMachine<CPlayerContext>::TState* CPlayerContext::ChangeState(
        const Hedgehog::Base::CSharedString& in_rType)
    {
        return fCPlayerContextChangeState(this, &in_rType);
    }

    inline Hedgehog::Universe::TStateMachine<CPlayerContext>::TState* CPlayerContext::ChangeState(
        const EPlayerSpeedState in_PlayerSpeedState)
    {
        return ChangeState(ConvertPlayerSpeedStateToString(in_PlayerSpeedState));
    }

    inline int pCPlayerContextChangePosture = 0x00E78D30;
    static __declspec(noinline) __declspec(naked) void fCPlayerContextChangePosture()
    {
	    __asm
        {
            mov eax, edx
            jmp [pCPlayerContextChangePosture]
        }
    }

    inline BB_FUNCTION_PTR(inline Hedgehog::Universe::TStateMachine<CPlayerContext>::TState*, __fastcall, fpCPlayerContextChangePosture, fCPlayerContextChangePosture,
        CPlayer* This, const Hedgehog::Base::CSharedString& in_rType, bool in_Unknown);

    inline Hedgehog::Universe::TStateMachine<CPlayerContext>::TState* CPlayerContext::ChangePosture(
        const Hedgehog::Base::CSharedString& in_rType, bool in_Unknown)
    {
        return fpCPlayerContextChangePosture(m_pPlayer, in_rType, in_Unknown);
    }

    template <typename T>
    T* CPlayerContext::ChangeState()
    {
        return static_cast<T*>(ChangeState(T::ms_pStateName));
    }
}