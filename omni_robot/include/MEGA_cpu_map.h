#ifndef DEFINES_H
#define DEFINES_H
#define cpu_map_for_MEGA

#define fr_motor_step_ddr DDRB
#define fr_motor_step_wPort PORTB
#define fr_motor_step_rPort PINB
#define fr_motor_step_bit 6

#define fr_motor_dir_ddr DDRB
#define fr_motor_dir_wPort PORTB
#define fr_motor_dir_rPort PINB
#define fr_motor_dir_bit 7

#define bl_motor_step_ddr DDRE
#define bl_motor_step_wPort PORTE
#define bl_motor_step_rPort PINE
#define bl_motor_step_bit 4

#define fl_motor_step_ddr DDRE
#define fl_motor_step_wPort PORTE
#define fl_motor_step_rPort PINE
#define fl_motor_step_bit 5

#define br_motor_step_ddr DDRG
#define br_motor_step_wPort PORTG
#define br_motor_step_rPort PING
#define br_motor_step_bit 5

#define bl_motor_dir_ddr DDRE
#define bl_motor_dir_wPort PORTE
#define bl_motor_dir_rPort PINE
#define bl_motor_dir_bit 3

#define fl_motor_dir_ddr DDRH
#define fl_motor_dir_wPort PORTH
#define fl_motor_dir_rPort PINH
#define fl_motor_dir_bit 3

#define br_motor_dir_ddr DDRH
#define br_motor_dir_wPort PORTH
#define br_motor_dir_rPort PINH
#define br_motor_dir_bit 4

#define motors_enable_ddr DDRH
#define motors_enable_wPort PORTH
#define motors_enable_rPort PINH
#define motors_enable_bit 5

#define I2C_controller_SCL_ddr DDRC
#define I2C_controller_SCL_wPort PORTD
#define I2C_controller_SCL_rPort PIND
#define I2C_controller_SCL_bit 0

#define I2C_controller_SDA_ddr DDRC
#define I2C_controller_SDA_wPort PORTD
#define I2C_controller_SDA_rPort PIND
#define I2C_controller_SDA_bit 1


#define SetBit(RES, BIT)(RES |= (1 << BIT)) // Set BIT in RES to HIGH
#define ClrBit(RES, BIT)(RES &= ~ (1 << BIT)) // Set BIT in RES to LOW
#define TstBit(RES, BIT)(RES &  (1 << BIT)) // Test BIT in RES and return 0 or 1
#define InvBit(RES, BIT)(RES ^= (1 << BIT)) // Invert BIT in RES (0 to 1 and 1 to 0)
#define WriteBit(RES, BIT, VAL) (VAL)?SetBit(RES, BIT):ClrBit(RES, BIT) // Write VAL in BIT in RES (0 or 1)

#endif