#pragma once

#include "adcIF.hpp"
#include <cstdint>
#include <array>

class Adc2 : public AdcIF
{
public:
    static Adc2 &getInstance();

    virtual bool init() override;
    virtual bool start() override;
    virtual std::uint32_t getChannelsTotal() override;
    virtual std::uint32_t getBitDepth() override;
    virtual std::uint32_t getFrameBitWidth() override;
    virtual bool stop() override;
    virtual bool deinit() override;

    struct Dma
    {
        bool init();
        void handle();
        void convCpltCallback();
        void convHalfCpltCallback();
        bool deinit();
    } dma;

protected:
    virtual bool getValueUnsafe(std::size_t channelNo, std::uint32_t &valueOut) override;

private:
    Adc2();

    bool configChannels();
    bool autoCalibrate();

    ~Adc2();

    void operator=(Adc2 const &) = delete;
    Adc2(Adc2 const &) = delete;
};
