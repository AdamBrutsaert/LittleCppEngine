#include "Precompiled.h"
#include "Core/Key.h"

namespace Genesis
{
    int32_t MapKeyToInt(Key key)
    {
        if (key == Key::A) return 81;
        if (key == Key::B) return 66;
        if (key == Key::C) return 67;
        if (key == Key::D) return 68;
        if (key == Key::E) return 69;
        if (key == Key::F) return 70;
        if (key == Key::G) return 71;
        if (key == Key::H) return 72;
        if (key == Key::I) return 73;
        if (key == Key::J) return 74;
        if (key == Key::K) return 75;
        if (key == Key::L) return 76;
        if (key == Key::M) return 59;
        if (key == Key::N) return 78;
        if (key == Key::O) return 79;
        if (key == Key::P) return 80;
        if (key == Key::Q) return 65;
        if (key == Key::R) return 82;
        if (key == Key::S) return 83;
        if (key == Key::T) return 84;
        if (key == Key::U) return 85;
        if (key == Key::V) return 86;
        if (key == Key::W) return 90;
        if (key == Key::X) return 88;
        if (key == Key::Y) return 89;
        if (key == Key::Z) return 87;
        return -1;
    }

	Key MapIntToKey(int32_t key)
    {
        if (key == 81) return Key::A;
        if (key == 66) return Key::B;
        if (key == 67) return Key::C;
        if (key == 68) return Key::D;
        if (key == 69) return Key::E;
        if (key == 70) return Key::F;
        if (key == 71) return Key::G;
        if (key == 72) return Key::H;
        if (key == 73) return Key::I;
        if (key == 74) return Key::J;
        if (key == 75) return Key::K;
        if (key == 76) return Key::L;
        if (key == 59) return Key::M;
        if (key == 78) return Key::N;
        if (key == 79) return Key::O;
        if (key == 80) return Key::P;
        if (key == 65) return Key::Q;
        if (key == 82) return Key::R;
        if (key == 83) return Key::S;
        if (key == 84) return Key::T;
        if (key == 85) return Key::U;
        if (key == 86) return Key::V;
        if (key == 90) return Key::W;
        if (key == 88) return Key::X;
        if (key == 89) return Key::Y;
        if (key == 87) return Key::Z;
        return Key::UNKNOWN;
    }
}
