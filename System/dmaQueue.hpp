#pragma once

#include <cstdint>
#include <array>
#include <queue>

#include "thread.hpp"
#include "dmaCallbacks.hpp"

class DmaQueue : public cpp_freertos::Thread, public DmaCallbacks
{
public:	
    struct DmaSession
    { 
        std::uint8_t * ptr; 
        std::uint16_t size;
        DmaCallbacks & dmaCallbacks; // todo think about this
    };

    virtual bool transmitDma(std::uint8_t *pData, std::uint16_t size, DmaCallbacks &dmaCallbacks) = 0;
    virtual bool receiveDma(std::uint8_t *pData, std::uint16_t size, DmaCallbacks &dmaCallbacks) = 0;

    bool txPush(const std::uint8_t * ptr, std::uint16_t size);

protected:
    DmaQueue(uint32_t priority);
    ~DmaQueue();

private:	
    bool txNext();
    bool txHandle();

    virtual void Run() override; // task code

    void dmaTxCpltCallback() override;
    // void dmaTxHalfCpltCallback() override;
    // void dmaRxCpltCallback() override;
    // void dmaRxHalfCpltCallback() override;
    // void dmaErrorCallback() override;
    // void dmaAbortCpltCallback() override;
    // void dmaAbortTransmitCpltCallback() override;
    // void dmaAbortReceiveCpltCallback() override;

    std::deque<DmaSession> txSessionQueue;

    int txCpltCount;
};
