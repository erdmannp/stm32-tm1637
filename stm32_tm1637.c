#include "stm32_tm1637.h"


void _tm1637Start(void);
void _tm1637Stop(void);
void _tm1637ReadResult(void);
void _tm1637WriteByte(unsigned char b);
void _tm1637DelayUsec(unsigned int i);
void _tm1637ClkHigh(void);
void _tm1637ClkLow(void);
void _tm1637DioHigh(void);
void _tm1637DioLow(void);
void _tm1637DisplaySequence(unsigned char digitArr[]);
void _tm1637PrepareNumber(int n, unsigned char arr[]);

const char segmentMap[] = {
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, // 0-7
    0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71, // 8-9, A-F
    0x00
};

const char minus = 0x40;
const char none = 0x00;

void tm1637Init(void)
{
    CLK_PORT_CLK_ENABLE();
    DIO_PORT_CLK_ENABLE();
    GPIO_InitTypeDef g = {0};
    g.Pull = GPIO_PULLUP;
    g.Mode = GPIO_MODE_OUTPUT_OD; // OD = open drain
#ifdef GPIO_SPEED_FREQ_VERY_HIGH
    g.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
#else
    g.Speed = GPIO_SPEED_FREQ_HIGH;
#endif
    g.Pin = CLK_PIN;
    HAL_GPIO_Init(CLK_PORT, &g);
    g.Pin = DIO_PIN;
    HAL_GPIO_Init(DIO_PORT, &g);

    tm1637SetBrightness(8);
}

#ifdef POORTEST
void printAsNumber(unsigned char *arr)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) 
        {
            if (arr[i] == segmentMap[j])
            { 
                printf("%d", j);
                break;
            } 
            if (arr[i] == none) 
            {
                printf("_");
                break;
            }
            if(arr[i] == minus) 
            {
                printf("-");
                break;
            }
        }
    }
}
#endif

void tm1637DisplayTwoNumbers(int left, int right)
{
    unsigned char digitArr[4];
    unsigned char arr[2];

    _tm1637PrepareNumber(left, arr);
    digitArr[0] = arr[0];
    digitArr[1] = arr[1];
    
    _tm1637PrepareNumber(right, arr);
    digitArr[2] = arr[0];
    digitArr[3] = arr[1];

#ifdef POORTEST
    printf("%d%d", left, right);
    printf("%x%x%x%x", digitArr[0], digitArr[1], digitArr[2], digitArr[3]);
    printAsNumber(digitArr);
    printf("\n");
#endif

    _tm1637DisplaySequence(digitArr);
}

void _tm1637PrepareNumber(int n, unsigned char *arr) 
{
    if (n < 0)
    {
        arr[1] = minus;
        arr[0] = segmentMap[(n * -1) % 10];
    } else {
        if (n > 9) 
        {
            arr[1] = segmentMap[(n / 10) % 10];
            arr[0] = segmentMap[n  % 10];
        } else {
            arr[1] = none;
            arr[0] = segmentMap[n % 10];
        }
    }
}

void tm1637DisplayDecimal(int v, int displaySeparator)
{
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 10];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 10;
    }
    
    _tm1637DisplaySequence(digitArr);
}

void tm1637DisplayHex(int v, int displaySeparator)
{
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[v % 16];
        if (i == 2 && displaySeparator) {
            digitArr[i] |= 1 << 7;
        }
        v /= 16;
    }
    
    _tm1637DisplaySequence(digitArr);    
}


// Valid brightness values: 0 - 8.
// 0 = display off.void tm1637SetBrightness(char brightness)
void tm1637SetBrightness(char brightness)
{
    // Brightness command:
    // 1000 0XXX = display off
    // 1000 1BBB = display on, brightness 0-7
    // X = don't care
    // B = brightness
    _tm1637Start();
    _tm1637WriteByte(0x87 + brightness);
    _tm1637ReadResult();
    _tm1637Stop();
}

void _tm1637DisplaySequence(unsigned char digitArr[]) 
 {
    _tm1637Start();
    _tm1637WriteByte(0x40);
    _tm1637ReadResult();
    _tm1637Stop();

    _tm1637Start();
    _tm1637WriteByte(0xc0);
    _tm1637ReadResult();

    for (int i = 0; i < 4; ++i) {
        _tm1637WriteByte(digitArr[3 - i]);
        _tm1637ReadResult();
    }

    _tm1637Stop();
}

void _tm1637Start(void)
{
    _tm1637ClkHigh();
    _tm1637DioHigh();
    _tm1637DelayUsec(2);
    _tm1637DioLow();
}

void _tm1637Stop(void)
{
    _tm1637ClkLow();
    _tm1637DelayUsec(2);
    _tm1637DioLow();
    _tm1637DelayUsec(2);
    _tm1637ClkHigh();
    _tm1637DelayUsec(2);
    _tm1637DioHigh();
}

void _tm1637ReadResult(void)
{
    _tm1637ClkLow();
    _tm1637DelayUsec(5);
    // while (dio); // We're cheating here and not actually reading back the response.
    _tm1637ClkHigh();
    _tm1637DelayUsec(2);
    _tm1637ClkLow();
}

void _tm1637WriteByte(unsigned char b)
{
    for (int i = 0; i < 8; ++i) {
        _tm1637ClkLow();
        if (b & 0x01) {
            _tm1637DioHigh();
        }
        else {
            _tm1637DioLow();
        }
        _tm1637DelayUsec(3);
        b >>= 1;
        _tm1637ClkHigh();
        _tm1637DelayUsec(3);
    }
}

void _tm1637DelayUsec(unsigned int i)
{
    for (; i>0; i--) {
        for (int j = 0; j < 10; ++j) {
            __asm__ __volatile__("nop\n\t":::"memory");
        }
    }
}

void _tm1637ClkHigh(void)
{
    HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_SET);
}

void _tm1637ClkLow(void)
{
    HAL_GPIO_WritePin(CLK_PORT, CLK_PIN, GPIO_PIN_RESET);
}

void _tm1637DioHigh(void)
{
    HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_SET);
}

void _tm1637DioLow(void)
{
    HAL_GPIO_WritePin(DIO_PORT, DIO_PIN, GPIO_PIN_RESET);
}
