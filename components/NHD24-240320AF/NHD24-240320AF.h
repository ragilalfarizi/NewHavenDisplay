#ifndef NHD24240320AF_H
#define NHD24240320AF_H

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "esp_err.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"

#define LCD_HOST           SPI2_HOST
#define LCD_MOSI_PIN       23
#define LCD_SCK_PIN        18
#define LCD_CS_PIN         5
#define LCD_RST_PIN        22
#define LCD_BL_PIN         21  // Optional: Backlight control pin
#define LCD_DC_PIN         4
#define LCD_BCKL_PIN       2
#define LCD_PIXEL_CLOCK_HZ 2 * 1000 * 1000
#define LCD_CMD_BITS       8
#define LCD_PARAM_BITS     8
#define LCD_H_RES          240
#define LCD_V_RES          320

static void SPI_init();
static void LCD_IO_handle_init(esp_lcd_panel_io_handle_t io_handle);
static void LCD_controller_drv_init(esp_lcd_panel_io_handle_t io_handle,
                                    esp_lcd_panel_handle_t panel_handle);
void NHD24_init();

#endif  // NHD24240320AF_H
