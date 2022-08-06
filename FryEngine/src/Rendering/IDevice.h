#pragma once
#include <cinttypes>
namespace FryEngine
{
    class IDevice
    {
    public:
        virtual void ClearView(uint8_t r, uint8_t g, uint8_t b, uint8_t a) = 0;
        virtual void Present() = 0;
    private:
    };
} // FryEngine