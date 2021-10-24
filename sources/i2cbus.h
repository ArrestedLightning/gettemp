//i2c.h

void Open_ComPort(char com);
int Close_ComPort(void);
void I2C_Start();
void I2C_Stop();
int I2C_Tx_byte(long B);
int I2C_Rx_byte(int Ack);
void I2C_tx_bit1();
void I2C_tx_bit0();
int I2C_rx_bit();
void SDA_Output(void);
void SDA_Input(void);
void SCL_High(void);
void SCL_Low(void);
void SDA_High(void);
void SDA_Low(void);
int SDA_Value(void);
void Wait(void);
