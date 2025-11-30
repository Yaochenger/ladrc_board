//
//#include "led.h"
//#ifdef LDARC_DEVICE_LED
//
//void GPIO_LED_INIT(void)
//{
//    GPIO_InitTypeDef GPIO_InitStructure = {0};
//    GPIO_TypeDef *port, port2;
//    uint16_t pin, pin2;
//
//    SDK_Parse_Pin("PD8", &port, &pin);
//    SDK_Parse_Pin("PD10", &port2, &pin2);
//
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
//    GPIO_InitStructure.GPIO_Pin = pin | pin2;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_Init(port, &GPIO_InitStructure);
//}
//
//void LED_GPIO_Sample(void)
//{
//    Delay_Ms(500);
//    GPIO_SetBits(GPIOD, GPIO_Pin_8);
//    GPIO_SetBits(GPIOD, GPIO_Pin_10);
//    Delay_Ms(500);
//    GPIO_ResetBits(GPIOD, GPIO_Pin_8);
//    GPIO_ResetBits(GPIOD, GPIO_Pin_10);
//}
//
//int SDK_Parse_Pin(const char *s, GPIO_TypeDef **port, uint16_t *pin)
//{
//    int num = 0;
//    int i = 2;
//    char ch;
//
//    if (!s) return -1;
//
//    char c = s[1];
//
//    if (c >= 'a' && c <= 'z') c -= 32;
//
//    switch (c) {
//        case 'A': *port = GPIOA; break;
//        case 'B': *port = GPIOB; break;
//        case 'C': *port = GPIOC; break;
//        case 'D': *port = GPIOD; break;
//        case 'E': *port = GPIOE; break;
//        case 'F': *port = GPIOF; break;
//#ifdef GPIOG
//        case 'G': *port = GPIOG; break;
//#endif
//#ifdef GPIOH
//        case 'H': *port = GPIOH; break;
//#endif
//#ifdef GPIOI
//        case 'I': *port = GPIOI; break;
//#endif
//#ifdef GPIOJ
//        case 'J': *port = GPIOJ; break;
//#endif
//#ifdef GPIOK
//        case 'K': *port = GPIOK; break;
//#endif
//        default: return -1;
//    }
//
//    while (1)
//    {
//        ch = s[i];
//        if (ch < '0' || ch > '9') break;
//        num = num * 10 + (ch - '0');
//        i++;
//    }
//
//    if (num < 0 || num > 15) return -1;
//
//    *pin = (1U << num);
//    return 0;
//}
//
//#endif // LDARC_DEVICE_LED
