#ifndef BEECOM_H_
#define BEECOM_H_

#include <cstdint>
#include <cassert>
#include <cstddef>

#define CRC16AUGCCITT_LOOKUP                                                                                                                            \
    0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U, 0x8108U, 0x9129U, 0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,     \
        0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52B5U, 0x4294U, 0x72F7U, 0x62D6U, 0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU, \
        0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U, 0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU, \
        0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U, 0xB75BU, 0xA77AU, 0x9719U, 0x8738U, 0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU, \
        0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U, 0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU, \
        0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U, 0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU, \
        0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U, 0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U, 0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U, \
        0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U, 0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U, \
        0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU, 0x1080U, 0x00A1U, 0x30C2U, 0x20E3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U, \
        0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU, 0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U, \
        0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU, 0x34E2U, 0x24C3U, 0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U, \
        0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U, 0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU, 0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U, \
        0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU, 0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U, \
        0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU, 0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U, 0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U, \
        0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U, 0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U, \
        0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U, 0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U

namespace beecom
{
    class ICRCStrategy
    {
    public:
        virtual ~ICRCStrategy() = default;
        virtual uint16_t calculate(const uint8_t *data, size_t length) const = 0;
        virtual uint16_t updateCRC(uint16_t currentCRC, uint8_t dataByte) const = 0;
    };

    class CRC16AUGCCITTStrategy : public ICRCStrategy
    {
    public:
        static constexpr uint16_t initialCRCValue = 0x1D0F;

    private:
        static constexpr uint16_t lookupTable[256] = {CRC16AUGCCITT_LOOKUP};

    public:
        uint16_t calculate(const uint8_t *data, size_t length) const override
        {
            uint16_t crc = initialCRCValue;
            for (size_t i = 0; i < length; ++i)
            {
                crc = updateCRC(crc, data[i]);
            }
            return crc;
        }

        uint16_t updateCRC(uint16_t currentCRC, uint8_t dataByte) const override
        {
            return (currentCRC << 8) ^ lookupTable[((currentCRC >> 8) ^ dataByte) & 0xFF];
        }
    };

    constexpr uint8_t MAX_PAYLOAD_SIZE = 200U;
    constexpr uint8_t SOP_VALUE = 0xA5U;

    struct PacketHeader
    {
        uint8_t sop = SOP_VALUE;
        uint8_t type = 0U;
        uint8_t length = 0U;
        uint16_t crc = 0U;
    };

    struct Packet
    {
        PacketHeader header;
        uint8_t payload[MAX_PAYLOAD_SIZE] = {};

        void reset()
        {
            header = PacketHeader();
        }
    };

    enum class PacketState
    {
        EMPTY,
        SOP_RECEIVED,
        TYPE_RECEIVED,
        LEN_RECEIVED,
        CRC_LSB_RECEIVED,
        CRC_MSB_RECEIVED,
        GETTING_PAYLOAD,
        WHOLE_PACKET_RECEIVED
    };

    using PacketHandler = void (*)(const Packet &packet, bool crcValid);

    class Receiver
    {
    public:
        Receiver(PacketHandler callback, ICRCStrategy *crcStrategy = nullptr)
            : packetHandler(callback), crcStrategy(crcStrategy ? crcStrategy : &defaultCRCStrategy) {}

        void Deserialize(const uint8_t *data, size_t size);

    private:
        Packet packet;
        size_t payloadCounter = 0;
        PacketState state = PacketState::EMPTY;
        PacketHandler packetHandler;
        ICRCStrategy *crcStrategy;
        static CRC16AUGCCITTStrategy defaultCRCStrategy;

        void handleStateEmpty(uint8_t byte);
        void handleStateGotSOP(uint8_t byte);
        void handleStateGotType(uint8_t byte);
        void handleStateGotLength(uint8_t byte);
        void handleStateGotCRCLo(uint8_t byte);
        void handleStateGotCRCHi(uint8_t byte);
        void handleStateGettingPayload(uint8_t byte);
        void processCompletePacket();
        bool validateCRC() const;
        void resetState();
        void updateHeaderCRC(uint8_t byte);
        void transitionState(PacketState newState);
    };

} // namespace beecom

#endif /* BEECOM_H_ */
