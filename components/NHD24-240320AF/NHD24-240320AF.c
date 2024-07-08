#include "NHD24-240320AF.h"

spi_device_handle_t spi;
static const char* TAG = "SPI";

static void SPI_init() {
  // SPI Bus Initialization
  spi_bus_config_t buscfg = {
      .mosi_io_num = LCD_MOSI_PIN,
      .sclk_io_num = LCD_SCK_PIN,
      .miso_io_num = -1,    // not used because of 3-Wire config
      .quadhd_io_num = -1,  // not used
      .quadwp_io_num = -1,  // not used
      .max_transfer_sz = LCD_H_RES * 80 * sizeof(uint16_t)};
  ESP_ERROR_CHECK(spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO));
  ESP_LOGI(TAG, "SPI initialized successfully");
}

static void LCD_IO_handle_init(esp_lcd_panel_io_handle_t io_handle) {
  esp_lcd_panel_io_spi_config_t io_config = {
      .dc_gpio_num = LCD_DC_PIN,
      .cs_gpio_num = LCD_CS_PIN,
      .pclk_hz = LCD_PIXEL_CLOCK_HZ,
      .lcd_cmd_bits = LCD_CMD_BITS,
      .lcd_param_bits = LCD_PARAM_BITS,
      .spi_mode = 0,
      .trans_queue_depth = 10,
  };
  ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST,
                                           &io_config, &io_handle));
}

static void LCD_controller_drv_init(esp_lcd_panel_io_handle_t io_handle,
                                    esp_lcd_panel_handle_t panel_handle) {
  esp_lcd_panel_dev_config_t panel_config = {
      .reset_gpio_num = LCD_RST_PIN,
      .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
      .bits_per_pixel = 16,
  };
  ESP_ERROR_CHECK(
      esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));
}
void NHD24_init() {
  // Initialize SPI Config
  SPI_init();

  // TODO: Make io_handle and panel_handle global.
  // either using extern in .h file or declare it in app main

  // Initialize LCD IO Device Handle
  static esp_lcd_panel_io_handle_t io_handle = NULL;
  LCD_IO_handle_init(io_handle);

  // Initialize LCD Controller Driver
  static esp_lcd_panel_handle_t panel_handle = NULL;
  LCD_controller_drv_init(io_handle, panel_handle);

  // Reset LCD
  ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
  ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));

  // Turn on Backlight
  gpio_set_direction(LCD_BCKL_PIN, GPIO_MODE_OUTPUT);
  gpio_set_level(LCD_BCKL_PIN, 1);

  ESP_LOGI(TAG, "LCD initialized successfully");
}
