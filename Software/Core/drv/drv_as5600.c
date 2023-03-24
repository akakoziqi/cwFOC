#include "drv_as5600.h"
#include "drv_i2c.h"

#define AS5600_I2C_ADDR (0X36)
#define AS5600_REG_ZMCO (0X00)
#define AS5600_REG_ZPOS (0X01)
#define AS5600_REG_MPOS (0X03)
#define AS5600_REG_MANG (0X05)
#define AS5600_REG_CONF (0X07)
#define AS5600_REG_ANGLE (0X0E)
#define AS5600_REG_STATUS (0X0B)
#define AS5600_REG_AGC (0X1A)
#define AS5600_REG_MAGNITUDE (0X1B)
#define AS5600_REG_BURN (0XFF)
#define AS5600_RESOLUTION (4096)

#define abs(x) ((x) > 0 ? (x) : -(x))
#define _2PI 6.28318530718

static float angle_data_prev;      // 上次位置
static float full_rotation_offset; // 转过的整圈数

const char tag[] = "AS5600";

extern void drv_as5600_init(void)
{
    uint8_t data[2] = {0x20, 0xC0};
    // i2c_write_regdatas_sync(I2C_Device1, AS5600_I2C_ADDR, AS5600_REG_CONF, data, 2, 1);
}

extern uint16_t drv_as5600_read_raw_angle(void)
{
    uint16_t angle = 0;
    uint8_t data[2] = {0};
    bool stat = true;
    // stat &= i2c_read_data_sync(I2C_Device1, &data[0], AS5600_I2C_ADDR, AS5600_REG_ANGLE);
    // stat &= i2c_read_data_sync(I2C_Device1, &data[1], AS5600_I2C_ADDR, AS5600_REG_ANGLE + 1);
    if (false == stat)
    {
        API_LOGE(tag, "Read Error!");
    }

    angle = (data[0] << 8) + data[1];

    API_LOGI(tag, "angle = %d", angle);

    return angle;
}

extern float drv_as5600_read_angle(void)
{
    float angle_data = drv_as5600_read_raw_angle();

    float d_angle = angle_data - angle_data_prev;
    if (abs(d_angle) > (0.8 * AS5600_RESOLUTION))
    {
        full_rotation_offset += (d_angle > 0 ? -_2PI : _2PI);
    }
    angle_data_prev = angle_data;

    return (full_rotation_offset + (angle_data / (float)AS5600_RESOLUTION) * _2PI);
}