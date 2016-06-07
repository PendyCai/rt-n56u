/* Skyworth RN1 Wireless Router */

#define BOARD_PID		"SKY-RN1"
#define BOARD_NAME		"SKY-RN1"
#define BOARD_DESC		"Skyworth RN1 MT7621A 11AC Wireless Router"
#define BOARD_VENDOR_NAME	"Skyworth Digital Technology Co., Ltd."
#define BOARD_VENDOR_URL	""
#define BOARD_MODEL_URL		""
#define BOARD_BOOT_TIME		30
#define BOARD_FLASH_TIME	40
#define BOARD_GPIO_BTN_RESET	14
#define BOARD_GPIO_BTN_WPS	    18
//#define BOARD_GPIO_BTN_FN1	7
//#define BOARD_GPIO_BTN_FN2	10

#define BOARD_GPIO_LED_INVERTED		/* LED pins value is inverted (1: LED show, 0: LED hide) */
#undef  BOARD_GPIO_LED_ALL

/* WIFI 2.4G / 5G LED Indicators */
#undef  BOARD_GPIO_LED_WIFI
#undef  BOARD_GPIO_LED_SW2G
#undef  BOARD_GPIO_LED_SW5G

/* Front LED Indicators */
#undef  BOARD_GPIO_LED_ROUTER
#define BOARD_GPIO_LED_FRONT_RED    6   /* Front LED Red */
#define BOARD_GPIO_LED_FRONT_GREEN  9   /* Front LED Green */
#define BOARD_GPIO_LED_POWER	BOARD_GPIO_LED_FRONT_RED

/* Ethernet LED Indicators */
//#define BOARD_GPIO_LED_LAN	12	/* LED Fn */
//#define BOARD_GPIO_LED_WAN	17

/* USB Power Control and LED */
#define BOARD_GPIO_PWR_USB_ON	1	/* 1: 5V Power ON, 0: 5V Power OFF */
#define BOARD_GPIO_PWR_USB	    13	/* USB2.0 5V Power */
#define BOARD_GPIO_PWR_USB2	    17	/* USB3.0 5V Power */
#define BOARD_GPIO_LED_USB      13	/* USB #1 LED */
#define BOARD_GPIO_LED_USB2     14	/* USB #2 LED */
#undef  BOARD_GPIO_LED_USB
#undef  BOARD_GPIO_LED_USB2

#define BOARD_HAS_5G_11AC	    1
#define BOARD_NUM_ANT_5G_TX	    2
#define BOARD_NUM_ANT_5G_RX	    2
#define BOARD_NUM_ANT_2G_TX	    2
#define BOARD_NUM_ANT_2G_RX	    2
#define BOARD_NUM_ETH_LEDS	    1
#define BOARD_NUM_ETH_EPHY	    3
#define BOARD_ETH_LED_SWAP	    0
#define BOARD_HAS_EPHY_L1000	1
#define BOARD_HAS_EPHY_W1000	1
#define BOARD_NUM_UPHY_USB3	    1
#define BOARD_USB_PORT_SWAP	    1	/* USB3.0 = #2, USB2.0 = #1 */
